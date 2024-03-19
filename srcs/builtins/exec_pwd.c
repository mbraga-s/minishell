/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manumart <manumart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 07:08:52 by manumart          #+#    #+#             */
/*   Updated: 2024/03/19 23:39:10 by manumart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	exec_pwd(int fd)
{
	char	cwd[PATH_MAX];

	getcwd(cwd, sizeof(cwd));
	ft_putstr(fd, cwd);
	write(fd, "\n", 1);
}
