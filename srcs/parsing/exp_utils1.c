/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_utils1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manumart <manumart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 16:40:27 by mbraga-s          #+#    #+#             */
/*   Updated: 2024/03/26 14:46:50 by manumart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// Finds the value of the expandable variable in the env variables
// and returns a pointer to dup of that variable.
char	*get_nenv(int len, int i, char *str, char **env)
{
	char	*temp;
	char	*new_env;
	int		j;

	j = 0;
	new_env = NULL;
	if (!env)
		return (NULL);
	temp = ft_calloc((len + 1), sizeof(char));
	ft_strlcpy(temp, &str[i + 1], (len + 1));
	temp = ft_strjoin(temp, "=");
	while (env[j] && ft_strncmp(temp, env[j], len + 1))
		j++;
	if (env[j] && !ft_strncmp(temp, env[j], len + 1))
		new_env = ft_strdup(&env[j][len + 1]);
	free(temp);
	return (new_env);
}

int	new_funct4(int flag, char *str, int i)
{
	if (str[i] == 34 && flag == 0)
		flag = 1;
	else if (str[i] == 34 && flag == 1)
		flag = 0;
	return (flag);
}
