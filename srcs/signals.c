/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manumart <manumart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 11:17:45 by manumart          #+#    #+#             */
/*   Updated: 2024/03/27 17:28:47 by manumart         ###   ########.fr       */
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
	write(1, "^C", 2);
	exit(130);
}

void	sigquithandler(int signum)
{
	(void)signum;
	ft_putstr(2, "Quit (core dumped)\n");
}
