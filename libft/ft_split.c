/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manumart <manumart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 19:34:57 by mbraga-s          #+#    #+#             */
/*   Updated: 2024/03/27 17:30:03 by manumart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// inv_comma- runs the string when the first " or ' is found until the next one.
int	inv_comma(char const *ptr, int i, char c)
{
	int	count;
	int	flag;

	count = 0;
	flag = 0;
	while (ptr[++i])
	{
		if (ptr[i] == c)
		{
			flag = 1;
			break ;
		}
		count++;
	}
	if (flag == 1)
		return (count);
	else
		return (0);
}

// ft_wcount - counts number of words in the string using char c as separator
// and running inv_comma when " or ' is found to skip that part.
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

// ft_wlen - counts the size of the word, using char c (separator) as end point.
int	ft_wlen(char const *s, char c, int i)
{
	int	len;

	len = 0;
	while (s[i] && s[i] != c)
	{
		if (s[i] == 34 || s[i] == 39)
		{
			len = len + inv_comma(s, i, s[i]) + 1;
			i = i + inv_comma(s, i, s[i]) + 1;
		}
		i++;
		len++;
	}
	return (len);
}

// ft_split - breaks the string into several using char c as separator and
// using inv_comma to respect " and ' functionality.
// Check earlier versions of this function to better understand what's happening
// because to follow norm, code had to become a bit spaghetti
char	**ft_split(char const *s, char c)
{
	char	**ptr;
	int		i;
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
		ptr[k++] = ft_substr(s, i, ft_wlen(s, c, i));
		i = i + ft_wlen(s, c, i);
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
