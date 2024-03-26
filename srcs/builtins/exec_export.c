/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraga-s <mbraga-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 07:06:23 by manumart          #+#    #+#             */
/*   Updated: 2024/03/26 18:50:28 by mbraga-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	printenvpsorted(char **envpsorted, int fd)
{
	int	i;
	int	j;
	int	flag;

	i = 0;
	while (envpsorted[i])
	{
		flag = 0;
		j = 0;
		ft_putstr(fd, "declare -x ");
		while (envpsorted[i][j] != '\0')
		{
			write(1, &envpsorted[i][j], 1);
			if (flag == 0 && envpsorted[i][j] == '=')
			{
				ft_putstr(fd, "\"");
				flag = 1;
			}
			if (flag == 1 && envpsorted[i][j + 1] == '\0')
				ft_putstr(fd, "\"");
			j++;
		}
		ft_putstr(fd, "\n");
		i++;
	}
}

void	exportonly(char **envp, int fd)
{
	char	**envpsorted;
	int		envp_size;

	envpsorted = dpdup(envp);
	envp_size = getdpsize(envpsorted);
	envpsorted = sortenvp(envpsorted, envp_size);
	printenvpsorted(envpsorted, fd);
	free_array(envpsorted);
}

void	exporterror(char *arg)
{
	ft_putstr(2, "export: \'");
	ft_putstr(2, arg);
	ft_putstr(2, "\': not a valid identifier\n");
	g_data.status = 1;
}

void	replace_variablefor(char **env, char *arg, int output)
{
	free(env[output]);
	env[output] = arg;
}

void	exec_export(t_data *data, int fd)
{
	int	i;

	i = 1;
	if ((!data->args[1] || data->args[1][0] == '\0') && msdata()->envp)
		exportonly(msdata()->envp, fd);
	else
	{
		while (data->args[i])
		{
			if (is_valid(data->args[i]))
				addtoenv(data->args[i]);
			else
				exporterror(data->args[i]);
			i++;
		}
	}
}
