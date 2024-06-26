/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraga-s <mbraga-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 16:58:29 by mbraga-s          #+#    #+#             */
/*   Updated: 2024/04/14 16:05:10 by mbraga-s         ###   ########.fr       */
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
	msdata()->hd_signal = 0;
	expander(data);
	g_data.status = 0;
	redirections(data);
	if (msdata()->hd_signal == 0)
		execution(data);
	free_all(data);
}

void	miniloop(void)
{
	char	*input;
	char	**tokens;

	tokens = NULL;
	input = readline("$minishell: ");
	signal(SIGINT, SIG_IGN);
	if (!input)
	{
		free_array(msdata()->envp);
		ft_putstr(1, "exit\n");
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
	if (msdata()->envp)
		getshlvl();
	while (1)
	{
		signal(SIGINT, sigintmain);
		signal(SIGQUIT, SIG_IGN);
		miniloop();
	}
}
