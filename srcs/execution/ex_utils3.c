/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_utils3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraga-s <mbraga-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 16:05:34 by mbraga-s          #+#    #+#             */
/*   Updated: 2024/03/26 17:09:53 by mbraga-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	btn_infile(t_data *data);

int	btn_outfile(t_data *data);

//Checks if there is an infile and/or outfile for the built-in.
int	btn_redirect(t_data *data)
{
	int	fd;

	fd = 1;
	if (!btn_infile(data))
	{
		g_data.status = 1;
		return (0);
	}
	fd = btn_outfile(data);
	if (fd)
		return (fd);
	g_data.status = 1;
	return (0);
}

//Opens the infiles and the here-docs.
int	btn_infile(t_data *data)
{
	int	fd;
	int	i;

	i = 0;
	while (data->infile && data->infile[i])
	{
		if (!ft_strncmp(data->inflag[i], "0", 1))
			fd = open(data->infile[i], O_RDONLY);
		else
			fd = ft_heredoc(data->infile[i]);
		if (fd < 0)
		{
			perror(data->infile[i]);
			return (0);
		}
		close(fd);
		i++;
	}
	return (1);
}

//Opens the outfiles.
int	btn_outfile(t_data *data)
{
	int	fd;
	int	i;

	i = 0;
	fd = 1;
	while (data->outfile && data->outfile[i])
	{
		if (!ft_strncmp(data->outflag[i], "0", 1))
			fd = open(data->outfile[i], O_RDWR | O_CREAT | O_TRUNC, 0644);
		else
			fd = open(data->outfile[i], O_RDWR | O_CREAT | O_APPEND, 0644);
		if (fd < 0)
		{
			perror(data->outfile[i]);
			return (0);
		}
		if (data->outfile[i + 1])
			close(fd);
		i++;
	}
	return (fd);
}
