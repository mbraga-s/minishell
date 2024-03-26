/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraga-s <mbraga-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 18:07:27 by mbraga-s          #+#    #+#             */
/*   Updated: 2024/03/26 17:30:22 by mbraga-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//Opens a pipe as a way to write to a process and writes the input to it.
//Returns the read end of the pipe.
int	ft_heredoc(char *str)
{
	char	*input;
	int		fd[2];

	if (pipe(fd) == -1)
	{
		perror(NULL);
		return (0);
	}
	input = NULL;
	signal(SIGQUIT, sigquithandler);
	signal(SIGINT, sigheredochandler);
	input = readline("> ");
	while (ft_strncmp(input, str, (ft_strlen(str) + 1)))
	{
		free(input);
		input = readline("> ");
		input = expand(input, msdata()->envp);
		input = rem_quotes(input);
		write(fd[1], input, ft_strlen(input));
	}
	write(fd[1], "\n", 1);
	close(fd[1]);
	free(input);
	return (fd[0]);
}
