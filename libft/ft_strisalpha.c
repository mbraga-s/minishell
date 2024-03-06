/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strisalpha.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraga-s <mbraga-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 15:23:17 by mbraga-s          #+#    #+#             */
/*   Updated: 2024/03/06 16:02:20 by mbraga-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strisalpha(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if ((str[i] >= 'A' && str[i] <= 'Z'))
			return (1);
		else if (str[i] >= 'a' && str[i] <= 'z')
			return (1);
		i++;
	}
	return (0);
}
