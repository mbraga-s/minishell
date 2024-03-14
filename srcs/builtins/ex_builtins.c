/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manumart <manumart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 06:56:30 by manumart          #+#    #+#             */
/*   Updated: 2024/03/07 08:00:56 by manumart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// free array
void	free_array(char **str)
{
	int	i;

	if (str == NULL)
		return ;
	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

int	getdpsize(char **dp)
{
	int	dp_size;

	dp_size = 0;
	while (dp[dp_size] != NULL)
		dp_size++;
	return (dp_size);
}

char	**dpdup(char **str)
{
	char	**dup;
	size_t	i;
	size_t	j;

	if (!str || !str[0])
		return (NULL);
	i = getdpsize(str);
	dup = ft_calloc(sizeof(char *), i + 1);
	if (!dup)
		return (NULL);
	j = 0;
	while (str[j] != NULL)
	{
		dup[j] = ft_strdup(str[j]);
		if (!dup[j])
		{
			free_array(dup);
			return (dup);
		}
		j++;
	}
	return (dup);
}

char	*rem_allquotes(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (str == NULL || str[0] == '\0')
		return (NULL);
	while (str[i])
	{
		if (str[i] != '\"')
		{
			str[j] = str[i];
			j++;
		}
		i++;
	}
	str[j] = '\0';
	return (str);
}
