/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraga-s <mbraga-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 11:59:31 by mbraga-s          #+#    #+#             */
/*   Updated: 2024/01/12 16:08:02 by mbraga-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_op(char *str)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '|' || str[i] == '<' || str[i] == '>')
			count++;
		i++;
	}
	return (count);
}

char	*alloc_sep(char *str)
{
	int		len;
	int		count;
	char	*ptr;

	count = count_op(str);
	len = ft_strlen(str);
	ptr = ft_calloc((len + (count * 2) + 1), sizeof(char));
	if (!ptr)
		return (NULL);
	return (ptr);
}

char	*separate(char *str)
{
	int		i;
	int		j;
	char	*ptr;

	i = 0;
	j = 0;
	ptr = alloc_sep(str);
	while (str[i])
	{
		if (str[i] == '|' || str[i] == '<' || str[i] == '>')
		{
			ptr[j++] = ' ';
			ptr[j++] = str[i];
			if ((str[i] == '<' && str[i + 1] == '<') || \
				(str[i] == '>' && str[i + 1] == '>'))
				ptr[j++] = str[++i];
			ptr[j] = ' ';
		}
		else
			ptr[j] = str[i];
		j++;
		i++;
	}
	ptr[j] = '\0';
	return (ptr);
}

char	**lexer(char *str)
{
	char	*sep;
	char	**lex;

	sep = separate(str);
	lex = ft_split(sep, ' ');
	free (sep);
	return (lex);
}

int	main(int argc, char **argv)
{
	char	**lex;
	int		i;

	i = 0;
	lex = NULL;
	if (argc == 2)
	{
		lex = lexer(argv[1]);
		while (lex[i])
		{
			printf("%s\n", lex[i]);
			i++;
		}
		i = 0;
		while (lex[i])
		{
			free(lex[i]);
			i++;
		}
		free(lex);
	}
	return (0);
}
