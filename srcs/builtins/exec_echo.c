/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manumart <manumart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 07:09:52 by manumart          #+#    #+#             */
/*   Updated: 2024/03/08 19:12:55 by manumart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	exec_echo(t_data *data)
{
	int	newline;
	int	i;

	newline = 0;
	i = 1;
	if (data->args[1])
	{
		if (!ft_strncmp(data->args[1], "-n", 2))
			newline = 1;
		else
		{
			while (data->args[i])
			{
				ft_putstr(1, data->args[i]);
				i++;
				if (data->args[i])
					ft_putstr(1, " ");
			}
		}
		if (newline == 0)
			ft_putstr(1, "\n");
	}
	else
		ft_putstr(1, "\n");
}
