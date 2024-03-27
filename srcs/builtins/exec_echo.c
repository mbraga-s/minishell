/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraga-s <mbraga-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 07:09:52 by manumart          #+#    #+#             */
/*   Updated: 2024/03/27 14:22:05 by mbraga-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	exec_echo(t_data *data, int fd)
{
	int	newline;
	int	i;

	newline = 0;
	i = 1;
	if (data->args[1])
	{
		if (!ft_strncmp(data->args[1], "-n", 2))
		{
			newline = 1;
			i++;
		}
		while (data->args[i])
		{
			ft_putstr(fd, data->args[i]);
			i++;
			if (data->args[i])
				ft_putstr(fd, " ");
		}
		if (newline == 0)
			ft_putstr(fd, "\n");
	}
	else
		ft_putstr(fd, "\n");
}
