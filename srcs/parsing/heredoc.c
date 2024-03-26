/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraga-s <mbraga-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 18:07:27 by mbraga-s          #+#    #+#             */
/*   Updated: 2024/03/26 18:40:05 by mbraga-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	input_error(void)
{
	ft_putstr(2, "warning: here-document delimited by EOF.\n");
	exit(0);
}

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
	signal(SIGINT, sigheredochandler);
	input = readline("> ");
	if (!input)
		input_error();
	while (ft_strncmp(input, str, (ft_strlen(str) + 1)))
	{
		write(fd[1], input, ft_strlen(input));
		free(input);
		input = readline("> ");
		if (!input)
			input_error();
		input = rem_quotes(expand(input, msdata()->envp));
		write(fd[1], "\n", 1);
	}
	close(fd[1]);
	free(input);
	return (fd[0]);
}
