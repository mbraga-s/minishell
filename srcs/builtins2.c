/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraga-s <mbraga-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 14:07:50 by mbraga-s          #+#    #+#             */
/*   Updated: 2024/03/06 16:25:02 by mbraga-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* void	free_array(char **str)
{
	int	i;

	if (str == NULL)
	{
		return ;cl
	}
	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
} */

// dup de variavel DP
/* char	**dpdup(char **str)
{
	char	**dup;
	size_t	i;

	i = 0;
	while (str[i] != NULL)
		i++;
	dup = ft_calloc(sizeof(char *), i + 1);
	if (!dup)
		return (NULL);
	i = 0;
	while (str[i] != NULL)
	{
		dup[i] = ft_strdup(str[i]);
		if (!dup[i])
		{
			free_array(dup);
			return (NULL);
		}
		i++;
	}
	dup[i] = NULL;
	return (dup);
} */
// obter tamanho de uma variavel double pointer (DP)

char	**sortenvp(char **envpsorted, int envp_size)
{
	int		swapped;
	int		i;
	char	*temp;

	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		i = 0;
		while (i < envp_size - 1)
		{
			if (ft_strncmp(envpsorted[i], envpsorted[i + 1], envp_size) > 0)
			{
				swapped = 1;
				temp = envpsorted[i];
				envpsorted[i] = envpsorted[i + 1];
				envpsorted[i + 1] = temp;
			}
			i++;
		}
		envp_size--;
	}
	return (envpsorted);
}

int	searchforchar(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void	printenvpsorted(char **envpsorted)
{
	int		i;
	char	previouschar;
	int		j;

	i = 0;
	while (envpsorted[i])
	{
		j = 0;
		write(1, "declare -x ", 12);
		while (envpsorted[i][j] != '\0')
		{
			previouschar = envpsorted[i][j];
			write(1, &envpsorted[i][j], 1);
			if (previouschar == '=' || (envpsorted[i][j + 1] == '\0' && searchforchar(envpsorted[i], '=')))
			{
				write(1, "\"", 1);
			}
			j++;
		}
		write(1, "\n", 1);
		i++;
	}
	free_array(envpsorted);
}

int	getenvpsize(char **envp)
{
	int	envp_size;

	envp_size = 0;
	while (envp[envp_size] != NULL)
		envp_size++;
	return (envp_size);
}

void	exportonly(char **envp)
{
	char	**envpsorted;
	int		envp_size;

	envp_size = getenvpsize(envp);
	envpsorted = ft_calloc((envp_size + 1), sizeof(char *));
	if (!envpsorted)
		return ;
	envpsorted = sortenvp(dup_array(envp), envp_size);
	printenvpsorted(envpsorted);
}

void	exporterror(t_data *data, char **new, int i)
{
	write(2, "export: \'", 10);
	write(2, data->args[i], ft_strlen(data->args[i]));
	write(2, "\': not a valid identifier\n", 26);
	free_array(new);
}

int	searchinenvp(char *input, char **nenv)
{
	int	i;

	i = 0;
	while (nenv[i])
	{
		if (ft_strncmp(nenv[i], input, ft_strlen(input)))
			i++;
		else
			return (i);
	}
	return (-1);
}

char	*rem_allquotes(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (str == NULL || str[0] == '\0')
		return (NULL);
	while (str[i])
	{
		if (str[i] != '\"')
		{
			str[j] = str[i];
			j++;
		}
		i++;
	}
	str[j] = '\0';
	return (str);
}

void	exportwithargs(t_data *data, char **new, int i)
{
	int	flag;

	if (!new || !new[0])
	{
		exporterror(data, new, i);
		return ;
	}
	flag = searchinenvp(new[0], minishellenv()->envp);
	if (flag == -1)
		minishellenv()->envp = add_args(minishellenv()->envp, data->args[i]);
	else if (flag != 1)
	{
		if (new[1])
		{
			if (new[1][0] == '\"')
			{
				free(minishellenv()->envp[flag]);
				minishellenv()->envp[flag] = ft_strdup(rem_allquotes(data->args[i]));
			}
			else
			{
				free(minishellenv()->envp[flag]);
				minishellenv()->envp[flag] = ft_strdup(data->args[i]);
			}
		}
	}
}

void	exec_export(t_data *data)
{
	char	**new;
	int		i;

	i = 0;
	while (data->args && data->args[i])
		i++;
	if (i < 2)
		exportonly(minishellenv()->envp);
	else
	{
		i = 1;
		while (data->args[i])
		{
			new = ft_split(data->args[i], '=');
			if (data->args[i][0] == '=' || (new && !ft_strisalpha(new[0])))
			{
				exporterror(data, new, i);
				printf("dei erro\n");
			}
			else
			{
				exportwithargs(data, new, i);
				free_array(new);
				printf("dei certo\n");
			}
			i++;
		}
	}
}
