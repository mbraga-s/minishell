/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manumart <manumart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 11:17:45 by manumart          #+#    #+#             */
/*   Updated: 2024/03/26 15:32:49 by manumart         ###   ########.fr       */
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
	(void)signum;
    if(signum = SIGINT)
    {
                
    }
}

void	sigquithandler(int signum)
{
	(void)signum;
	ft_putstr(1, "exit");
}
