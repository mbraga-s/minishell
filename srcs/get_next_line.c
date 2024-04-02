/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraga-s <mbraga-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 19:29:41 by mbraga-s          #+#    #+#             */
/*   Updated: 2024/04/02 12:36:04 by mbraga-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_clean(char *ptr)
{
	int	i;
	int	j;
	int	flag;

	i = 0;
	j = 0;
	flag = 0;
	while (ptr && ptr[i])
	{
		if (flag == 1)
		{
			ptr[j] = ptr[i];
			j++;
		}
		if (ptr[i] == '\n')
			flag = 1;
		ptr[i] = '\0';
		i++;
	}
	return (flag);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	stash[BUFFER_SIZE + 1];
	int			i;

	i = 0;
	line = 0;
	stash[BUFFER_SIZE] = '\0';
	write(0, "> ", 2);
	if (BUFFER_SIZE < 1)
	{
		while (stash[i])
			stash[i++] = 0;
		return (0);
	}
	while (stash[0] || read(fd, stash, BUFFER_SIZE) > 0)
	{
		line = ft_strjoin(line, stash);
		if (ft_clean(stash))
			break ;
	}
	return (line);
}
