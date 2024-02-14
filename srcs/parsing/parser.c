/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraga-s <mbraga-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:30:04 by mbraga-s          #+#    #+#             */
/*   Updated: 2024/02/14 16:35:54 by mbraga-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
	int		i;

	i = 0;
	data = ft_lstnew();
	while (token[i])
	{
		while (token[i] && ft_strncmp(token[i], "|", 2))
		{
			if (!ft_strncmp(token[i], "<", 2) && ++i)
				data->infile = ft_strdup(token[i]);
			else if (!ft_strncmp(token[i], ">", 2) && ++i)
				data->outfile = ft_strdup(token[i]);
			else
				data->args = add_args(data->args, token[i]);
			i++;
		}
		if (token[i] && !ft_strncmp(token[i], "|", 2))
		{
			data = ft_lstadd_back(&data, ft_lstnew());
			i++;
		}
	}
	free_tokens(token);
	return (ft_lstfirst(data));
}
