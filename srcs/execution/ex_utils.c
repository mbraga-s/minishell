/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraga-s <mbraga-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 16:45:54 by mbraga-s          #+#    #+#             */
/*   Updated: 2024/02/12 16:55:23 by mbraga-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
