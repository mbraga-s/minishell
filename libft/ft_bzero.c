/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraga-s <mbraga-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 16:01:20 by mbraga-s          #+#    #+#             */
/*   Updated: 2024/01/12 14:19:37 by mbraga-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_bzero(void *s, size_t n)
{
	char	*ptr;
	int		i;

	ptr = s;
	i = 0;
	while (n > 0)
	{
		ptr[i] = '\0';
		i++;
		n--;
	}
}

/*int	main(void)
{
	char a[5] = "Hello";

	printf("%s", a);
	ft_bzero(a, 5);
	printf("%s", a);
}
*/