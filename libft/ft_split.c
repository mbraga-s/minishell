/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraga-s <mbraga-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 19:34:57 by mbraga-s          #+#    #+#             */
/*   Updated: 2024/01/12 16:28:28 by mbraga-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_wcount(char const *s, char c)
{
	int	i;
	int	sep;
	int	flag;
	int	count;

	i = 0;
	sep = 1;
	flag = 0;
	count = 0;
	while (s[i++])
	{
		if (s[i] == 39 && flag == 0)
			flag = 1;
		else if (s[i] == 39 && flag == 1)
			flag = 0;
		else if (s[i] == c && flag == 0)
			sep = 1;
		else if (sep == 1 && s[i] != c && flag == 0)
		{
			count++;
			sep = 0;
		}
	}
	return (count);
}

int	ft_wlen(char const *s, char c, int i)
{
	int	len;

	len = 0;
	while (s[i] != c && s[i])
	{
		i++;
		len++;
	}
	return (len);
}

/* char	**ft_split(char const *s, char c)
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
		j = ft_wlen(s, c, i);
		ptr[k] = ft_substr(s, i, j);
		k++;
		i = i + j;
	}
	return (ptr);
} */

int	main(void)
{
	char *ptr = "Hello 'son of a bitch' im in.";
	int	i;

	i = ft_wcount(ptr, ' ');
	printf("%d\n", i);
	return (0);
}