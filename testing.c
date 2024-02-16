#include "minishell.h"

// main for testing parsing and expander (with argv, argc)

/* int	main(int argc, char **argv)
{
	int		i;
	char	**tokens;
	t_data	*data;
	t_data	*current;

	i = 0;
	tokens = NULL;
	data = NULL;
	if (argc >= 2)
	{
		tokens = lexer(argv[1]);
		data = parser(tokens);
		expander(data);
		current = data;
		while (current)
		{
			printf("\nargs = ");
			i = 0;
			while (current->args && current->args[i])
			{
				printf("%s | ", current->args[i]);
				i++;
			}
			printf("\n");
			printf("infiles = ");
			i = 0;
			while (current->infile && current->infile[i])
			{
				printf("%s | ", current->infile[i]);
				i++;
			}
			printf("\n");
			printf("outfiles = ");
			i = 0;
			while (current->outfile && current->outfile[i])
			{
				printf("%s | ", current->outfile[i]);
				i++;
			}
			printf("\n");
			printf("outflags = ");
			i = 0;
			while (current->outflag && current->outflag[i])
			{
				if (!ft_strncmp(current->outflag[i], "0", 1))
					printf("0 |");
				else
					printf("1 |");
				i++;
			}
			printf("\n\n");
			current = current->next;
		}
		free_all(data);
	}
	return (0);
} */

// main for testing parsing and expander (with readline)

/* int	main(void)
{
	char	*input;
	int		i;
	char	**tokens;
	t_data	*data;
	t_data	*current;

	tokens = NULL;
	data = NULL;
	i = 0;
	while (1)
	{
		input = readline("$ ");
		if (!input)
			exit(0);
		if (input[0] != '\0')
		{
			tokens = lexer(input);
			data = parser(tokens);
			expander(data);
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
			free_all(data);
		}
	}
	return (0);
} */

// main for testing executor (with argv, argc)

/* int	main(int argc, char **argv, char **env)
{
	char	**tokens;
	t_data	*data;

	tokens = NULL;
	data = NULL;
	if (argc >= 2)
	{
		tokens = lexer(argv[1]);
		data = parser(tokens);
		expander(data);
		execution(data, env);
		free_all(data);
	}
	return (0);
} */

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
