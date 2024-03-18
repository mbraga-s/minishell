/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraga-s <mbraga-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 07:09:06 by manumart          #+#    #+#             */
/*   Updated: 2024/03/18 16:25:40 by mbraga-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	exec_cd(t_data *data, int fd)
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
		{
			chdir(getenv("OLDPWD"));
			ft_putstr(fd, getenv("OLDPWD"));
			ft_putstr(fd, "\n");
		}
		else if (!access(data->args[1], F_OK))
			chdir(data->args[1]);
		else
		{
			ft_putstr(2, "cd : ");
			ft_putstr(2, data->args[1]);
			ft_putstr(2, ": No such file or directory\n");
		}
	}
	else
		ft_putstr(2, "cd: too many arguments\n");
}
