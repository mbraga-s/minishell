/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraga-s <mbraga-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 18:18:32 by mbraga-s          #+#    #+#             */
/*   Updated: 2024/03/05 19:30:20 by mbraga-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_pwd(void)
{
	char	cwd[PATH_MAX];

	getcwd(cwd, sizeof(cwd));
	if (cwd != NULL)
		printf("%s\n", cwd);
}

void	exec_cd(t_data *data)
{
	int	i;

	i = 0;
	while (data->args[i])
		i++;
	if (i <= 2)
	{
		if (!data->args[1] || !ft_strncmp(data->args[1], "--", 3))
			chdir(getenv("HOME"));
		else if (!ft_strncmp(data->args[1], "-", 2))
			chdir(getenv("OLDPWD"));
		else if (!access(data->args[1], F_OK))
			chdir(data->args[1]);
		else
			printf("cd : no such file or directory: %s\n", data->args[1]);
	}
	else
		printf("cd: too many arguments\n");
}

void	exec_exit(t_data *data)
{
	int	i;

	i = 0;
	g_data.status = 0;
	while (data->args[i])
		i++;
	printf("exit\n");
	if (i <= 2)
	{
		if (i == 2 && ft_strdigit(data->args[1]))
		{
			printf("exit : %s: numeric argument required\n", data->args[1]);
			g_data.status = 255;
		}
		else if (i == 2 && !ft_strdigit(data->args[1]))
		{
			g_data.status = ft_atoi(data->args[1]);
		}
		free_array(data->nenv);
		free_all(ft_lstfirst(data));
		exit(g_data.status);
	}
	else
		printf("exit: too many arguments\n");
}

void	exec_echo(t_data *data)
{
	int	newline;
	int	i;

	newline = 0;
	i = 0;
	while (data->args && data->args[i])
		i++;
	if (i > 1)
	{
		i = 1;
		if (!ft_strncmp(data->args[i], "-n", 2) && i++)
			newline = 1;
		while (data->args[i])
		{
			printf("%s", data->args[i]);
			i++;
			if (data->args[i])
				printf(" ");
		}
	}
	if (newline == 0)
		printf("\n");
}

void	exec_env(t_data *data)
{
	int	i;

	i = 0;
	if (data->args[1])
	{
		printf("env: '%s': No such file or directory", data->args[1]);
	}
	else
	{
		while (data->nenv[i])
		{
			printf("%s\n", data->nenv[i]);
			i++;
		}
	}
}


