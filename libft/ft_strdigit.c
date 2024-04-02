/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdigit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraga-s <mbraga-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 11:13:33 by manumart          #+#    #+#             */
/*   Updated: 2024/04/02 15:05:26 by mbraga-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strdigit(char *str)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (str && str[i])
	{
		if ((str[i] == 43 || str[i] == 45) && flag == 0)
			flag = 1;
		else if (str[i] < '0' || str[i] > '9')
			return (1);
		i++;
	}
	return (0);
}
