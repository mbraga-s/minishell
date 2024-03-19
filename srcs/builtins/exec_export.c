/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manumart <manumart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 07:06:23 by manumart          #+#    #+#             */
/*   Updated: 2024/03/19 16:21:26 by manumart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**sortenvp(char **envpsorted, int envp_size)
{
	int		swapped;
	int		i;
	char	*temp;

	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		i = 0;
		while (i < envp_size - 1)
		{
			if (ft_strncmp(envpsorted[i], envpsorted[i + 1], envp_size) > 0)
			{
				swapped = 1;
				temp = envpsorted[i];
				envpsorted[i] = envpsorted[i + 1];
				envpsorted[i + 1] = temp;
			}
			i++;
		}
		envp_size--;
	}
	return (envpsorted);
}

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
}

void	replace_variablefor(char **env, char *arg, int output)
{
	free(env[output]);
	env[output] = arg;
}

void	addtoenv(char *arg)
{
	int		output;
	char	**temp;
	char	*tmp2;

	tmp2 = ft_strdup(arg);
	temp = ft_split(arg, '=');
	if (msdata()->envp)
	{
		output = searchinenvp(temp[0], msdata()->envp);
		if (output != -1)
		{
			if (ft_strncmp(tmp2, msdata()->envp[output], ft_strlen(tmp2)) == 0)
			{
				free_array(temp);
				free(tmp2);
				return ;
			}
			replace_variablefor(msdata()->envp, rem_allquotes(tmp2), output);
			free_array(temp);
			return ;
		}
	}
	msdata()->envp = add_args(msdata()->envp, tmp2);
	free_array(temp);
	free(tmp2);
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
