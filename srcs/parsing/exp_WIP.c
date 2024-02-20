/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraga-s <mbraga-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 12:31:37 by mbraga-s          #+#    #+#             */
/*   Updated: 2024/02/20 21:24:49 by mbraga-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*rem_quotes(char *str);

char	*expand(char *str, char **envp);

//Checks if there are quoted or expandable strings

/* void	expander(t_data *current, char **envp)
{
	int		j;

	while (current)
	{
		j = 0;
		while (current->args && current->args[j])
		{
			if (current->args[j][0] == 36 && current->args[j][1])
				current->args[j] = expand(current->args[j], envp);
			else if (current->args[j][0] == 34)
			{
				current->args[j] = rem_quotes(current->args[j]);
				if (current->args[j][0] == 36 && current->args[j][1])
					current->args[j] = expand(current->args[j], envp);
			}
			else if (current->args[j][0] == 39)
				current->args[j] = rem_quotes(current->args[j]);
			j++;
		}
		current = current->next;
	}
} */

void	expander(t_data *current, char **envp)
{
	int		j;

	while (current)
	{
		j = 0;
		while (current->args && current->args[j])
		{
			if (current->args[j][0] == 34)
			{
				current->args[j] = rem_quotes(current->args[j]);
				current->args[j] = expand(current->args[j], envp);
			}
			else if (current->args[j][0] == 39)
				current->args[j] = rem_quotes(current->args[j]);
			else
				current->args[j] = expand(current->args[j], envp);
			j++;
		}
		current = current->next;
	}
}

//Removes quotes from the string by moving every character one position
//to the left and setting the last 2 to NULLs

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

//Searchs for the string in the environment variables
//If found, frees the string and returns a copy of the variable's value

/* char	*expand(char *str, char **envp)
{
	char	*str1;
	char	*env;
	int		i;
	int		len;

	i = 0;
	env = NULL;
	if (!envp)
		return (NULL);
	len = ft_strlen(str);
	str1 = ft_strdup(&str[1]);
	while (envp && envp[i] && ft_strncmp(str1, envp[i], ft_strlen(str1)))
		i++;
	if (envp[i] && !ft_strncmp(str1, envp[i], ft_strlen(str1)))
		env = ft_strdup(&envp[i][len]);
	free(str);
	free(str1);
	return (env);
} */

char	*new_funct(int len, int i, char *str, char **env)
{
	char	*temp;
	char	*new_env;
	int		j;

	j = 0;
	new_env = NULL;
	temp = ft_calloc((len), sizeof(char));
	ft_strlcpy(temp, &str[i + 1], (len));
	temp = ft_strjoin(temp, "=");
	while (env[j] && ft_strncmp(temp, env[j], len))
		j++;
	if (env[j] && !ft_strncmp(temp, env[j], len))
		new_env = ft_strdup(&env[j][len]);
	free (temp);
	return (new_env);
}

void	new_funct2(char *str, char *temp, char *ptr, int total, int len)
{
	int	i;
	int	j;
	int	h;
	int flag;

	i = 0;
	j = 0;
	h = 0;
	flag = 0;
	while (str[i] && total > 0)
	{
		ptr[j] = str[i];
		if (str[i] == 36 && flag == 0 && temp)
		{
			i = i + len - 1;
			while (temp && temp[h])
			{
				ptr[j] = temp[h++];
				j++;
			}
			total = total - h;
			j--;
			flag = 1;
		}
		total--;
		i++;
		j++;
	}
	if (temp)
		free(temp);
	free(str);
}

char	*expand(char *str, char **envp)
{
	int		i;
	int		j;
	int		len;
	char	*temp;
	char	*ptr;
	int		total;

	i = 0;
	len = 0;
	if (!envp)
		return (NULL);
	while (str && str[i])
	{
		if (str[i] == 36)
		{
			j = i + 1;
			while (str[j] && ft_isalnum(str[j++]))
				len++;
			len++;
			temp = new_funct(len, i, str, envp);
			total = ft_strlen(temp) + ft_strlen(str) - len + 1;
			ptr = ft_calloc(total, sizeof(char));
			new_funct2(str, temp, ptr, total, len);
			if (!temp)
				ptr = expand(ptr, envp);
			return (ptr);
		}
		i++;
	}
	return (str);
}

int	main(int argc, char **argv, char **env)
{
	char	*ptr;
	char	*temp;

	ptr = NULL;
	if (argc >= 2)
	{
		temp = ft_strdup(argv[1]);
		ptr = expand(temp, env);
		printf("%s\n", ptr);
		free(ptr);
	}
	return (0);
}