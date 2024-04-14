/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraga-s <mbraga-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 11:43:38 by mbraga-s          #+#    #+#             */
/*   Updated: 2024/04/14 16:05:44 by mbraga-s         ###   ########.fr       */
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

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

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
	int					fd_in;
	int					fd_out;
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
	t_data				*strut;
	int					hd_signal;
	int					shlvl;
}						t_envs;

extern struct s_global	g_data;

t_envs					*msdata(void);

// utils.c

void					free_all(t_data *node);

t_data					*ft_lstfirst(t_data *lst);

char					*ft_putstr(int fd, char *str);

void					check_error(char *str);

void					getshlvl(void);

// ex_utils1.c

int						dupcheck(int file_fd, int fd);

void					close_fd(int *fd);

char					*check_path(char *arg, char **envp);

// ex_utils2.c

int						file_check(int dups[2], t_data *data);

// ex_utils3.c

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

char					**sortenvp(char **envpsorted, int envp_size);

// builtin_utils

int						searchforchar(char *str, char c);

int						is_valid(char *str);

void					addtoenv(char *arg);

int						searchinenvp(char *input, char **envp);

void					replace_variablefor(char **env, char *arg, int output);

char					*rem_allquotes(char *str);

char					**dpdup(char **str);

int						getdpsize(char **dp);

void					free_array(char **array);

// forks.c

void					first_fork(t_data *data, char **envp);

void					mid_fork(t_data *data, char **envp);

void					last_fork(t_data *data, char **envp);

// expander.c

void					expander(t_data *data);

char					*get_nenv(int len, int i, char *str, char **env);

int						getunquotedlen(char *str);

int						new_funct4(int flag, char *str, int i);

char					*rem_quotes(char *str);

char					*expand(char *str, char **envp);

// parser.c

t_data					*parser(char **token);

char					**add_args(char **args, char *token);

// heredoc.c

int						ft_heredoc(char *str, t_data *data);

// lexer.c

char					**lexer(char *str);

// syntax.c

int						syntax_checker(char **tokens);

// signals.c

void					sigintmain(int signum);

void					siginthd(int signum);

void					signalhandlechild(void);

// redirections.c

void					redirections(t_data *data);

void					close_all(t_data *data);

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

char					*ft_stjnf(char *s1, char *s2);

int						ft_isdigit(int c);

int						ft_atoi(char *nptr);

char					*ft_strchr(const char *s, int c);

int						ft_isalnum(int c);

int						ft_strdigit(char *str);

int						ft_isalpha(int c);

char					*ft_itoa(int n);

char					*get_next_line(int fd);

#endif