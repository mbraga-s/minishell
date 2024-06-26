/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraga-s <mbraga-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 17:56:04 by mbraga-s          #+#    #+#             */
/*   Updated: 2024/04/14 16:06:24 by mbraga-s         ###   ########.fr       */
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

//Finds the first node of a linked list and returns it.
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

char	*ft_putstr(int fd, char *str)
{
	write(fd, str, ft_strlen(str));
	return (str);
}

void	getshlvl(void)
{
	int		findshlvl;
	char	**temp;
	char	*str;

	findshlvl = searchinenvp("SHLVL", msdata()->envp);
	temp = ft_split(msdata()->envp[findshlvl], '=');
	msdata()->shlvl = temp[1][0]++;
	if (!ft_strdigit(temp[1]))
		str = ft_stjnf("SHLVL=", temp[1]);
	else 
		str = ft_stjnf("SHLVL=", "1");
	addtoenv(str);
	free(str);
	free_array(temp);
}
