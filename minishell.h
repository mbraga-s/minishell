/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraga-s <mbraga-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 11:43:38 by mbraga-s          #+#    #+#             */
/*   Updated: 2024/01/23 18:11:38 by mbraga-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <limits.h>
# include <stdarg.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>

//struct used to store the command to execute, arguments for said command
// the stdin and stdout of said command and a flag to recognise a pipe

typedef struct s_data
{
	char			*cmd;
	char			**args;
	int				fd[2];
	int				pipe_flag;
	char			*infile;
	char			*outfile;
	struct s_data	*next;
	struct s_data	*prev;
}				t_data;

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

void	init_data(t_data *node);

#endif