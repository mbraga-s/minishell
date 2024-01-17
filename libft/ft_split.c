/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraga-s <mbraga-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 19:34:57 by mbraga-s          #+#    #+#             */
/*   Updated: 2024/01/17 16:11:55 by mbraga-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	inv_comma(char const *ptr, int i, char c)
{
	int	count;

	count = 0;
	while (ptr[++i])
	{
		if (ptr[i] == c)
			break ;
		count++;
	}
	return (count);
}

int	ft_wcount(char const *s, char c)
{
	int	i;
	int	sep;
	int	count;

	i = 0;
	sep = 1;
	count = 0;
	while (s[i])
	{
		if (s[i] == 34 || s[i] == 39)
			i = i + 1 + inv_comma(s, i, s[i]);
		if (s[i] == c)
			sep = 1;
		if (sep == 1 && s[i] != c)
		{
			count++;
			sep = 0;
		}
		i++;
	}
	return (count);
}

int	ft_wlen(char const *s, char c, int i)
{
	int	len;

	len = 0;
	while (s[i] && s[i] != c)
	{
		i++;
		len++;
	}
	return (len);
}

char	**ft_split(char const *s, char c)
{
	char	**ptr;
	int		i;
	int		j;
	int		k;

	i = 0;
	k = 0;
	ptr = (char **)ft_calloc(ft_wcount(s, c) + 1, sizeof(char *));
	if (!ptr)
		return (NULL);
	while (s[i] && (k < ft_wcount(s, c)))
	{
		while (s[i] == c)
			i++;
		if (s[i] == 34 || s[i] == 39)
		{
			j = inv_comma(s, i, s[i]);
			i++;
			ptr[k] = ft_substr(s, i, j);
			i = i + j + 1;
		}
		else
		{
			j = ft_wlen(s, c, i);
			ptr[k] = ft_substr(s, i, j);
			i = i + j;
		}
		k++;
	}
	return (ptr);
}

/* int	main(int argc, char **argv)
{
	int		i;
	char	**ptr;

	i = 0;
	if (argc == 2)
	{
		ptr = ft_split(argv[1], ' ');
		while (ptr[i])
		{
			printf("%s\n", ptr[i]);
			free (ptr[i]);
			i++;
		}
		free (ptr);
 		//i = ft_wcount(argv[1], ' ');
		//printf("words = %d\n", i);
	}
	return (0);
} */
