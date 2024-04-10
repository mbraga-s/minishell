/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraga-s <mbraga-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 11:17:45 by manumart          #+#    #+#             */
/*   Updated: 2024/04/10 20:02:51 by mbraga-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sigintmain(int signum)
{
	if (signum == 2)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	siginthd(int signum)
{
	int	i;

	(void)signum;
	i = 0;
	while (i < FOPEN_MAX)
		close(i++);
	free_all(msdata()->strut);
	free_array(msdata()->envp);
	exit(130);
}

/* void	signalhandlechild(t_data *data)
{
	int	flag;
	int	i;

	flag = 0;
	data = ft_lstfirst(data);
	while (data)
	{
		i = -1;
		while (data->infile && data->infile[++i])
		{
			if (!ft_strncmp(data->inflag[i], "1", 1))
				flag = 1;
		}
		data = data->next;
	}
	signal(SIGINT, siginthd);
	if (flag == 0)
		signal(SIGQUIT, SIG_DFL);
	else if (flag == 1)
		signal(SIGQUIT, SIG_IGN);
}
 */