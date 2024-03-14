/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manumart <manumart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 18:07:27 by mbraga-s          #+#    #+#             */
/*   Updated: 2024/03/08 19:11:49 by manumart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	openhdoc(char *str)
{
	int	fd[2];

	if (pipe(fd) == -1)
	{
		perror(NULL);
		return (0);
	}
	ft_putstr(fd[1], str);
	close(fd[1]);
	return (fd[0]);
}

char	*ft_heredoc(char *str)
{
	char	*ptr;
	char	*input;

	ptr = NULL;
	input = NULL;
	input = readline("> ");
	while (ft_strncmp(input, str, (ft_strlen(str) + 1)))
	{
		ptr = ft_strjoin(ptr, input);
		free (input);
		ptr = ft_strjoin(ptr, "\n");
		input = readline("> ");
	}
	free(input);
	if (!ptr)
		ptr = ft_strdup("");
	return (ptr);
}
