/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraga-s <mbraga-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 12:31:37 by mbraga-s          #+#    #+#             */
/*   Updated: 2024/03/15 19:00:57 by mbraga-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*rem_quotes(char *str);

char	*expand(char *str, char **envp);

//Checks if an arguments becomes a NULL after expanding.
//ex: "$VAR" and removes it from the args list.
void	check_args(char **args, int pos)
{
	if (args[pos] && args[pos][0] == '\0')
	{
		free(args[pos]);
		while (args[pos + 1])
		{
			args[pos] = args[pos + 1];
			pos++;
		}
		args[pos] = NULL;
	}
}

// Checks if there are quoted or expandable strings.
void	expander(t_data *current)
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
				current->args[j] = expand(current->args[j], msdata()->envp);
				check_args(current->args, j);
			}
			else if (current->args[j][0] == 39)
				current->args[j] = rem_quotes(current->args[j]);
			else
			{
				current->args[j] = expand(current->args[j], msdata()->envp);
				check_args(current->args, j);
			}
			j++;
		}
		current = current->next;
	}
}

// Removes quotes from the string by moving every character one position
// to the left and setting the last 2 to NULLs.
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
