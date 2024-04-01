/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manumart <manumart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 07:07:19 by manumart          #+#    #+#             */
/*   Updated: 2024/04/01 19:37:47 by manumart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	searchinenvp(char *input, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], input, ft_strlen(input)) != 0)
			i++;
		else
			return (i);
	}
	return (-1);
}

void	addtoenv(char *arg)
{
	int		output;
	char	**temp;
	char	*tmp2;

	tmp2 = ft_strdup(arg);
	temp = ft_split(arg, '=');
	if ((msdata()->envp))
	{
		output = searchinenvp(temp[0], (msdata()->envp));
		if (output != -1)
		{
			if (!(ft_strncmp(tmp2, (msdata()->envp)[output], ft_strlen(tmp2))))
			{
				free_array(temp);
				free(tmp2);
				return ;
			}
			replace_variablefor((msdata()->envp), rem_allquotes(tmp2), output);
			free_array(temp);
			return ;
		}
	}
	(msdata()->envp) = add_args((msdata()->envp), tmp2);
	free_array(temp);
	free(tmp2);
}

void	exec_env(t_data *data, int fd)
{
	int	i;

	i = 0;
	if (data->args[1])
	{
		ft_putstr(2, "env: '");
		ft_putstr(2, data->args[1]);
		ft_putstr(2, "': No such file or directory\n");
	}
	else
	{
		while (msdata()->envp && ((msdata()->envp)[i])
			&& ft_strchr(msdata()->envp[i], '='))
		{
			ft_putstr(fd, rem_allquotes((msdata()->envp)[i]));
			ft_putstr(fd, "\n");
			i++;
		}
	}
}
