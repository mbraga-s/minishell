/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manumart <manumart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 07:06:23 by manumart          #+#    #+#             */
/*   Updated: 2024/03/16 11:42:46 by manumart         ###   ########.fr       */
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

void	printenvpsorted(char **envpsorted)
{
	int	i;
	int	j;
	int	flag;

	i = 0;
	while (envpsorted[i])
	{
		flag = 0;
		j = 0;
		ft_putstr(1, "declare -x ");
		while (envpsorted[i][j] != '\0')
		{
			write(1, &envpsorted[i][j],1);
			if (flag == 0 && envpsorted[i][j] == '=')
			{
				ft_putstr(1, "\"");
				flag = 1;
			}
			if (flag == 1 && envpsorted[i][j + 1] == '\0')
				ft_putstr(1, "\"");
			j++;
		}
		ft_putstr(1, "\n");
		i++;
	}
}

void	exportonly(char **envp)
{
	char	**envpsorted;\
	int		envp_size;

	envpsorted = dpdup(envp);
	envp_size = getdpsize(envpsorted);
	envpsorted = sortenvp(envpsorted, envp_size);
	printenvpsorted(envpsorted);
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
	char	*temparg;

	temparg = ft_strdup(arg);
	temp = ft_split(arg, '=');
	output = searchinenvp(temp[0], msdata()->envp);
	if (output != -1)
	{
		if (ft_strncmp(temparg, msdata()->envp[output],
				ft_strlen(temparg)) == 0)
		{
			free_array(temp);
			free(temparg);
			return ;
		}
		replace_variablefor(msdata()->envp, rem_allquotes(temparg), output);
		free_array(temp);
		return ;
	}
	msdata()->envp = add_args(msdata()->envp, temparg);
	free_array(temp);
	free(temparg);
}

void	exec_export(t_data *data)
{
	int	i;

	i = 1;
	if (!data->args[1] || data->args[1][0] == '\0')
		exportonly(msdata()->envp);
	else
	{
		while (data->args[i])
		{
			if (is_valid(data->args[i]))
			{
				addtoenv(data->args[i]);
				printf("dei certo\n");
			}
			else
			{
				exporterror(data->args[i]);
			}
			i++;
		}
	}
}
