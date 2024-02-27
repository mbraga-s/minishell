/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraga-s <mbraga-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 16:58:29 by mbraga-s          #+#    #+#             */
/*   Updated: 2024/02/27 16:45:11 by mbraga-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// main for testing executor (with readline)

struct s_global	g_data;

void	inner_working(char **tokens, char **env)
{
	t_data	*data;

	data = NULL;
	data = parser(tokens);
	expander(data, env);
	execution(data, env);
	free_all(data);
}

int	main(int argc, char **argv, char **env)
{
	char	*input;
	char	**tokens;

	(void)argc;
	(void)argv;
	tokens = NULL;
	while (1)
	{
		input = readline("\x1B[36mminishell$ \x1B[0m");
		if (!input)
			exit(1);
		if (input[0] != '\0')
		{
			add_history(input);
			tokens = lexer(input);
			if (syntax_checker(tokens))
				inner_working(tokens, env);
		}
		free(input);
	}
	return (0);
}
