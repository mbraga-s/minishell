/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manumart <manumart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 18:18:32 by mbraga-s          #+#    #+#             */
/*   Updated: 2024/03/07 04:38:34 by manumart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

void	exec_pwd(void)
{
	char	cwd[PATH_MAX];

	getcwd(cwd, sizeof(cwd));
	if (cwd != NULL)
		printf("%s\n", cwd);
}

void	exec_cd(t_data *data)
{
	int	i;

	i = 0;
	while (data->args[i])
		i++;
	if (i <= 2)
	{
		if (!data->args[1] || !ft_strncmp(data->args[1], "--", 3))
			chdir(getenv("HOME"));
		else if (!ft_strncmp(data->args[1], "-", 2))
			chdir(getenv("OLDPWD"));
		else if (!access(data->args[1], F_OK))
			chdir(data->args[1]);
		else
			printf("cd : no such file or directory: %s\n", data->args[1]);
	}
	else
		printf("cd: too many arguments\n");
}

void	exec_exit(t_data *data)
{
	int	exitcode;
	int	i;

	i = 0;
	exitcode = 0;
	while (data->args[i])
		i++;
	printf("exit\n");
	if (i <= 2)
	{
		if (i == 2 && ft_isdigit(data->args[1]))
		{
			printf("exit : %s: numeric argument required\n", data->args[1]);
			exitcode = 255;
		}
		else if (i == 2 && !ft_isdigit(data->args[1]))
		{
			exitcode = ft_atoi(data->args[1]);
		}
		free_all(ft_lstfirst(data));
		clean_env();
		exit(exitcode);
	}
	else
		printf("exit: too many arguments\n");
}	
}

// env
void	exec_env(t_data *data)
{
	int	i;

	i = 0;
	if (data->args[1])
	{
		printf("env: '%s': No such file or directory", data->args[1]);
	}
	else
	{
		while (msdata()->envp[i])
		{
			if (ft_strchr(msdata()->envp[i], '='))
				printf("%s\n", msdata()->envp[i]);
			i++;
		}
	}
}

//

// echo

void	exec_echo(t_data *data)
{
	int	newline;
	int	i;

	newline = 0;
	i = 1;
	if (data->args[1])
	{
		if (!ft_strncmp(data->args[1], "-n", 2))
			newline = 1;
		else
		{
			while (data->args[i])
			{
				write(1, data->args[i], ft_strlen(data->args[i]));
				i++;
				if (data->args[i])
					write(1, " ", 1);
			}
		}
		if (newline == 0)
			write(1, "\n", 1);
	}
	else
		write(1, "\n", 1);
}
//

int	ft_isalnum(char c)
{
	if ((c >= '0' && c <= '9'))
		return (1);
	else if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

// export

// free array

void	free_array(char **str)
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
}
// dup de variavel DP
char	**dpdup(char **str)
{
	char	**dup;
	size_t	i;
	size_t	j;

	if (!str || !str[0])
		return (NULL);
	i = getdpsize(str);
	dup = ft_calloc(sizeof(char *), i + 1);
	if (!dup)
		return (NULL);
	j = 0;
	while (str[j] != NULL)
	{
		dup[j] = ft_strdup(str[j]);
		if (!dup[j])
		{
			free_array(dup);
			return (dup);
		}
		j++;
	}
	return (dup);
}
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
	int		j;
	int 	flag;

	i = 0;
	while (envpsorted[i])
	{
		flag = 0;	
		j = 0;
		write(1, "declare -x ", 11);
		while (envpsorted[i][j] != '\0')
		{
			write(1, &envpsorted[i][j], 1);
			if(flag == 0 && envpsorted[i][j] == '=')
			{
				write(1,"\"",1);
				flag = 1;
			}	
			if(flag == 1 && envpsorted[i][j + 1] == '\0')
				write(1,"\"",1);
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
	envpsorted = dpdup(envp);
	printenvpsorted(sortenvp(envpsorted,envp_size));
	free_array(envpsorted);
}

void	exporterror(char *arg)
{
	write(2, "export: \'", 10);
	write(2, arg, ft_strlen(arg));
	write(2, "\': not a valid identifier\n", 26);
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
int	is_valid(char *str)
{
	int	i;

	i = 0;
	if ((str[i] >= '0' && str[i] <= '9') || str[i] == '=')
		return (0);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_' && str[i] != '=')
			return (0);
		i++;
	}
	return (1);
}

int	digitquestionmark(int str)
{
	if (str >= '0' && str <= '9')
		return (1);
	return (0);
}

void replace_variablefor(char **env,char *arg,int output)
{
	free(env[output]);
	env[output] = arg;
}
void	addtoenv(char *arg)
{
	int output;
	char **temp;
	char *temparg;
	
	temparg = ft_strdup(rem_allquotes(arg));
	temp = ft_split(arg,'=');
	output = searchinenvp(temp[0],msdata()->envp);
	if (output != -1)
	{
		replace_variablefor(msdata()->envp,temparg,output);
		free_array(temp);
		free(temparg);
		return ;
	}
	msdata()->envp = add_args(msdata()->envp,temparg);
	free_array(temp);
	free(temparg);
}

void	exec_export(t_data *data)
{
	int	i;

	i = 1;
	if (!data->args[1] || data->args[1][0] == '\0')
		exportonly(msdata()->envp);
	else
	{
		while (data->args[i])
		{
			if (is_valid(data->args[i]))
			{
				addtoenv(data->args[i]);
				printf("dei certo\n");
			}
			else
			{
				exporterror(data->args[i]);
				printf("dei erro\n");
			}
			i++;
		}
	}
}

void exec_unset(t_data *data)
{
	int i;
	int output;

	i = 1;
	while (data->args[i])
	{
		output = searchinenvp(data->args[i],msdata()->envp);
		if (output != -1)
		{
			free(msdata()->envp[output]);
			msdata()->envp[output] = NULL;
		}
		i++;
	}
}
