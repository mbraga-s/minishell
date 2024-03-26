/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manumart <manumart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 07:09:06 by manumart          #+#    #+#             */
/*   Updated: 2024/03/26 15:35:57 by manumart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*findvariableinenv(char *var)
{
	int		i;
	char	*temp;
	char	*temp2;

	i = 0;
	while (msdata()->envp && msdata()->envp[i])
	{
		if (!ft_strncmp(msdata()->envp[i], var, ft_strlen(var)))
		{
			temp = ft_strchr(msdata()->envp[i], '=');
			temp2 = ft_strdup(temp + 1);
			return (temp2);
		}
		i++;
	}
	return (NULL);
}

void	updatepaths(char *PWD, char *OLDPWD)
{
	int	i;

	i = 0;
	while (msdata()->envp && msdata()->envp[i] != NULL)
	{
		if (!ft_strncmp(msdata()->envp[i], "PWD", 3))
		{
			free(msdata()->envp[i]);
			(msdata()->envp)[i] = ft_stjnf("PWD=", PWD);
		}
		else if (!ft_strncmp(msdata()->envp[i], "OLDPWD", 6))
		{
			free((msdata()->envp)[i]);
			(msdata()->envp)[i] = ft_stjnf("OLDPWD=", OLDPWD);
		}
		i++;
	}
	if (!findvariableinenv("PWD"))
		(msdata()->envp) = add_args(msdata()->envp, ft_stjnf("PWD=", PWD));
	if (!findvariableinenv("OLDPWD"))
		(msdata()->envp) = add_args(msdata()->envp, ft_stjnf("OLDPWD=",
					OLDPWD));
}

void	chdirandupdate(char *path)
{
	char	oldpwd[PATH_MAX];
	char	pwd[PATH_MAX];

	getcwd(oldpwd, sizeof(oldpwd));
	if (chdir(path) != 0)
	{
		perror("chdir");
		return ;
	}
	getcwd(pwd, sizeof(pwd));
	updatepaths(pwd, oldpwd);
}

void	cderror(char *path)
{
	ft_putstr(2, "cd : ");
	if (!ft_strncmp(path, "-", 2))
		ft_putstr(2, "OLDPWD not set\n");
	else
	{
		ft_putstr(2, path);
		ft_putstr(2, ": No such file or directory\n");
	}
}

void	exec_cd(t_data *data, int fd)
{
	int	i;

	i = 0;
	while (data->args[i])
		i++;
	if (i <= 2)
	{
		if (!data->args[1] || !ft_strncmp(data->args[1], "--", 3))
			chdirandupdate(findvariableinenv("HOME"));
		else if (!ft_strncmp(data->args[1], "-", 2)
			&& findvariableinenv("OLDPWD"))
		{
			chdirandupdate(findvariableinenv("OLDPWD"));
			ft_putstr(fd, findvariableinenv("OLDPWD"));
			write(fd, "\n", 1);
		}
		else if (!access(data->args[1], F_OK))
			chdirandupdate(data->args[1]);
		else
			cderror(data->args[1]);
	}
	else
		ft_putstr(2, "cd: too many arguments\n");
}
