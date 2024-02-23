/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraga-s <mbraga-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 18:07:27 by mbraga-s          #+#    #+#             */
/*   Updated: 2024/02/23 14:18:34 by mbraga-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	openhdoc(char *str)
{
	int	fd[2];

	if (pipe(fd) == -1)
	{
		perror(NULL);
		return (0);
	}
	write(fd[1], str, ft_strlen(str));
	close(fd[1]);
	return (fd[0]);
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
	if (!ptr)
		ptr = ft_strdup("");
	return (ptr);
}
