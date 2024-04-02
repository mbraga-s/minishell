/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraga-s <mbraga-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 15:41:51 by mbraga-s          #+#    #+#             */
/*   Updated: 2024/04/02 14:39:53 by mbraga-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	infile_check(int dups[2], t_data *data);

int	outfile_check(int dups[2], t_data *data);

//Checks if there is an infile and/or outfile on the node.
//If there is, opens them and dups the file descriptor to stdin or stdout.
//Works for multiple infiles and outfiles.
int	file_check(int dups[2], t_data *data)
{
	if (infile_check(dups, data) && outfile_check(dups, data))
		return (1);
	return (0);
}

//Error set for infile
void	in_error(char *str)
{
	perror(str);
	g_data.status = 1;
}

//Opens the infiles and the here-docs.
int	infile_check(int dups[2], t_data *data)
{
	int		fd;
	int		i;

	i = -1;
	while (data->infile && data->infile[i++])
	{
		if (!ft_strncmp(data->inflag[i], "0", 1))
			fd = open(data->infile[i], O_RDONLY);
		else
			fd = ft_heredoc(data->infile[i]);
		if (fd < 0)
		{
			in_error(data->infile[i]);
			return (0);
		}
		if (!(data->infile[i + 1]))
			break ;
		close(fd);
	}
	if (data->infile)
	{
		dups[0] = dupcheck(fd, dups[0]);
		close(fd);
	}
	return (1);
}

//Opens the outfiles.
int	outfile_check(int dups[2], t_data *data)
{
	int	fd;
	int	i;

	i = 0;
	while (data->outfile && data->outfile[i])
	{
		if (!ft_strncmp(data->outflag[i], "0", 1))
			fd = open(data->outfile[i], O_RDWR | O_CREAT | O_TRUNC, 0644);
		else
			fd = open(data->outfile[i], O_RDWR | O_CREAT | O_APPEND, 0644);
		if (fd < 0)
		{
			perror(data->outfile[i]);
			g_data.status = 1;
			return (0);
		}
		dups[1] = dupcheck(fd, dups[1]);
		close(fd);
		i++;
	}
	return (1);
}
