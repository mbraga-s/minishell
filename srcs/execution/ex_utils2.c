/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraga-s <mbraga-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 15:41:51 by mbraga-s          #+#    #+#             */
/*   Updated: 2024/04/11 00:06:07 by mbraga-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//Checks if there is an infile and/or outfile on the node.
//If there is, opens them and dups the file descriptor to stdin or stdout.
//Works for multiple infiles and outfiles.
int	file_check(int dups[2], t_data *data)
{
	if (data->fd_in == -1 || data->fd_out == -1)
	{
		g_data.status = 1;
		return (0);
	}
	if (data->fd_in > 0)
	{
		dups[0] = dupcheck(data->fd_in, dups[0]);
	}
	if (data->fd_out > 0)
	{
		dups[1] = dupcheck(data->fd_out, dups[1]);
	}
	return (1);
}
