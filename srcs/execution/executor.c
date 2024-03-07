/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manumart <manumart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 12:31:02 by mbraga-s          #+#    #+#             */
/*   Updated: 2024/03/07 04:51:56 by manumart         ###   ########.fr       */
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
		else if (!ft_strncmp(data->args[0], "export", 7))
		{
			exec_export(data);
			return (1);
		}
		else if (!ft_strncmp(data->args[0], "unset", 6))
		{
			exec_unset(data);
			return (1);
		}
		else if (!ft_strncmp(data->args[0], "env", 4))
		{
			exec_env(data);
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

void	execution(t_data *data)
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
		first_fork(data, msdata()->envp);
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
	while (current)
	{
		waitpid(current->pid, &status, 0);
		if (WIFEXITED(status))
			g_data.status = WEXITSTATUS(status);
		current = current->next;
	}
}
