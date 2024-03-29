/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manumart <manumart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 17:30:36 by mbraga-s          #+#    #+#             */
/*   Updated: 2024/03/07 04:26:47 by manumart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strdup(const char *s)
{
	char	*ptr;
	size_t	len;

	len = ft_strlen(s);
	ptr = ft_calloc(len + 1, sizeof (char));
	if (!ptr)
		return (NULL);
	ft_memcpy(ptr, s, len + 1);
	return (ptr);
}
