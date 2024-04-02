/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraga-s <mbraga-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 07:08:21 by manumart          #+#    #+#             */
/*   Updated: 2024/04/02 16:31:26 by mbraga-s         ###   ########.fr       */
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
			free(msdata()->envp[output]);
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
