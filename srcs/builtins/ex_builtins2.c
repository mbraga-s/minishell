/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_builtins2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manumart <manumart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 07:15:04 by manumart          #+#    #+#             */
/*   Updated: 2024/03/26 14:49:08 by manumart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_valid(char *str)
{
	int	i;

	i = 0;
	if ((str[i] >= '0' && str[i] <= '9') || str[i] == '=')
		return (0);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_' && str[i] != '=')
			return (0);
		i++;
	}
	return (1);
}

int	digitquestionmark(int str)
{
	if (str >= '0' && str <= '9')
		return (1);
	return (0);
}

int	searchforchar(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_strjoinwofree(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*ptr;

	i = 0;
	j = 0;
	ptr = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!ptr)
		return (0);
	while (s1 && s1[i])
	{
		ptr[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		ptr[i] = s2[j];
		i++;
		if (s2[j] == '\n')
			break ;
		j++;
	}
	ptr[i] = '\0';
	return (ptr);
}
