/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manumart <manumart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 11:43:38 by mbraga-s          #+#    #+#             */
/*   Updated: 2024/03/26 14:49:21 by manumart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <limits.h>
# include <linux/limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

// struct used to store the command to execute, arguments for said command
// the stdin and stdout of said command and a flag to recognise a pipe

typedef struct s_data
{
	char				**args;
	int					fd[2];
	char				**infile;
	char				**outfile;
	char				**outflag;
	char				**inflag;
	int					pid;
	struct s_data		*next;
	struct s_data		*prev;
}						t_data;

typedef struct s_global
{
	int					status;
}						t_global;

typedef struct s_envs
{
	char				**envp;
}						t_envs;

extern struct s_global	g_data;

t_envs					*msdata(void);

// utils.c

void					free_all(t_data *node);

char					*rem_allquotes(char *str);

char					**dpdup(char **str);

int						getdpsize(char **dp);

void					free_array(char **array);

t_data					*ft_lstfirst(t_data *lst);

void					check_error(char *str);

char					*ft_putstr(int fd, char *str);

// ex_utils1.c

int						searchforchar(char *str, char c);

int						is_valid(char *str);

int						pcheck(char *ptr);

char					*pathtest(char *env, char *arg);

char					*check_path(char *arg, char **envp);

int						dupcheck(int file_fd, int fd);

void					addtoenv(char *arg);

int						searchinenvp(char *input, char **envp);

void					close_fd(int *fd);

void					replace_variablefor(char **env, char *arg, int output);

// ex_utils2.c

int						file_check(int dups[2], t_data *data);

// ex_utils3.c

int						btn_redirect(t_data *data);

// ex_utils4.c

int						check_builtin(t_data *data, int fd);

int						is_builtin(t_data *data);

// executor.c

void					execution(t_data *data);

// builtins.c

void					exec_pwd(int fd);

void					exec_cd(t_data *data, int fd);

void					exec_exit(t_data *data);

void					exec_echo(t_data *data, int fd);

void					exec_env(t_data *data, int fd);

void					exec_export(t_data *data, int fd);

void					exec_unset(t_data *data);

// forks.c

void					first_fork(t_data *data, char **envp);

void					mid_fork(t_data *data, char **envp);

void					last_fork(t_data *data, char **envp);

// expander.c && exp_utils1.c

void					expander(t_data *data);

char					*get_nenv(int len, int i, char *str, char **env);

int						getunquotedlen(char *str);

int						new_funct4(int flag, char *str, int i);

// parser.c

t_data					*parser(char **token);

char					**add_args(char **args, char *token);

// heredoc.c

char					*ft_heredoc(char *str);

int						openhdoc(char *str);

// lexer.c

char					**lexer(char *str);

// syntax.c

int						syntax_checker(char **tokens);

// signals.c

void					siginthandler(int signum);

void					siginthandler2(int signum);

void					sigquithandler(int signum);
// libft

int						inv_comma(char const *ptr, int i, char c);

char					**ft_split(char const *s, char c);

char					*ft_substr(const char *s, unsigned int start,
							size_t len);

size_t					ft_strlcpy(char *dst, const char *src, size_t size);

void					*ft_calloc(size_t nmemb, size_t size);

void					ft_bzero(void *s, size_t n);

size_t					ft_strlen(const char *str);

t_data					*ft_lstnew(void);

t_data					*ft_lstadd_back(t_data **lst, t_data *new);

int						ft_lstsize(t_data *lst);

t_data					*ft_lstlast(t_data *lst);

int						ft_strncmp(const char *s1, const char *s2, size_t n);

char					*ft_strdup(const char *s);

void					*ft_memcpy(void *dest, const void *src, size_t n);

char					*ft_strjoin(char *s1, char *s2);

char					*ft_strjoinwofree(char *s1, char *s2);

int						ft_isdigit(int c);

int						ft_atoi(char *nptr);

char					*ft_strchr(const char *s, int c);

int						ft_isalnum(int c);

int						ft_strdigit(char *str);

int						ft_isalpha(int c);

char					*ft_itoa(int n);

#endif