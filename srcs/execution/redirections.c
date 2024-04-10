/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraga-s <mbraga-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 19:42:00 by mbraga-s          #+#    #+#             */
/*   Updated: 2024/04/10 23:59:00 by mbraga-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
			perror(data->infile[i]);
			return (-1);
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
	fd = 0;
	while (data->outfile && data->outfile[++i])
	{
		if (!ft_strncmp(data->outflag[i], "0", 1))
			fd = open(data->outfile[i], O_RDWR | O_CREAT | O_TRUNC, 0644);
		else if (!ft_strncmp(data->outflag[i], "1", 1))
			fd = open(data->outfile[i], O_RDWR | O_CREAT | O_APPEND, 0644);
		if (fd < 0)
			return (-1);
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
		if (data->fd_out > 0)
			close(data->fd_out);
		data = data->next;
	}
}
