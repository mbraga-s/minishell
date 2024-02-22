/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraga-s <mbraga-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 18:07:27 by mbraga-s          #+#    #+#             */
/*   Updated: 2024/02/22 20:11:02 by mbraga-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	openhdoc(char *str)
{
	int	fd;

	fd = open(".", __O_TMPFILE | O_RDWR);
	write(fd, str, ft_strlen(str));
	return (fd);
}

char	*ft_heredoc(char *str)
{
	char	*ptr;
	char	*input;

	ptr = NULL;
	input = NULL;
	input = readline("> ");
	while (ft_strncmp(input, str, (ft_strlen(str) + 1)))
	{
		ptr = ft_strjoin(ptr, input);
		free (input);
		ptr = ft_strjoin(ptr, "\n");
		input = readline("> ");
	}
	free(input);
	return (ptr);
}
