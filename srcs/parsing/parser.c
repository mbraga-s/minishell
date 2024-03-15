/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraga-s <mbraga-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:30:04 by mbraga-s          #+#    #+#             */
/*   Updated: 2024/03/15 19:04:20 by mbraga-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//Appends a string to an already existing array of strings.
char	**add_args(char **args, char *token)
{
	int		i;
	int		len;
	char	**ptr;

	i = 0;
	len = 0;
	while (args && args[len])
		len++;
	ptr = ft_calloc((len + 2), sizeof(char *));
	if (!ptr)
		return (NULL);
	while (i < len)
	{
		ptr[i] = args[i];
		i++;
	}
	ptr[i] = ft_strdup(token);
	free(args);
	return (ptr);
}

//Checks for infiles, outfiles and appending.
int	parser_pt1(char **token, t_data *data, int i)
{
	if (!ft_strncmp(token[i], "<", 2) && ++i)
	{
		data->infile = add_args(data->infile, token[i]);
		data->inflag = add_args(data->inflag, "0");
		return (1);
	}
	else if (!ft_strncmp(token[i], ">", 2) && ++i)
	{
		data->outfile = add_args(data->outfile, token[i]);
		data->outflag = add_args(data->outflag, "0");
		return (1);
	}
	else if (!ft_strncmp(token[i], ">>", 3) && ++i)
	{
		data->outfile = add_args(data->outfile, token[i]);
		data->outflag = add_args(data->outflag, "1");
		return (1);
	}
	return (0);
}

//Checks for an here-doc operator.
int	parser_pt2(char **token, t_data *data, int i)
{
	char	*heredoc;

	heredoc = NULL;
	if (!ft_strncmp(token[i], "<<", 3) && ++i)
	{
		heredoc = ft_heredoc(token[i]);
		data->infile = add_args(data->infile, heredoc);
		free(heredoc);
		data->inflag = add_args(data->inflag, "1");
		return (1);
	}
	return (0);
}

//Takes the tokens given by lexer and assigns them to a linked list.
t_data	*parser(char **token)
{
	t_data	*data;
	int		i;

	i = 0;
	data = ft_lstnew();
	while (token[i])
	{
		while (token[i] && ft_strncmp(token[i], "|", 2))
		{
			if (parser_pt1(token, data, i))
				i++;
			else if (parser_pt2(token, data, i))
				i++;
			else
				data->args = add_args(data->args, token[i]);
			i++;
		}
		if (token[i] && !ft_strncmp(token[i], "|", 2))
		{
			data = ft_lstadd_back(&data, ft_lstnew());
			i++;
		}
	}
	free_array(token);
	return (ft_lstfirst(data));
}
