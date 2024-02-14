/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraga-s <mbraga-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 11:43:38 by mbraga-s          #+#    #+#             */
/*   Updated: 2024/02/14 14:17:22 by mbraga-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <limits.h>
# include <linux/limits.h>
# include <stdarg.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

//struct used to store the command to execute, arguments for said command
// the stdin and stdout of said command and a flag to recognise a pipe

typedef struct s_data
{
	char			**args;
	int				fd[2];
	char			*infile;
	char			*outfile;
	struct s_data	*next;
	struct s_data	*prev;
}				t_data;

//utils.c

void	free_all(t_data *node);

t_data	*ft_lstfirst(t_data *lst);

//ex_utils.c

int		pcheck(char *ptr);

char	*pathtest(char *env, char *arg);

char	*check_path(char *arg, char **envp);

int		dupcheck(int file_fd, int fd);

void	close_fd(int *fd);

//builtins.c

void	exec_pwd(void);

void	exec_cd(t_data *data);

void	exec_exit(t_data *data);

//forks.c

void	file_check(int dups[2], t_data *data);

void	first_fork(t_data *data, char **envp);

void	mid_fork(t_data *data, char **envp);

void	last_fork(t_data *data, char **envp);

//expander.c

void	expander(t_data *data);

//parser.c

t_data	*parser(char **token);

char	**add_args(char **args, char *token);

//lexer.c

char	**lexer(char *str);

//libft

int		inv_comma(char const *ptr, int i, char c);

char	**ft_split(char const *s, char c);

char	*ft_substr(const char *s, unsigned int start, size_t len);

size_t	ft_strlcpy(char *dst, const char *src, size_t size);

void	*ft_calloc(size_t nmemb, size_t size);

void	ft_bzero(void *s, size_t n);

size_t	ft_strlen(const char *str);

t_data	*ft_lstnew(void);

void	ft_lstadd_back(t_data **lst, t_data *new);

int		ft_lstsize(t_data *lst);

t_data	*ft_lstlast(t_data *lst);

int		ft_strncmp(const char *s1, const char *s2, size_t n);

char	*ft_strdup(const char *s);

void	*ft_memcpy(void *dest, const void *src, size_t n);

char	*ft_strjoin(char *s1, char *s2);

int		ft_isdigit(char *str);

int		ft_atoi(char *nptr);

#endif