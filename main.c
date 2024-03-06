/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraga-s <mbraga-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 16:58:29 by mbraga-s          #+#    #+#             */
/*   Updated: 2024/03/06 23:58:45 by mbraga-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// main for testing executor (with readline)

struct s_global	g_data;

t_envs	*minishelldata(void)
{
	static t_envs	data;

	return (&data);
}

int	check_input(char *input)
{
	int		i;

	i = 0;
	while (input && input[i])
	{
		if (input[i] == 39 || input[i] == 34)
		{
			if (searchforchar(&input[i + 1], input[i]) != -1)
			{
				i = i + searchforchar(&input[i + 1], input[i]) + 1;
			}
			else
				return (0);
		}
		i++;
	}
	return (1);
}

void	inner_working(char **tokens, char **env_copy)
{
	t_data	*data;

	data = NULL;
	data = parser(tokens, env_copy);
	expander(data);
	execution(data);
	free_all(data);
}

void	miniloop(void)
{
	char	*input;
	char	**tokens;

	tokens = NULL;
	input = readline("\x1B[36mminishell$ \x1B[0m");
	if (!input)
		exit(1);
	if (input && input[0] != '\0')
	{
		add_history(input);
		if (check_input(input))
		{
			tokens = lexer(input);
			if (syntax_checker(tokens))
				inner_working(tokens, minishelldata()->envp);
		}
		else
			write(2, "Input error: unclosed quotes\n", 29);
	}
	free(input);
}

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	minishelldata()->envp = dup_array(env);
	while (1)
	{
		miniloop();
	}
	free_array(minishelldata()->envp);
	return (0);
}
