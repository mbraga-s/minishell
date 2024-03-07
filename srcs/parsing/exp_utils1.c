/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_utils1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraga-s <mbraga-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 16:40:27 by mbraga-s          #+#    #+#             */
/*   Updated: 2024/02/27 16:41:36 by mbraga-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*get_newenv(int len, int i, char *str, char **env)
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
