/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manumart <manumart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 16:51:40 by mbraga-s          #+#    #+#             */
/*   Updated: 2024/03/07 04:46:04 by manumart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	ptr1;
	unsigned char	ptr2;
	size_t			i;

	i = 0;
	if (n == 0 || !s1 || !s2)
		return (0);
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0' && i < n)
		i++;
	if (i == n)
		i--;
	ptr1 = s1[i];
	ptr2 = s2[i];
	return (ptr1 - ptr2);
}

/*int	main(void)
{
	char	*a;
	char	*b;
	int		i;
	int		f;

	a = "Hillo";
	b = "Hello";
	i = ft_strncmp(a, b, 3);
	printf("\nft_strncmp result: %d\n", i);
	f = strncmp(a, b, 3);
	printf("strncmp result: %d\n", f);
}
*/