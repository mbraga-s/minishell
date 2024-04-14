/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manumart <manumart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 07:09:52 by manumart          #+#    #+#             */
/*   Updated: 2024/04/14 14:15:05 by manumart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	findonly(char c, char c2, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c || str[i] == c2)
			i++;
		else
			return (1);
	}
	return (0);
}

void	exec_echo(t_data *data, int fd)
{
	int	newline;
	int	i;

	newline = 0;
	i = 1;
	if (data->args[1])
	{
		if (!findonly('-', 'n', data->args[1]) && !ft_strncmp(data->args[1],
				"-n", 2))
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
