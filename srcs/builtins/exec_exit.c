/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manumart <manumart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 07:09:19 by manumart          #+#    #+#             */
/*   Updated: 2024/03/07 07:16:03 by manumart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
		{
			printf("exit : %s: numeric argument required\n", data->args[1]);
			g_data.status = 255;
		}
		else if (i == 2 && !ft_strdigit(data->args[1]))
		{
			g_data.status = ft_atoi(data->args[1]);
		}
		free_array(msdata()->envp);
		free_all(ft_lstfirst(data));
		exit(g_data.status);
	}
	else
		printf("exit: too many arguments\n");
}
