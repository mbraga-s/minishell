/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manumart <manumart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 11:17:45 by manumart          #+#    #+#             */
/*   Updated: 2024/03/19 11:29:51 by manumart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
void siginthandler(int signum)
{
    (void)signum;
    ft_putstr(1, "nao vou morrer hehe\n");
}