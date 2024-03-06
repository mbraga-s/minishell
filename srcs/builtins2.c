/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraga-s <mbraga-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 14:07:50 by mbraga-s          #+#    #+#             */
/*   Updated: 2024/03/06 23:17:20 by mbraga-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* void	free_array(char **str)
{
	int	i;

	if (str == NULL)
		return ;
	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
} */
// dup de variavel DP
/* char	**dup_array(char **str)
{
	char	**dup;
	size_t	i;
	size_t  j;
	
	if(!str || !str[0])
		return(NULL);
	i = getdpsize(str);
	dup = ft_calloc(i + 1,sizeof(char *));
	if (!dup)
		return (NULL);
	j = 0;
	while (str[j] != NULL)
	{
		dup[j] = ft_strdup(str[j]);
		if (!dup[j])
		{
			free_array(dup);
			return (NULL);
		}
		j++;
	}
	return (dup);
} */
// obter tamanho de uma variavel double pointer (DP)

/* char	**sortenvp(char **envpsorted, int envp_size)
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
} */
int	searchforchar(char *str, char c)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

/* void	printenvpsorted(char **envpsorted)
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
			if (previouschar == '=' || (envpsorted[i][j + 1] == '\0'
					&& searchforchar(envpsorted[i], '=')))
			{
				write(1, "\"", 1);
			}
			j++;
		}
		write(1, "\n", 1);
		i++;
	}
}

int	getdpsize(char **dp)
{
	int	dp_size;

	dp_size = 0;
	while (dp[dp_size] != NULL)
		dp_size++;
	return (dp_size);
}
void	exportonly(char **envp)
{
	char	**envpsorted;
	int		envp_size;

	envp_size = getdpsize(envp);
	envpsorted = sortenvp(dup_array(envp), envp_size);
	printenvpsorted(envpsorted);
	free_array(envpsorted);
}

void	exporterror(t_data *data, char **new, int i)
{
	write(2, "export: \'", 10);
	write(2, data->args[i], ft_strlen(data->args[i]));
	write(2, "\': not a valid identifier\n", 26);
	free_array(new);
}

int	searchinenvp(char *input, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], input, ft_strlen(input)) != 0)
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
	str[j] = '\0'; // Null-terminate the modified string
	return (str);
}
void	exportwithargs(t_data *data, char **new, int i)
{
	if (!new || !new[0])
	{
		exporterror(data, new, i);
		return ;
	}
	if (searchinenvp(new[0], minishelldata()->envp) == -1)
		minishelldata()->envp = add_args(minishelldata()->envp, data->args[i]);
	if (searchinenvp(new[0], minishelldata()->envp) != 1)
	{
		if (new[1])
		{
			if (new[1][0] == '\"')
			{
				free_array(minishelldata()->envp);
				minishelldata()->envp[getdpsize(minishelldata()->envp) - 1] = ft_strdup(rem_allquotes(data->args[i]));
			}
			else
			{
				free_array(minishelldata()->envp);
				minishelldata()->envp[getdpsize(minishelldata()->envp) - 1] = ft_strdup(data->args[i]);
			}
		}
	}
}

int	digitquestionmark(int str)
{
	if (str >= '0' && str <= '9')
		return (1);
	return (0);
}
void	exec_export(t_data *data)
{
	char	**new;
	int		i;

	i = 1;
	if (!data->args[1] || data->args[1][0] == '\0')
		exportonly(minishelldata()->envp);
	else
	{
		while (data->args[i])
		{
			new = ft_split(data->args[i], '=');
			if (data->args[i][0] == '=' || (new && !ft_isalnum(new[0]))
				|| digitquestionmark(data->args[i][0]))
			{
				exporterror(data, new, i);
				printf("dei erro\n");
			}
			else
			{
				exportwithargs(data, new, i);
				printf("dei certo\n");
			}
			i++;
			free_array(new);
		}
	}
} */