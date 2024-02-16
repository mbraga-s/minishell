/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraga-s <mbraga-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 17:54:25 by mbraga-s          #+#    #+#             */
/*   Updated: 2024/02/16 18:48:55 by mbraga-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	syn_error(char **tokens, int i)
{
	if (!tokens[i])
		printf("syntax error near unexpected token `newline'\n");
	else
		printf("syntax error near unexpected token `%s'\n", tokens[i]);
	free_tokens(tokens);
}

int	syntax_checker(char **tokens)
{
	int	i;

	i = 0;
	if (!ft_strncmp(tokens[i], "|", 2))
	{
		syn_error(tokens, i);
		return (0);
	}
	while (tokens && tokens[i])
	{
		if ((!ft_strncmp(tokens[i], "<", 2)) && ++i)
		{
			if (!tokens[i] || (!ft_strncmp(tokens[i], "|", 2)) || \
				(!ft_strncmp(tokens[i], ">", 1)) || \
				(!ft_strncmp(tokens[i], "<", 1)))
			{
				syn_error(tokens, (i));
				return (0);
			}
		}
		else if ((!ft_strncmp(tokens[i], ">", 2)) && ++i)
		{
			if (!tokens[i] || (!ft_strncmp(tokens[i], "|", 2)) || \
				(!ft_strncmp(tokens[i], ">", 1)) || \
				(!ft_strncmp(tokens[i], "<", 1)))
			{
				syn_error(tokens, (i));
				return (0);
			}
		}
		else if ((!ft_strncmp(tokens[i], "<<", 3)) && ++i)
		{
			if (!tokens[i] || (!ft_strncmp(tokens[i], "|", 2)) || \
				(!ft_strncmp(tokens[i], ">", 1)) || \
				(!ft_strncmp(tokens[i], "<", 1)))
			{
				syn_error(tokens, (i));
				return (0);
			}
		}
		else if ((!ft_strncmp(tokens[i], ">>", 3)) && ++i)
		{
			if (!tokens[i] || (!ft_strncmp(tokens[i], "|", 2)) || \
				(!ft_strncmp(tokens[i], ">", 1)) || \
				(!ft_strncmp(tokens[i], "<", 1)))
			{
				syn_error(tokens, (i));
				return (0);
			}
		}
		else if ((!ft_strncmp(tokens[i], "|", 2)) && ++i)
		{
			if (!tokens[i] || (!ft_strncmp(tokens[i], "|", 2)))
			{
				syn_error(tokens, (i));
				return (0);
			}
		}
		else
			i++;
	}
	return (1);
}
