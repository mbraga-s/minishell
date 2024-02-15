/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraga-s <mbraga-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 15:41:19 by mbraga-s          #+#    #+#             */
/*   Updated: 2024/02/15 16:08:47 by mbraga-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	first_fork(t_data *data, char **envp)
{
	char	*path;
	int		dups[2];

	dups[0] = 0;
	dups[1] = 1;
	path = NULL;
	if (data->fd[0] != 0)
	{
		dups[1] = dupcheck(data->fd[1], 1);
		close_fd(data->fd);
	}
	if (file_check(dups, data))
	{
		if (!check_builtin(data))
			path = check_path(data->args[0], envp);
		if (path)
			execve(path, data->args, envp);
	}
	close_fd(dups);
	data = ft_lstfirst(data);
	free_all(data);
	free(path);
	exit(1);
}

void	mid_fork(t_data *data, char **envp)
{
	char	*path;
	int		dups[2];

	path = NULL;
	dups[0] = dupcheck(data->prev->fd[0], 0);
	dups[1] = dupcheck(data->fd[1], 1);
	close_fd(data->prev->fd);
	close_fd(data->fd);
	if (file_check(dups, data))
	{
		if (!check_builtin(data))
			path = check_path(data->args[0], envp);
		if (path)
			execve(path, data->args, envp);
	}
	close_fd(dups);
	data = ft_lstfirst(data);
	free_all(data);
	free(path);
	exit(1);
}

void	last_fork(t_data *data, char **envp)
{
	char	*path;
	int		dups[2];

	path = NULL;
	dups[0] = 0;
	dups[1] = 1;
	dups[0] = dupcheck(data->prev->fd[0], 0);
	close_fd(data->prev->fd);
	if (file_check(dups, data))
	{
		if (!check_builtin(data))
			path = check_path(data->args[0], envp);
		if (path)
			execve(path, data->args, envp);
	}
	close_fd(dups);
	data = ft_lstfirst(data);
	free_all(data);
	free(path);
	exit(1);
}
