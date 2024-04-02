/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraga-s <mbraga-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 07:09:19 by manumart          #+#    #+#             */
/*   Updated: 2024/04/02 15:28:58 by mbraga-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	exit_error(t_data *data)
{
	ft_putstr(2, "exit :");
	ft_putstr(2, data->args[1]);
	ft_putstr(2, ": numeric argument required\n");
	g_data.status = 2;
}

void	exec_exit(t_data *data)
{
	int	i;

	i = 0;
	g_data.status = 0;
	while (data->args[i])
		i++;
	printf("exit\n");
	if (i <= 2)
	{
		if (i == 2 && ft_strdigit(data->args[1]))
			exit_error(data);
		else if (i == 2 && !ft_strdigit(data->args[1]) && 
			(ft_atoi(data->args[1]) > 0))
			g_data.status = ft_atoi(data->args[1]);
		else if (i == 2 && !ft_strdigit(data->args[1]) && 
			(ft_atoi(data->args[1]) < 0))
			g_data.status = 156;
		free_array(msdata()->envp);
		free_all(ft_lstfirst(data));
		exit(g_data.status);
	}
	ft_putstr(2, "exit: too many arguments\n");
	g_data.status = 1;
}
