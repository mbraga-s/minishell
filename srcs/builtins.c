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
		exit(exitcode);
	}
	else
		printf("exit: too many arguments\n");
}
