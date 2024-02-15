/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraga-s <mbraga-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 15:41:51 by mbraga-s          #+#    #+#             */
/*   Updated: 2024/02/15 15:50:36 by mbraga-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//Checks if there is an infile and/or outfile on the node
//If there is, opens them and dups the file descriptor to stdin or stdout
//Works for multiple infiles and outfiles

int	file_check(int dups[2], t_data *data)
{
	int	fd[2];
	int	i;

	i = 0;
	while (data->infile && data->infile[i])
	{
		fd[0] = open(data->infile[i], O_RDONLY);
		if (fd[0] < 0)
		{
			perror(data->infile[i]);
			return (0);
		}
		dups[0] = dupcheck(fd[0], dups[0]);
		close(fd[0]);
		i++;
	}
	i = 0;
	while (data->outfile && data->outfile[i])
	{
		fd[1] = open(data->outfile[i], O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (fd[1] < 0)
		{
			perror(data->outfile[i]);
			return (0);
		}
		dups[1] = dupcheck(fd[1], dups[1]);
		close(fd[1]);
		i++;
	}
	return (1);
}
