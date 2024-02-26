/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraga-s <mbraga-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 17:54:25 by mbraga-s          #+#    #+#             */
/*   Updated: 2024/02/26 15:01:42 by mbraga-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	syn_error(char **tokens, int i)
{
	if (!tokens[i])
		printf("syntax error near unexpected token `newline'\n");
	else
		printf("syntax error near unexpected token `%s'\n", tokens[i]);
	g_data.status = 2;
	free_tokens(tokens);
}

int	syntax_part1(char **tokens, int *i)
{
	if ((!ft_strncmp(tokens[*i], "<", 2)) && ++*i)
	{
		if (!tokens[*i] || (!ft_strncmp(tokens[*i], "|", 2)) || \
			(!ft_strncmp(tokens[*i], ">", 1)) || \
			(!ft_strncmp(tokens[*i], "<", 1)))
		{
			syn_error(tokens, (*i));
			return (0);
		}
	}
	else if ((!ft_strncmp(tokens[*i], ">", 2)) && ++*i)
	{
		if (!tokens[*i] || (!ft_strncmp(tokens[*i], "|", 2)) || \
			(!ft_strncmp(tokens[*i], ">", 1)) || \
			(!ft_strncmp(tokens[*i], "<", 1)))
		{
			syn_error(tokens, (*i));
			return (0);
		}
	}
	return (1);
}

int	syntax_part2(char **tokens, int *i)
{
	if ((!ft_strncmp(tokens[*i], "<<", 3)) && ++*i)
	{
		if (!tokens[*i] || (!ft_strncmp(tokens[*i], "|", 2)) || \
			(!ft_strncmp(tokens[*i], ">", 1)) || \
			(!ft_strncmp(tokens[*i], "<", 1)))
		{
			syn_error(tokens, (*i));
			return (0);
		}
	}
	else if ((!ft_strncmp(tokens[*i], ">>", 3)) && ++*i)
	{
		if (!tokens[*i] || (!ft_strncmp(tokens[*i], "|", 2)) || \
			(!ft_strncmp(tokens[*i], ">", 1)) || \
			(!ft_strncmp(tokens[*i], "<", 1)))
		{
			syn_error(tokens, (*i));
			return (0);
		}
	}
	return (1);
}

int	syntax_part3(char **tokens, int *i)
{
	if ((!ft_strncmp(tokens[*i], "|", 2)) && ++*i)
	{
		if (!tokens[*i] || (!ft_strncmp(tokens[*i], "|", 2)))
		{
			syn_error(tokens, (*i));
			return (0);
		}
	}
	return (1);
}

int	syntax_checker(char **tokens)
{
	int	i;

	i = 0;
	if (!tokens || !tokens[i])
	{
		free_tokens(tokens);
		return (0);
	}
	if (!ft_strncmp(tokens[i], "|", 2))
	{
		syn_error(tokens, i);
		return (0);
	}
	while (tokens && tokens[i])
	{
		if (!syntax_part1(tokens, &i))
			return (0);
		else if (!syntax_part2(tokens, &i))
			return (0);
		else if (!syntax_part3(tokens, &i))
			return (0);
		else
			i++;
	}
	return (1);
}
