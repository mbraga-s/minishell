/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraga-s <mbraga-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 11:17:45 by manumart          #+#    #+#             */
/*   Updated: 2024/03/26 17:31:49 by mbraga-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	siginthandler(int signum)
{
	int	pid;

	pid = waitpid(-1, NULL, 0);
	(void)signum;
	if (pid == -1)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	siginthandler2(int signum)
{
	(void)signum;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
}

void	sigheredochandler(int signum)
{
	int	i;

	(void)signum;
	i = 3;
	while (i < FOPEN_MAX)
		close(i++);
	free_all(msdata()->strut);
	free_array(msdata()->envp);
	exit(130);
}

void	sigquithandler(int signum)
{
	(void)signum;
	ft_putstr(2, "warning: here-document delimited by EOF.\n");
}
