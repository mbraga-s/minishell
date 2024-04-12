/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraga-s <mbraga-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 15:41:51 by mbraga-s          #+#    #+#             */
/*   Updated: 2024/04/12 16:32:40 by mbraga-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//Checks if there is an infile and/or outfile on the node.
//If there is, opens them and dups the file descriptor to stdin or stdout.
//Works for multiple infiles and outfiles.
int	file_check(int dups[2], t_data *data)
{
	signalhandlechild();
	if (data->fd_in < 0 || data->fd_out < 0)
	{
		if (data->fd_in == -1 || data->fd_out == -1)
			g_data.status = 1;
		return (0);
	}
	if (data->fd_in > 0)
	{
		dups[0] = dupcheck(data->fd_in, dups[0]);
	}
	if (data->fd_out > 1)
	{
		dups[1] = dupcheck(data->fd_out, dups[1]);
	}
	return (1);
}

//Opens the infiles and the here-docs.
//Returns the latest fd opened or -1 if error.
int	in_check(t_data *data)
{
	int	fd;
	int	i;

	i = -1;
	fd = 0;
	while (data->infile && data->infile[++i])
	{
		if (!ft_strncmp(data->inflag[i], "0", 1))
			fd = open(data->infile[i], O_RDONLY);
		else if (!ft_strncmp(data->inflag[i], "1", 1))
			fd = ft_heredoc(data->infile[i], data);
		if (fd < 0)
		{
			if (fd == -1)
				perror(data->infile[i]);
			return (fd);
		}
		if (!(data->infile[i + 1]))
			break ;
		close(fd);
	}
	return (fd);
}

//Opens or creates the outfiles.
//Returns the latest fd opened or -1 if error.
int	out_check(t_data *data)
{
	int	fd;
	int	i;

	i = -1;
	fd = 1;
	while (data->outfile && data->outfile[++i])
	{
		if (!ft_strncmp(data->outflag[i], "0", 1))
			fd = open(data->outfile[i], O_RDWR | O_CREAT | O_TRUNC, 0644);
		else if (!ft_strncmp(data->outflag[i], "1", 1))
			fd = open(data->outfile[i], O_RDWR | O_CREAT | O_APPEND, 0644);
		if (fd < 0)
		{
			perror(data->outfile[i]);
			return (-1);
		}
		if (!(data->outfile[i + 1]))
			break ;
		close(fd);
	}
	return (fd);
}

//Handles redirections
void	redirections(t_data *data)
{
	while (data)
	{
		data->fd_in = in_check(data);
		data->fd_out = out_check(data);
		data = data->next;
	}
}

//Closes all file descriptors stored in the all nodes
//fd_in and fd_out.
void	close_all(t_data *data)
{
	data = ft_lstfirst(data);
	while (data)
	{
		if (data->fd_in > 0)
			close(data->fd_in);
		if (data->fd_out > 1)
			close(data->fd_out);
		data = data->next;
	}
}
