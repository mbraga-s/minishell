/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manumart <manumart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 11:17:45 by manumart          #+#    #+#             */
/*   Updated: 2024/03/22 17:08:21 by manumart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void siginthandler(int signum)
{
    int pid;
    
    pid = waitpid(-1, NULL, 0);
    (void)signum;
    if(pid == -1)
    {
        write(1, "\n", 1);
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
    }
}

void sigquithandler(int signum)
{
    int pid;
    
    pid = waitpid(-1, NULL, 0);
    (void)signum;
    if(pid == -1)
    {
        
    }
}