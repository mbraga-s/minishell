/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraga-s <mbraga-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 17:21:44 by mbraga-s          #+#    #+#             */
/*   Updated: 2024/04/01 15:34:10 by mbraga-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//Copies the env value found (nenv) to the pointer given
//starting at the position j.
int	new_funct(char *ptr, char *nenv, int j)
{
	int	h;

	h = 0;
	while (nenv && nenv[h])
		ptr[j++] = nenv[h++];
	return (j);
}

//Returns the size of the expandable variable ($SMTH)
//by running until a non-alphanumeric char is found.
int	new_funct1(char *str, int j)
{
	int	len;

	len = 0;
	while (str[j] && ft_isalnum(str[j++]))
		len++;
	return (len);
}

// Allocates and 'builds' the string resulting from the replacement
// of the $NAME with it's value.
// len indicates the size of $NAME (5 in this case) and nenv
// is the value in the environment variables.
char	*n_ft2(char *str, char *nenv, int pos, int len)
{
	int		i;
	int		j;
	int		total;
	char	*ptr;

	i = 0;
	j = 0;
	total = ft_strlen(nenv) + ft_strlen(str) - len + 1;
	ptr = ft_calloc(total, sizeof(char));
	while (str[i] && i < pos)
		ptr[j++] = str[i++];
	if (nenv)
	{
		j = new_funct(ptr, nenv, j);
		i = i + (len);
	}
	else if (!nenv)
		i = i + (len);
	while (str[i])
		ptr[j++] = str[i++];
	free(nenv);
	free(str);
	return (ptr);
}

//Replaces the $? with the appropriate value.
char	*new_funct3(char *str, int pos, int len)
{
	int		i;
	int		j;
	int		total;
	char	*ptr;
	char	*temp;

	i = 0;
	j = 0;
	temp = ft_itoa(g_data.status);
	total = ft_strlen(temp) + ft_strlen(str) - len + 1;
	ptr = ft_calloc(total, sizeof(char));
	while (str[i] && i < pos)
		ptr[j++] = str[i++];
	if (temp)
	{
		j = new_funct(ptr, temp, j);
		i = i + (len);
	}
	while (str[i])
		ptr[j++] = str[i++];
	free(temp);
	free(str);
	return (ptr);
}

// Runs through the string seaching for a $. When found, replaces
// the expandable variable with it's value and returns the resulting
// string.
char	*expand(char *str, char **env)
{
	int		i;
	int		len;
	int		flag;

	i = 0;
	flag = 0;
	while (str && str[i] != '\0')
	{
		flag = new_funct4(flag, str, i);
		if (str[i] == 39 && flag == 0)
			i = i + inv_comma(str, i, str[i]) + 1;
		if (str[i] == 36 && str[i + 1] != 63)
		{
			len = new_funct1(str, i + 1);
			if (len > 0)
			{
				str = n_ft2(str, get_nenv(len, i, str, env), i, (len + 1));
				i--;
			}
		}
		else if (str[i] == 36 && str[i + 1] == 63)
			str = new_funct3(str, i, 2);
		i++;
	}
	return (str);
}
