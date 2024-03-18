/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraga-s <mbraga-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 12:31:02 by mbraga-s          #+#    #+#             */
/*   Updated: 2024/03/18 16:36:07 by mbraga-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	execution(t_data *data)
{
	t_data	*current;
	int		status;
	int		btn_fd;

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
	{
		btn_fd = btn_redirect(data);
		if (btn_fd == 0)
		{
			g_data.status = 1;
			return ;
		}
		check_builtin(data, btn_fd);
		if (btn_fd > 2)
			close(btn_fd);
		return ;
	}
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
