/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manumart <manumart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 07:07:19 by manumart          #+#    #+#             */
/*   Updated: 2024/03/08 19:13:31 by manumart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	searchinenvp(char *input, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], input, ft_strlen(input)) != 0)
			i++;
		else
			return (i);
	}
	return (-1);
}


void	exec_env(t_data *data)
{
	int	i;

	i = 0;
	if (data->args[1])
	{
		ft_putstr(2, "env: '");
		ft_putstr(2, data->args[1]);
		ft_putstr(2, "': No such file or directory\n");
	}
	else
	{
		while (msdata()->envp[i])
		{
			ft_putstr(1, rem_allquotes(msdata()->envp[i]));
			ft_putstr(1, "\n");
			i++;
		}
	}
}
