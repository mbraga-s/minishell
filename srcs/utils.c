/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraga-s <mbraga-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 17:56:04 by mbraga-s          #+#    #+#             */
/*   Updated: 2024/02/16 11:04:46 by mbraga-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_all(t_data *node)
{
	t_data	*current;
	int		i;

	while (node)
	{
		current = node;
		node = node->next;
		i = 0;
		while (current->args && current->args[i])
			free (current->args[i++]);
		free (current->args);
		i = 0;
		while (current->infile && current->infile[i])
			free (current->infile[i++]);
		free (current->infile);
		i = 0;
		while (current->outfile && current->outfile[i])
			free (current->outfile[i++]);
		free (current->outfile);
		i = 0;
		while (current->outflag && current->outflag[i])
			free (current->outflag[i++]);
		free (current->outflag);
		free (current);
	}
}

void	free_tokens(char **tokens)
{
	int		i;

	i = 0;
	while (tokens[i])
		free (tokens[i++]);
	free (tokens);
}

t_data	*ft_lstfirst(t_data *lst)
{
	if (!lst)
		return (NULL);
	while (lst->prev != NULL)
		lst = lst->prev;
	return (lst);
}
