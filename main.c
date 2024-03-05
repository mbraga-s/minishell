/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraga-s <mbraga-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 16:58:29 by mbraga-s          #+#    #+#             */
/*   Updated: 2024/03/05 11:12:22 by mbraga-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// main for testing executor (with readline)

struct s_global	g_data;

char	**dup_envs(char **env)
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

void	inner_working(char **tokens, char **env_copy)
{
	t_data	*data;

	data = NULL;
	data = parser(tokens, env_copy);
	expander(data);
	execution(data);
	free_all(data);
}

int	main(int argc, char **argv, char **env)
{
	char	*input;
	char	**tokens;
	char	**env_copy;

	(void)argc;
	(void)argv;
	tokens = NULL;
	env_copy = dup_envs(env);
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
				inner_working(tokens, env_copy);
		}
		free(input);
	}
	return (0);
}
