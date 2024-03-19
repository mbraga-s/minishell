/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manumart <manumart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 07:09:06 by manumart          #+#    #+#             */
/*   Updated: 2024/03/19 13:53:41 by manumart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*findvariableinenv(char *var)
{
	int		i;
	char	*temp;
	char	*temp2;

	i = 0;
	while (msdata()->envp[i])
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

void updatepaths(char *PWD, char *OLDPWD) 
{
    int i = 0;

    while (msdata()->envp[i] != NULL) 
	{
        if (!ft_strncmp(msdata()->envp[i], "PWD", 3)) 
		{
            free(msdata()->envp[i]);
            msdata()->envp[i] = ft_strjoinwofree("PWD=",PWD);
        }
        else if (!ft_strncmp(msdata()->envp[i], "OLDPWD", 6)) 
		{
            free(msdata()->envp[i]);
            msdata()->envp[i] = ft_strjoinwofree("OLDPWD=",OLDPWD);
        }
        i++;
    }
}

void chdirandupdate(char *path)
{
	char OLDPWD[PATH_MAX];
	char PWD[PATH_MAX];

	getcwd(OLDPWD, sizeof(OLDPWD));
	if (chdir(path) != 0) {
        perror("chdir");
        return;
    }
	getcwd(PWD, sizeof(PWD));	
	updatepaths(PWD, OLDPWD);
}

void cderror(char *path)
{
	ft_putstr(2, "cd : ");
	ft_putstr(2, path);
	ft_putstr(2, ": No such file or directory\n");
}
void	exec_cd(t_data *data,int fd)
{
	int		i;
	
	i = 0;
	while (data->args[i])
		i++;
	if (i <= 2)
	{
		if (!data->args[1] || !ft_strncmp(data->args[1], "--", 3))
			chdirandupdate(findvariableinenv("HOME"));
		else if (!ft_strncmp(data->args[1], "-", 2))
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
