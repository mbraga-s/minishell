/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraga-s <mbraga-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 12:31:02 by mbraga-s          #+#    #+#             */
/*   Updated: 2024/03/18 16:32:38 by mbraga-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//Creates an array with the names of each built-in function
//to use in a smaller checker for those strings.
char	**builtin_buffer(void)
{
	int		i;
	char	**array;

	i = 0;
	array = ft_calloc(8, sizeof(char *));
	if (!array)
		return (NULL);
	array[i] = ft_strdup("cd"); // int 0
	array[++i] = ft_strdup("echo"); // int 1
	array[++i] = ft_strdup("env"); // int 2
	array[++i] = ft_strdup("exit"); // int 3
	array[++i] = ft_strdup("export"); // int 4
	array[++i] = ft_strdup("pwd"); // int 5
	array[++i] = ft_strdup("unset"); // int 6
	array[++i] = NULL;
	return (array);
}

//Runs the required built-in function
void	run_builtin(int i, t_data *data, int fd)
{
	if (i == 0)
		exec_cd(data, fd);
	else if (i == 1)
		exec_echo(data, fd);
	else if (i == 2)
		exec_env(data, fd);
	else if (i == 3)
		exec_exit(data);
	else if (i == 4)
		exec_export(data, fd);
	else if (i == 5)
		exec_pwd(fd);
	else if (i == 6)
		exec_unset(data);
}

// Checks if the cmd given is one of the built-ins and, if it is, runs it
int	check_builtin(t_data *data, int fd)
{
	char	**buffer;
	int		i;

	i = 0;
	if (!(data->args) || !(data->args[0]))
		return (0);
	buffer = builtin_buffer();
	while (buffer && buffer[i])
	{
		if (!ft_strncmp(data->args[0], buffer[i], (ft_strlen(buffer[i]) + 1)))
			break ;
		i++;
	}
	free_array(buffer);
	if (i == 7)
		return (0);
	run_builtin(i, data, fd);
	return (1);
}

//Checks if a function is a built-in by comparing it with the builtin buffer.
//If it is a built-in, returns 1. Returns 0 if it isn't. 
int	is_builtin(t_data *data)
{
	int		i;
	char	**buffer;

	i = 0;
	buffer = NULL;
	if (data->args && data->args[0])
	{
		buffer = builtin_buffer();
		while (buffer && buffer[i])
		{
			if (!ft_strncmp(data->args[0], buffer[i], (ft_strlen(buffer[i]) + 1)))
			{
				free_array(buffer);
				return (1);
			}
			i++;
		}
	}
	free_array(buffer);
	return (0);
}

void	execution(t_data *data)
{
	t_data	*current;
	int		status;
	int		btn_fd;

	status = 0;
	current = data;
	if (data->next)
	{
		if (pipe(data->fd) == -1)
		{
			perror(NULL);
			exit(1);
		}
	}
	else if (is_builtin(data))
	{
		btn_fd = btn_redirect(data);
		if (btn_fd == 0)
		{
			g_data.status = 1;
			return ;
		}
		check_builtin(data, btn_fd);
		if (btn_fd > 2)
			close(btn_fd);
		return ;
	}
	data->pid = fork();
	if (data->pid == 0)
		first_fork(data, msdata()->envp);
	data = data->next;
	while (data && data->next)
	{
		if (pipe(data->fd) == -1)
		{
			perror(NULL);
			exit(1);
		}
		data->pid = fork();
		if (data->pid == 0)
			mid_fork(data, msdata()->envp);
		close_fd(data->prev->fd);
		data = data->next;
	}
	if (data)
	{
		data->pid = fork();
		if (data->pid == 0)
			last_fork(data, msdata()->envp);
		close_fd(data->prev->fd);
	}
	while (current)
	{
		waitpid(current->pid, &status, 0);
		if (WIFEXITED(status))
			g_data.status = WEXITSTATUS(status);
		current = current->next;
	}
}
