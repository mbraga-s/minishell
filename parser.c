/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraga-s <mbraga-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:30:04 by mbraga-s          #+#    #+#             */
/*   Updated: 2024/01/23 18:18:23 by mbraga-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	*parser(char **tokens)
{
	t_data	*data;
	int		i;

	i = 0;
	data = ft_calloc(1, sizeof(t_data));
	init_data(data);
	while (tokens[i])
	{
		while (ft_strncmp(tokens[i], "|", 2))
		{
			if (!ft_strncmp(tokens[i], "<", 2))
				data->infile = tokens[++i];
			else if (!ft_strncmp(tokens[i], ">", 2))
				data->outfile = tokens[++i];
			else if (!data->cmd)
				data->cmd = tokens[i];
			else
				printf("Args\n");
				//data->args = tokens[i];
			i++;
		}
		ft_lstadd_back(&data, ft_lstnew());
		i++;
	}
	return (data);
}

// main for testing lexer

int	main(int argc, char **argv)
{
 	char	**tokens;
	t_data	*data;
	
	tokens = NULL;
	data = NULL;
	if (argc == 2)
	{
		tokens = lexer(argv[1]);
		data = parser(tokens);
		while (data->next)
		{
			printf("cmd = %s\n", data->cmd);
			printf("infile = %s\n", data->infile);
			printf("outile = %s\n", data->outfile);
			data = data->next;
		}
	}
	return (0);
}
