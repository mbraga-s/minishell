/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraga-s <mbraga-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:30:04 by mbraga-s          #+#    #+#             */
/*   Updated: 2024/02/07 16:51:28 by mbraga-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//add_args - appends a string to an already existing array of strings

char	**add_args(char **args, char *token)
{
	int		i;
	int		len;
	char	**ptr;

	i = 0;
	len = 0;
	while (args && args[len])
		len++;
	ptr = ft_calloc((len + 2), sizeof(char *));
	if (!ptr)
		return (NULL);
	while (i < len)
	{
		ptr[i] = args[i];
		i++;
	}
	ptr[i] = ft_strdup(token);
	free(args);
	return (ptr);
}

//parser - takes the tokens given by lexer and assigns them to a linked list

t_data	*parser(char **token)
{
	t_data	*data;
	t_data	*current;
	int		i;

	i = 0;
	data = ft_lstnew();
	current = data;
	while (token[i])
	{
		while (token[i] && ft_strncmp(token[i], "|", 2))
		{
			if (!ft_strncmp(token[i], "<", 2))
			{
				i++;
				current->infile = ft_strdup(token[i]);
			}
			else if (!ft_strncmp(token[i], ">", 2))
			{
				i++;
				current->outfile = ft_strdup(token[i]);
			}
			else if (!current->cmd)
				current->cmd = ft_strdup(token[i]);
			else
				current->args = add_args(current->args, token[i]);
			i++;
		}
		if (token[i] && !ft_strncmp(token[i], "|", 2))
		{
			current->pipe_flag = 1;
			ft_lstadd_back(&current, ft_lstnew());
			current = current->next;
			i++;
		}
	}
	return (data);
}
