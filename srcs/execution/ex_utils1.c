/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_utils1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraga-s <mbraga-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 16:45:54 by mbraga-s          #+#    #+#             */
/*   Updated: 2024/04/11 00:29:50 by mbraga-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*pathtest(char *env, char *arg);

int		pcheck(char *ptr);

//Closes a pair of file descriptors
void	close_fd(int *fd)
{
	close(fd[0]);
	close(fd[1]);
}

//Protection for the dup2 command (separated from code to save lines)
int	dupcheck(int file_fd, int fd)
{
	int	i;

	i = dup2(file_fd, fd);
	if (i == -1)
	{
		perror(NULL);
		free_all(msdata()->strut);
		free_array(msdata()->envp);
		i = -1;
		while (++i < FOPEN_MAX)
			close(i);
		exit(1);
	}
	return (i);
}

//Runs through the environment variables looking for PATH.
char	*check_path(char *arg, char **envp)
{
	int		i;
	char	*env;
	char	*path;

	i = 0;
	env = NULL;
	if (!arg)
		printf("%s: command not found\n", arg);
	else if (pcheck(arg) == 0)
	{
		while (envp && envp[i])
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

//Goes through every path in PATH variable (from environment variables)
//and joins the cmd to it. Then it tries to access that path.
//If it succedes it returns that path otherwise it tries with the next.
char	*pathtest(char *env, char *arg)
{
	int		i;
	char	**ptr;
	char	*path;

	i = 0;
	ptr = NULL;
	if (env)
		ptr = ft_split(env, ':');
	while (ptr && ptr[i])
	{
		path = ft_strjoin(ptr[i], "/");
		path = ft_strjoin(path, arg);
		if (access(path, X_OK) == 0)
		{
			while (ptr && ptr[i++])
				free (ptr[i]);
			free(ptr);
			return (path);
		}
		free(path);
		i++;
	}
	free(ptr);
	return (NULL);
}

//Checks if the cmd given was already a path (if it had a /).
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
