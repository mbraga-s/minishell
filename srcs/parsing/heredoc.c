/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manumart <manumart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 18:07:27 by mbraga-s          #+#    #+#             */
/*   Updated: 2024/03/19 13:55:37 by manumart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//Opens a pipe as a way to write to a process and writes the given string to it.
//Returns the read end of the pipe.
int	openhdoc(char *str)
{
	int	fd[2];

	if (pipe(fd) == -1)
	{
		perror(NULL);
		return (0);
	}
	write(fd[1], str,ft_strlen(str));
	close(fd[1]);
	return (fd[0]);
}

//Requests input as an here-doc and saves it in a very long string.
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
