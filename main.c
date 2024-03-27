/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manumart <manumart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 16:58:29 by mbraga-s          #+#    #+#             */
/*   Updated: 2024/03/27 17:28:26 by manumart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// main for testing executor (with readline)

struct s_global	g_data;

t_envs	*msdata(void)
{
	static t_envs	envs;

	return (&envs);
}

int	check_input(char *input)
{
	int	i;

	i = 0;
	while (input && input[i])
	{
		if (input[i] == 39 || input[i] == 34)
		{
			if (searchforchar(&input[i + 1], input[i]) != -1)
				i = i + searchforchar(&input[i + 1], input[i]) + 1;
			else
				return (0);
		}
		i++;
	}
	return (1);
}

void	inner_working(char **tokens)
{
	t_data	*data;

	data = NULL;
	data = parser(tokens);
	msdata()->strut = data;
	expander(data);
	g_data.status = 0;
	execution(data);
	free_all(data);
}

void	miniloop(void)
{
	char	*input;
	char	**tokens;

	tokens = NULL;
	input = readline("\x1B[36mminishell$ \x1B[0m");
	signal(SIGQUIT, sigquithandler);
	signal(SIGINT, siginthandler2);
	if (!input)
	{
		free_array(msdata()->envp);
		exit(0);
	}
	if (*input)
	{
		add_history(input);
		if (check_input(input))
		{
			tokens = lexer(input);
			if (syntax_checker(tokens))
				inner_working(tokens);
		}
		else
			ft_putstr(2, "minishell: syntax error\n");
	}
	free(input);
}

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	msdata()->envp = dpdup(env);
	while (1)
	{
		signal(SIGINT, siginthandler);
		signal(SIGQUIT, SIG_IGN);
		miniloop();
	}
}
