/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraga-s <mbraga-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 17:21:44 by mbraga-s          #+#    #+#             */
/*   Updated: 2024/02/21 17:37:12 by mbraga-s         ###   ########.fr       */
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

char	*new_funct2(char *str, char *nenv, int pos, int len)
{
	int		i;
	int		j;
	int		h;
	int		total;
	char	*ptr;

	i = 0;
	j = 0;
	h = 0;
	total = ft_strlen(nenv) + ft_strlen(str) - len + 2;
	ptr = ft_calloc(total, sizeof(char));
	while (str[i]) //&& total > 0)
	{
		while (i < pos)
			ptr[j++] = str[i++];
		if (h == 0 && nenv)
		{
			while (nenv && nenv[h])
				ptr[j++] = nenv[h++];
			i = i + (len);
			//total = total - h;
		}
		if (h == 0 && !nenv)
		{
			i = i + (len);
			h++;
		}
		ptr[j++] = str[i++];
		//total--;
	}
	free(nenv);
	free(str);
	return (ptr);
}

char	*expand(char *str, char **env)
{
	int		i;
	int		j;
	int		len;
	char	*nenv;

	i = 0;
	while (str && str[i] != '\0')
	{
		if (str[i] == 36)
		{
			j = i + 1;
			len = 0;
			while (str[j] && ft_isalnum(str[j++]))
				len++;
			if (len > 0)
			{
				nenv = get_newenv(len, i, str, env);
				str = new_funct2(str, nenv, i, (len + 1));
				i--;
			}
		}
		i++;
	}
	return (str);
}