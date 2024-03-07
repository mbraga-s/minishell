/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manumart <manumart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 16:36:35 by mbraga-s          #+#    #+#             */
/*   Updated: 2024/03/07 04:25:55 by manumart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	char	*ptr;

	ptr = (char *)s;
	i = ft_strlen(ptr) + 1;
	while (i--)
	{
		if (*(ptr) == (char)c)
		{
			return (ptr);
		}
		ptr++;
	}
	return (0);
}

/*int	main(void)
{
	const char	*ptr;
	char		*str;
	int			c;

	c = 'i';
	ptr = "Isto e muito fixe moco";
	str = ft_strchr(ptr, c);

	printf("%s", str);
}
*/