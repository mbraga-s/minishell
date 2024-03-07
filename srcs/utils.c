/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manumart <manumart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 17:56:04 by mbraga-s          #+#    #+#             */
/*   Updated: 2024/03/07 04:29:04 by manumart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_all(t_data *node)
{
	t_data	*current;

	while (node)
	{
		current = node;
		node = node->next;
		free_array(current->args);
		free_array(current->infile);
		free_array(current->inflag);
		free_array(current->outfile);
		free_array(current->outflag);
		free(current);
	}
}

void	free_array(char **array)
{
	int		i;

	i = 0;
	while (array && array[i])
		free (array[i++]);
	free (array);
}

t_data	*ft_lstfirst(t_data *lst)
{
	if (!lst)
		return (NULL);
	while (lst->prev != NULL)
		lst = lst->prev;
	return (lst);
}

void	check_error(char *str)
{
	write(2, str, ft_strlen(str));
	if (!ft_strchr(str, '/'))
	{
		write(2, ": command not found\n", 20);
		g_data.status = 127;
	}
	else if (ft_strchr(str, '/') && access(str, X_OK) == 0)
	{
		write(2, ": Is a directory\n", 17);
		g_data.status = 126;
	}
	else if (access(str, F_OK) != 0)
	{
		write(2, ": No such file or directory\n", 28);
		g_data.status = 127;
	}
	else if (access(str, X_OK) != 0)
	{
		write(2, ": Permission denied\n", 20);
		g_data.status = 126;
	}
	else
		perror("");
}

char	**dup_array(char **env)
{
	int		i;
	char	**env_copy;

	i = 0;
	if (!env)
		return (NULL);
	while (env[i])
		i++;
	env_copy = ft_calloc(i + 1, sizeof(char *));
	i = 0;
	while (env[i])
	{
		env_copy[i] = ft_strdup(env[i]);
		i++;
	}
	return (env_copy);
}
