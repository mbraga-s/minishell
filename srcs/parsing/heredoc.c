/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraga-s <mbraga-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 18:07:27 by mbraga-s          #+#    #+#             */
/*   Updated: 2024/04/12 15:29:59 by mbraga-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//Error handling if an EOF is passed (Ctrl + D)
void	input_error(int pipe_fds[2], t_data *data)
{
	ft_putstr(2, "warning: here-document delimited by EOF.\n");
	close_fd(pipe_fds);
	data = ft_lstfirst(data);
	free_all(data);
	free_array(msdata()->envp);
	exit(1);
}

//Runs the loop for here_doc inside it's own fork.
void	ft_here_fork(char *str, int pipe_fds[2], t_data *data)
{
	char	*input;

	signal(SIGINT, siginthd);
	close_all(data);
	while (1)
	{
		input = readline("> ");
		if (!input)
			input_error(pipe_fds, data);
		input = rem_quotes(expand(input, msdata()->envp));
		if (!ft_strncmp(input, str, (ft_strlen(str)))
			&& (ft_strlen(input) == ft_strlen(str)))
			break ;
		write(pipe_fds[1], input, ft_strlen(input));
		write(pipe_fds[1], "\n", 1);
		free(input);
	}
	close_fd(pipe_fds);
	free(input);
	free_all(msdata()->strut);
	free_array(msdata()->envp);
	exit(g_data.status);
}

//Opens a pipe as a way to write to a process and writes the input to it.
//Returns the read end of the pipe.
int	ft_heredoc(char *str, t_data *data)
{
	int	pid;
	int	fd[2];
	int	status;

	status = 0;
	if (pipe(fd) == -1)
		return (perror(NULL), 0);
	pid = fork();
	if (pid == 0)
		ft_here_fork(str, fd, data);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
	{
		g_data.status = WEXITSTATUS(status);
		close_fd(fd);
		msdata()->hd_signal = 1;
		return (-2);
	}
	close(fd[1]);
	return (fd[0]);
}
