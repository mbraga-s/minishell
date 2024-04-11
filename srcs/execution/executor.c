/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraga-s <mbraga-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 12:31:02 by mbraga-s          #+#    #+#             */
/*   Updated: 2024/04/11 01:14:44 by mbraga-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//Error management for pipe creation
void	pipe_protect(t_data *data)
{
	if (pipe(data->fd) == -1)
	{
		perror(NULL);
		g_data.status = 1;
		exit(g_data.status);
	}
}

//Runs the forks and executes the pipe loop making sure
//no more than 2 pipes are open at a time.
void	execute_forks(t_data *data)
{
	data->pid = fork();
	if (data->pid == 0)
		first_fork(data, msdata()->envp);
	data = data->next;
	while (data && data->next)
	{
		pipe_protect(data);
		data->pid = fork();
		if (data->pid == 0)
			mid_fork(data, msdata()->envp);
		close_fd(data->prev->fd);
		data = data->next;
	}
	if (data)
	{
		data->pid = fork();
		if (data->pid == 0)
			last_fork(data, msdata()->envp);
		close_fd(data->prev->fd);
	}
}

//Handles the signals comming from the child process
void	exec_signal_handle(t_data	*data)
{
	int		status;

	while (data)
	{
		waitpid(data->pid, &status, 0);
		if (WIFSIGNALED(status))
		{
			if (status == 130)
				g_data.status = 130;
			else if (status == 131)
				g_data.status = 131;
		}
		if (WIFEXITED(status))
			g_data.status = WEXITSTATUS(status);
		data = data->next;
	}
	if (g_data.status == 130)
		ft_putstr(1, "\n");
	else if (g_data.status == 131)
		ft_putstr(2, "Quit (core dumped)\n");
}

//Minishell's executor.
//Runs the builtin check, forks and waits for all processes to end.
void	execution(t_data *data)
{
	if (data->next)
		pipe_protect(data);
	else if (is_builtin(data))
	{
		if (data->fd_in == -1)
			return ;
		printf("%d\n\n", data->fd_out);
		check_builtin(data, data->fd_out);
		close_all(data);
		return ;
	}
	execute_forks(data);
	data = ft_lstfirst(data);
	exec_signal_handle(data);
	close_all(data);
}
