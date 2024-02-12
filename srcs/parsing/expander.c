/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraga-s <mbraga-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 12:31:37 by mbraga-s          #+#    #+#             */
/*   Updated: 2024/02/12 16:49:45 by mbraga-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*rem_quotes(char *str);

void	expander(t_data *current)
{
	int		j;

	while (current)
	{
		if (current->cmd[0] == 34 || current->cmd[0] == 39)
		{
			if (current->cmd[0] == 34)
				printf("\nEXPANDER\n");
			current->cmd = rem_quotes(current->cmd);
		}
		j = 0;
		while (current->args && current->args[j])
		{
			if (current->args[j][0] == 34 || current->args[j][0] == 39)
			{
				if (current->args[j][0] == 34)
					printf("\nEXPANDER\n");
				current->args[j] = rem_quotes(current->args[j]);
			}
			j++;
		}
		current = current->next;
	}
}

char	*rem_quotes(char *str)
{
	int		i;
	int		len;

	len = ft_strlen(str);
	i = 0;
	if (!str)
		return (NULL);
	while (str[i] && i < (len - 2))
	{
		str[i] = str[i + 1];
		i++;
	}
	str[i++] = '\0';
	str[i++] = '\0';
	return (str);
}

/* int	main(void)
{
	char	**tokens;
	t_data	*data;
	int		i;
	char	*input;

	tokens = NULL;
	data = NULL;
	while (1)
	{
		input =	readline("$ ");
		if(!input)
			exit(0);
		tokens = lexer(input);
		data = parser(tokens);
		expander(data);
		while (data)
		{
			printf("\ncmd = %s\n", data->cmd);
			printf("args = ");
			i = 0;
			while (data->args && data->args[i])
			{
				printf("%s || ", data->args[i]);
				i++;
			}
			printf("\n");
			printf("infile = %s\n", data->infile);
			printf("outfile = %s\n", data->outfile);
			printf("pipe flag = %d\n", data->pipe_flag);
			data = data->next;
		}
	}
	return (0);
} */