/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraga-s <mbraga-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 12:31:02 by mbraga-s          #+#    #+#             */
/*   Updated: 2024/03/18 17:29:12 by mbraga-s         ###   ########.fr       */
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

//Minishell's executor.
//Runs the builtin check, forks and waits for all processes to end.
void	execution(t_data *data)
{
	int		status;
	int		btn_fd;

	status = 0;
	if (data->next)
		pipe_protect(data);
	else if (is_builtin(data))
	{
		btn_fd = btn_redirect(data);
		if (btn_fd == 0)
			return ;
		check_builtin(data, btn_fd);
		if (btn_fd > 2)
			close(btn_fd);
		return ;
	}
	execute_forks(data);
	data = ft_lstfirst(data);
	while (data)
	{
		waitpid(data->pid, &status, 0);
		if (WIFEXITED(status))
			g_data.status = WEXITSTATUS(status);
		data = data->next;
	}
}
