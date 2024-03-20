/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_utils1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraga-s <mbraga-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 16:40:27 by mbraga-s          #+#    #+#             */
/*   Updated: 2024/03/20 17:38:23 by mbraga-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//Finds the value of the expandable variable in the env variables
//and returns a pointer to dup of that variable.
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
