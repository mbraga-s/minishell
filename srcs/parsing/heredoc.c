/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraga-s <mbraga-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 18:07:27 by mbraga-s          #+#    #+#             */
/*   Updated: 2024/04/03 12:48:44 by mbraga-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	input_error(int pipe_fds[2], t_data *data)
{
	ft_putstr(2, "warning: here-document delimited by EOF.\n");
	close_fd(pipe_fds);
	data = ft_lstfirst(data);
	free_all(data);
	free_array(msdata()->envp);
	exit(1);
}

void	ft_here_fork(char *str, int pipe_fds[2], t_data *data)
{
	char	*input;

	while (1)
	{
		input = get_next_line(0);
		if (!input)
			input_error(pipe_fds, data);
		input = rem_quotes(expand(input, msdata()->envp));
		if (!ft_strncmp(input, str, (ft_strlen(str))) 
			&& (ft_strlen(input) - 1 == ft_strlen(str)))
			break ;
		write(pipe_fds[1], input, ft_strlen(input));
		free(input);
	}
	close_fd(pipe_fds);
	free(input);
	data = ft_lstfirst(data);
	free_all(data);
	free_array(msdata()->envp);
	exit(0);
}

//Opens a pipe as a way to write to a process and writes the input to it.
//Returns the read end of the pipe.
int	ft_heredoc(char *str, t_data *data)
{
	int	pid;
	int	fd[2];
	int	status;

	status = 0;
	msdata()->here_flag = 1;
	signal(SIGINT, sigheredochandler);
	if (pipe(fd) == -1)
		return (perror(NULL), 0);
	pid = fork();
	if (pid == 0)
		ft_here_fork(str, fd, data);
	waitpid(pid, &status, 0);
	close(fd[1]);
	msdata()->here_flag = 0;
	return (fd[0]);
}
