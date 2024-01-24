/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraga-s <mbraga-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:30:04 by mbraga-s          #+#    #+#             */
/*   Updated: 2024/01/24 16:13:01 by mbraga-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**add_args(char **args, char *token)
{
	int		i;
	int		len;
	char	**ptr;

	i = 0;
	len = 0;
	while (args && args[len])
		len++;
	ptr = ft_calloc((len + 2), sizeof(char *));
	if (!ptr)
		return (NULL);
	while (i < len)
	{
		ptr[i] = args[i];
		i++;
	}
	ptr[i] = token;
	free(args);
	return (ptr);
}

t_data	*parser(char **token)
{
	t_data	*data;
	t_data	*current;
	int		i;

	i = 0;
	data = ft_lstnew();
	current = data;
	while (token[i])
	{
		while (token[i] && ft_strncmp(token[i], "|", 2))
		{
			if (!ft_strncmp(token[i], "<", 2))
				current->infile = token[++i];
			else if (!ft_strncmp(token[i], ">", 2))
				current->outfile = token[++i];
			else if (!current->cmd)
				current->cmd = token[i];
			else
				current->args = add_args(current->args, token[i]);
			i++;
		}
		if (token[i] && !ft_strncmp(token[i], "|", 2))
		{
			ft_lstadd_back(&current, ft_lstnew());
			current = current->next;
			i++;
		}
	}
	return (data);
}

// main for testing lexer

int	main(int argc, char **argv)
{
	char	**tokens;
	t_data	*data;
	int		i;

	tokens = NULL;
	data = NULL;

	if (argc == 2)
	{
		tokens = lexer(argv[1]);
		data = parser(tokens);
		while (data)
		{
			printf("\ncmd = %s\n", data->cmd);
			printf("\nargs = ");
			i = 0;
			while (data->args && data->args[i])
			{
				printf("%s ", data->args[i]);
				i++;
			}
			printf("\n");
			printf("infile = %s\n", data->infile);
			printf("outfile = %s\n", data->outfile);
			data = data->next;
		}
	}
	return (0);
}
