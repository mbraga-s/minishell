/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraga-s <mbraga-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 12:31:37 by mbraga-s          #+#    #+#             */
/*   Updated: 2024/04/14 14:25:16 by mbraga-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*rem_quotes(char *str);

char	*expand(char *str, char **envp);

// Checks if an arguments becomes a NULL after expanding.
// ex: "$VAR" and removes it from the args list.
int	check_args(char **args, int pos)
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
		return (0);
	}
	else
		return (1);
}

// Part of the expander function in order to comply with norm
void	expander1(t_data *current)
{
	int	j;

	j = 0;
	while (current->infile && current->infile[j])
	{
		current->infile[j] = expand(current->infile[j], msdata()->envp);
		if (check_args(current->infile, j))
		{
			current->infile[j] = rem_quotes(current->infile[j]);
			j++;
		}
	}
	j = 0;
	while (current->outfile && current->outfile[j])
	{
		current->outfile[j] = expand(current->outfile[j], msdata()->envp);
		if (check_args(current->outfile, j))
		{
			current->outfile[j] = rem_quotes(current->outfile[j]);
			j++;
		}
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
			current->args[j] = expand(current->args[j], msdata()->envp);
			if (check_args(current->args, j))
			{
				current->args[j] = rem_quotes(current->args[j]);
				j++;
			}
		}
		expander1(current);
		current = current->next;
	}
}

// Removes quotes from the string by moving every character one position
// to the left and setting the last 2 to NULLs.
char	*rem_quotes(char *str)
{
	int		i;
	int		len;
	int		flag;
	char	*ptr;

	len = getunquotedlen(str);
	ptr = ft_calloc(len + 1, sizeof(char));
	i = 0;
	len = 0;
	flag = 0;
	while (str && str[i])
	{
		if ((str[i] == 34 || str[i] == 39) && flag == 0)
			flag = (int)str[i];
		else if ((str[i] == 34 && flag == 34) || (str[i] == 39 && flag == 39))
			flag = 0;
		else
		{
			ptr[len] = str[i];
			len++;
		}
		i++;
	}
	free(str);
	return (ptr);
}

// Returns the supposed len of a string after being unquoted.
int	getunquotedlen(char *str)
{
	int	len;
	int	flag;
	int	i;

	len = 0;
	i = 0;
	flag = 0;
	while (str && str[i])
	{
		if ((str[i] == 34 || str[i] == 39) && flag == 0)
			flag = (int)str[i];
		else if (str[i] == 34 && flag == 34)
		{
			len = len - 2;
			flag = 0;
		}
		else if (str[i] == 39 && flag == 39)
		{
			len = len - 2;
			flag = 0;
		}
		len++;
		i++;
	}
	return (len);
}
