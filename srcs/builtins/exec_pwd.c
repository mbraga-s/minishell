/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraga-s <mbraga-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 07:08:52 by manumart          #+#    #+#             */
/*   Updated: 2024/03/18 16:28:59 by mbraga-s         ###   ########.fr       */
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
