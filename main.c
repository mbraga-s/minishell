/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraga-s <mbraga-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 16:58:29 by mbraga-s          #+#    #+#             */
/*   Updated: 2024/02/19 16:58:33 by mbraga-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// main for testing executor (with readline)

int	main(int argc, char **argv, char **env)
{
	char	*input;
	char	**tokens;
	t_data	*data;

	(void)argc;
	(void)argv;
	tokens = NULL;
	data = NULL;
	while (1)
	{
		input = readline("\x1B[36mminishell$ \x1B[0m");
		if (!input)
			exit(0);
		if (input[0] != '\0')
		{
			add_history(input);
			tokens = lexer(input);
			if (syntax_checker(tokens))
			{
				data = parser(tokens);
				expander(data, env);
				execution(data, env);
				free_all(data);
			}
		}
		free(input);
	}
	return (0);
}
