/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraga-s <mbraga-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 14:15:27 by mbraga-s          #+#    #+#             */
/*   Updated: 2024/03/05 11:01:38 by mbraga-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_data(t_data *node, char **env_copy)
{
	node->args = NULL;
	node->fd[0] = 0;
	node->fd[1] = 1;
	node->infile = NULL;
	node->outfile = NULL;
	node->outflag = NULL;
	node->inflag = NULL;
	node->nenv = env_copy;
	node->pid = 0;
	node->next = NULL;
	node->prev = NULL;
}

t_data	*ft_lstnew(char **env_copy)
{
	t_data	*ptr;

	ptr = ft_calloc(1, sizeof(t_data));
	if (!ptr)
		return (NULL);
	init_data(ptr, env_copy);
	return (ptr);
}
