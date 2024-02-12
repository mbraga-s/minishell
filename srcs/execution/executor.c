/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraga-s <mbraga-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 12:31:02 by mbraga-s          #+#    #+#             */
/*   Updated: 2024/02/12 16:56:41 by mbraga-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	execution(t_data *data, char **envp)
{
	int		*fds[2];
	int		fd1[2];
	int		fd2[2];
	int		pid[2];
	int		flag;
	t_data	*current;

	fds[0] = fd1;
	fds[1] = fd2;
	flag = 1;
	fd1[0] = 0;
	fd1[1] = 1;
	current = data;
	if (data->next)
	{
		if (pipe(fd1) == -1)
		{
			perror(NULL);
			exit(1);
		}
	}
	pid[0] = fork();
	if (pid[0] == 0)
		first_fork(data, envp, fd1);
	data = data->next;
	while (data && data->next)
	{
		if (pipe(fds[flag]) == -1)
		{
			perror(NULL);
			exit(1);
		}
		pid[1] = fork();
		if (pid[1] == 0)
			mid_fork(data, envp, fds, flag);
		if (flag == 1)
			flag = 0;
		else
			flag = 1;
		close_fd(fds[flag]);
		data = data->next;
	}
	if (data)
	{
		if (flag == 1)
			flag = 0;
		else
			flag = 1;
		pid[1] = fork();
		if (pid[1] == 0)
			last_fork(data, envp, fds[flag]);
		close_fd(fds[flag]);
	}
	while (current)
	{
		waitpid(-1, NULL, 0);
		current = current->next;
	}
}
