/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraga-s <mbraga-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 12:31:02 by mbraga-s          #+#    #+#             */
/*   Updated: 2024/02/12 01:09:31 by mbraga-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*pathtest(char *env, char *arg);

int		pcheck(char *ptr);

void	mid_fork(t_data *data, char **envp, int **fds, int flag);

void	first_fork(t_data *data, char **envp, int *fd);

void	last_fork(t_data *data, char **envp, int *fd);

void	close_fd(int *fd)
{
	close(fd[0]);
	close(fd[1]);
}

int	dupcheck(int file_fd, int fd)
{
	int	i;

	i = dup2(file_fd, fd);
	if (i == -1)
		exit(1);
	return (i);
}

char	*check_path(char *arg, char **envp)
{
	int		i;
	char	*env;
	char	*path;

	i = 0;
	env = NULL;
	if (!arg)
		printf("command not found: %s\n", arg);
	else if (pcheck(arg) == 0)
	{
		while (envp[i])
		{
			if (!ft_strncmp("PATH=", envp[i], 5))
			{
				env = envp[i] + 5;
				break ;
			}
			i++;
		}
		path = pathtest(env, arg);
		if (path != NULL)
			return (path);
		free(path);
	}
	return (ft_strdup(arg));
}

char	*pathtest(char *env, char *arg)
{
	int		i;
	char	**ptr;
	char	*path;

	i = 0;
	ptr = ft_split(env, ':');
	while (ptr[i])
	{
		path = ft_strjoin(ptr[i], "/");
		path = ft_strjoin(path, arg);
		if (access(path, X_OK) == 0)
		{
			return (path);
			break ;
		}
		free(path);
		i++;
	}
	printf("command not found: %s\n", arg);
	free(ptr);
	return (NULL);
}

int	pcheck(char *ptr)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (ptr[i])
	{
		if (ptr[i] == '/')
		{
			flag = 1;
			break ;
		}
		i++;
	}
	return (flag);
}

void	execution(t_data *data, char **envp)
{
	int		*fds[2];
	int		fd1[2];
	int		fd2[2];
	int		pid[2];
	int		flag;

	fds[0] = fd1;
	fds[1] = fd2;
	flag = 1;
	fd1[0] = 0;
	fd1[1] = 1;
	if (data->next)
	{
		if (pipe(fd1) == -1)
		{
			perror(NULL);
			exit(1);
		}
	}
	pid[0] = fork();
	if (pid[0] == 0)
		first_fork(data, envp, fd1);
	data = data->next;
	while (data && data->next)
	{
		if (pipe(fds[flag]) == -1)
		{
			perror(NULL);
			exit(1);
		}
		pid[1] = fork();
		if (pid[1] == 0)
			mid_fork(data, envp, fds, flag);
		if (flag == 1)
			flag = 0;
		else
			flag = 1;
		close_fd(fds[flag]);
		data = data->next;
	}
	if (data)
	{
		if (flag == 1)
			flag = 0;
		else
			flag = 1;
		pid[1] = fork();
		last_fork(data, envp, fds[flag]);
		close_fd(fds[flag]);
	}
}

void	mid_fork(t_data *data, char **envp, int **fds, int flag)
{
	char	*path;
	int		i;
	int		dups[2];

	i = 0;
	if (flag == 0)
		i = 1;
	path = check_path(data->cmd, envp);
	dups[0] = dupcheck(fds[i][0], 0);
	dups[1] = dupcheck(fds[flag][1], 1);
	close_fd(fds[flag]);
	close_fd(fds[i]);
	if (path)
		execve(path, data->args, envp);
	close_fd(dups);
	free(path);
	exit(1);
}

void	first_fork(t_data *data, char **envp, int *fd)
{
	char	*path;
	int		dups[2];

	path = check_path(data->cmd, envp);
	if (fd[0] != 0)
	{
		printf ("fd");
		dups[1] = dupcheck(fd[1], 1);
		close_fd(fd);
	}
	if (data->infile)
	{
		fd[0] =  open(data->infile, O_RDONLY);
		if (fd[0] < 0)
		{
			perror(data->infile);
			fd[0] = open("temp", O_CREAT, 0644);
		}
		dups[0] = dupcheck(fd[0], 0);
		close(fd[0]);
	}
	if (path)
		execve(path, data->args, envp);
	close_fd(dups);
	free(path);
	exit(1);
}

void	last_fork(t_data *data, char **envp, int *fd)
{
	char	*path;
	int		dups[2];

	path = check_path(data->cmd, envp);
	if (fd)
	{
		dups[1] = dupcheck(fd[0], 0);
		close_fd(fd);
	}
	if (data->outfile)
	{
		fd[1] =  open(data->outfile, O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (fd[1] < 0)
		{
			perror(data->outfile);
			exit(1);
		}
		dups[0] = dupcheck(fd[1], 1);
		close(fd[1]);
	}
	if (path)
		execve(path, data->args, envp);
	close_fd(dups);
	free(path);
	exit(1);
}
