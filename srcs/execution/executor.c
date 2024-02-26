/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraga-s <mbraga-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 12:31:02 by mbraga-s          #+#    #+#             */
/*   Updated: 2024/02/26 16:22:42 by mbraga-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//Checks if the cmd given is one of the built-ins and, if it is, runs it

int	check_builtin(t_data *data)
{
	if (data->args && data->args[0])
	{
		if (!ft_strncmp(data->args[0], "pwd", 4))
		{
			exec_pwd();
			return (1);
		}
		else if (!ft_strncmp(data->args[0], "cd", 3))
		{
			exec_cd(data);
			return (1);
		}
		else if (!ft_strncmp(data->args[0], "exit", 5))
		{
			exec_exit(data);
			return (1);
		}
		else if (!ft_strncmp(data->args[0], "echo", 5))
		{
			exec_echo(data);
			return (1);
		}		
	}
	return (0);
}

int	is_builtin(t_data *data)
{
	if (data->args && data->args[0])
	{
		if (!ft_strncmp(data->args[0], "cd", 3))
		{
			exec_cd(data);
			return (1);
		}
		else if (!ft_strncmp(data->args[0], "exit", 5))
		{
			exec_exit(data);
			return (1);
		}
	}
	return (0);
}

void	execution(t_data *data, char **envp)
{
	t_data	*current;
	int		status;

	status = 0;
	current = data;
	if (data->next)
	{
		if (pipe(data->fd) == -1)
		{
			perror(NULL);
			exit(1);
		}
	}
	else if (is_builtin(data))
		return ;
	data->pid = fork();
	if (data->pid == 0)
		first_fork(data, envp);
	data = data->next;
	while (data && data->next)
	{
		if (pipe(data->fd) == -1)
		{
			perror(NULL);
			exit(1);
		}
		data->pid = fork();
		if (data->pid == 0)
			mid_fork(data, envp);
		close_fd(data->prev->fd);
		data = data->next;
	}
	if (data)
	{
		data->pid = fork();
		if (data->pid == 0)
			last_fork(data, envp);
		close_fd(data->prev->fd);
	}
	while (current)
	{
		waitpid(current->pid, &status, 0);
		if (WIFEXITED(status))
			g_data.status = WEXITSTATUS(status);
		current = current->next;
	}
}
