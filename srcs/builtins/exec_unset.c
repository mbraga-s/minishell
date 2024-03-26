/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manumart <manumart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 07:08:21 by manumart          #+#    #+#             */
/*   Updated: 2024/03/26 14:46:20 by manumart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	exec_unset(t_data *data)
{
	int	i;
	int	output;

	i = 1;
	while (data->args[i])
	{
		output = searchinenvp(data->args[i], msdata()->envp);
		if (output != -1)
		{
			while (msdata()->envp[output + 1])
			{
				msdata()->envp[output] = msdata()->envp[output + 1];
				output++;
			}
			msdata()->envp[output] = NULL;
		}
		i++;
	}
}
