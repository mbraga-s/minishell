/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraga-s <mbraga-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 15:41:19 by mbraga-s          #+#    #+#             */
/*   Updated: 2024/02/13 18:19:40 by mbraga-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	file_check(int dups[2], t_data *data)
{
	int	fd[2];

	if (data->infile)
	{
		fd[0] = open(data->infile, O_RDONLY);
		if (fd[0] < 0)
		{
			perror(data->infile);
			//fd[0] = open("temp", O_CREAT, 0644);
		}
		dups[0] = dupcheck(fd[0], dups[0]);
		close(fd[0]);
	}
	if (data->outfile)
	{
		fd[1] = open(data->outfile, O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (fd[1] < 0)
		{
			perror(data->outfile);
			exit(1);
		}
		dups[1] = dupcheck(fd[1], dups[1]);
		close(fd[1]);
	}
}

void	first_fork(t_data *data, char **envp)
{
	char	*path;
	int		dups[2];

	dups[0] = 0;
	dups[1] = 1;
	path = check_path(data->args[0], envp);
	if (data->fd[0] != 0)
	{
		dups[1] = dupcheck(data->fd[1], 1);
		close_fd(data->fd);
	}
	file_check(dups, data);
	if (path)
		execve(path, data->args, envp);
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

	path = check_path(data->args[0], envp);
	dups[0] = dupcheck(data->prev->fd[0], 0);
	dups[1] = dupcheck(data->fd[1], 1);
	close_fd(data->prev->fd);
	close_fd(data->fd);
	file_check(dups, data);
	if (path)
		execve(path, data->args, envp);
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
	
	dups[0] = 0;
	dups[1] = 1;
	path = check_path(data->args[0], envp);
	dups[0] = dupcheck(data->prev->fd[0], 0);
	close_fd(data->prev->fd);
	file_check(dups, data);
	if (path)
		execve(path, data->args, envp);
	close_fd(dups);
	data = ft_lstfirst(data);
	free_all(data);
	free(path);
	exit(1);
}
