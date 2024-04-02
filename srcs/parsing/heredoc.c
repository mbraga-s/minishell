/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraga-s <mbraga-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 18:07:27 by mbraga-s          #+#    #+#             */
/*   Updated: 2024/04/02 18:25:57 by mbraga-s         ###   ########.fr       */
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

	msdata()->here_flag = 1;
	if (pipe(fd) == -1)
		return (perror(NULL), 0);
	signal(SIGINT, sigheredochandler);
	while (1)
	{
		input = get_next_line(0);
		if (!input)
			input_error();
		input = rem_quotes(expand(input, msdata()->envp));
		if (!ft_strncmp(input, str, (ft_strlen(str))) 
			&& (ft_strlen(input) - 1 == ft_strlen(str)))
			break ;
		write(fd[1], input, ft_strlen(input));
		free(input);
	}
	close(fd[1]);
	free(input);
	msdata()->here_flag = 0;
	return (fd[0]);
}
