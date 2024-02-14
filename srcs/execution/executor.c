/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraga-s <mbraga-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 12:31:02 by mbraga-s          #+#    #+#             */
/*   Updated: 2024/02/14 17:10:48 by mbraga-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_exit(t_data *data)
{
	if (!ft_strncmp(data->args[0], "exit", 5))
	{
		exec_exit(data);
		return (1);
	}
	return (0);
}

void	execution(t_data *data, char **envp)
{
	int		pid[2];
	t_data	*current;

	current = data;
	if (data->next)
	{
		if (pipe(data->fd) == -1)
		{
			perror(NULL);
			exit(1);
		}
	}
	else if (check_exit(data))
		return ;
	pid[0] = fork();
	if (pid[0] == 0)
		first_fork(data, envp);
	data = data->next;
	while (data && data->next)
	{
		if (pipe(data->fd) == -1)
		{
			perror(NULL);
			exit(1);
		}
		pid[1] = fork();
		if (pid[1] == 0)
			mid_fork(data, envp);
		close_fd(data->prev->fd);
		data = data->next;
	}
	if (data)
	{
		pid[1] = fork();
		if (pid[1] == 0)
			last_fork(data, envp);
		close_fd(data->prev->fd);
	}
	while (current)
	{
		waitpid(-1, NULL, 0);
		current = current->next;
	}
}
