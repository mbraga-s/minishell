/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraga-s <mbraga-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 12:31:37 by mbraga-s          #+#    #+#             */
/*   Updated: 2024/02/22 14:06:32 by mbraga-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*rem_quotes(char *str);

char	*expand(char *str, char **envp);

// Checks if there are quoted or expandable strings

void	expander(t_data *current, char **envp)
{
	int	j;

	while (current)
	{
		j = 0;
		while (current->args && current->args[j])
		{
			if (current->args[j][0] == 34)
			{
				current->args[j] = rem_quotes(current->args[j]);
				current->args[j] = expand(current->args[j], envp);
			}
			else if (current->args[j][0] == 39)
				current->args[j] = rem_quotes(current->args[j]);
			else
				current->args[j] = expand(current->args[j], envp);
			j++;
		}
		current = current->next;
	}
}

// Removes quotes from the string by moving every character one position
// to the left and setting the last 2 to NULLs

char	*rem_quotes(char *str)
{
	int	i;
	int	len;

	len = ft_strlen(str);
	i = 0;
	if (!str)
		return (NULL);
	while (str[i] && i < (len - 2))
	{
		str[i] = str[i + 1];
		i++;
	}
	str[i++] = '\0';
	str[i++] = '\0';
	return (str);
}
