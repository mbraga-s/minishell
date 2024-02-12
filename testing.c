#include "minishell.h"

void	free_all(t_data *node, char **tokens);

void	execution(t_data *data, char **envp);

int	main(int argc, char **argv, char **env)
{
	int		i;
	char	**tokens;
	t_data	*data;
	t_data 	*current;
	i = 0;

	tokens = NULL;
	data = NULL;
	if (argc >= 2)
	{
		tokens = lexer(argv[1]);
		data = parser(tokens);
		expander(data);
		execution(data, env);
		current = data;
		while (current)
		{
			printf("\ncmd = %s\n", current->cmd);
			printf("args = ");
			i = 0;
			while (current->args && current->args[i])
			{
				printf("%s | ", current->args[i]);
				i++;
			}
			printf("\n");
			printf("infile = %s\n", current->infile);
			printf("outfile = %s\n", current->outfile);
			printf("pipe flag = %d\n", current->pipe_flag);
			current = current->next;
		}
		free_all(data, tokens);
	}
	return (0);
}

// main for testing parser

/* int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	//int		i;
	char	*input;
	char	**tokens;
	t_data	*data;
	//t_data 	*current;

	tokens = NULL;
	data = NULL;
	while (1)
	{
		input =	readline("$ ");
		if (!input)
			exit(0);
		if (input[0] != '\0')
		{
			tokens = lexer(input);
			data = parser(tokens);
			expander(data);
			execution(data, env);
			current = data;
			while (current)
			{
				printf("\ncmd = %s\n", current->cmd);
				printf("args = ");
				i = 0;
				while (current->args && current->args[i])
				{
					printf("%s || ", current->args[i]);
					i++;
				}
				printf("\n");
				printf("infile = %s\n", current->infile);
				printf("outfile = %s\n", current->outfile);
				printf("pipe flag = %d\n", current->pipe_flag);
				current = current->next;
			}
			free_all(data, tokens);
		}
	}
	return (0);
} */

void	free_all(t_data *node, char **tokens)
{
	t_data	*current;
	int		i;

	while (node)
	{
		current = node;
		node = node->next;
		free (current->cmd);
		i = 0;
		while (current->args && current->args[i])
			free (current->args[i++]);
		//free (current->args[i]);
		free (current->args);
		free (current->infile);
		free (current->outfile);
		free (current);
	}
	i = 0;
	while (tokens[i])
		free(tokens[i++]);
	free (tokens);
}
