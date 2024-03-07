# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: manumart <manumart@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/22 15:43:04 by mbraga-s          #+#    #+#              #
#    Updated: 2024/03/07 04:37:38 by manumart         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = ./srcs/utils ./srcs/builtins ./srcs/builtins2 main

SRCS_LIBFT = ft_bzero ft_calloc ft_split ft_strlcpy\
	ft_strlen ft_substr ft_lstadd_back ft_lstnew ft_lstlast\
	ft_strncmp ft_strdup ft_memcpy ft_strjoin ft_strdigit \
	ft_atoi ft_strchr ft_isalnum ft_isalpha ft_isdigit ft_itoa

SRCS_EXECUTION = executor forks ex_utils1 ex_utils2

SRCS_PARSING = lexer parser syntax expander exp_utils exp_utils1 heredoc

LIB = $(NAME).a

EXEC_PATH = ./srcs/execution

PARSE_PATH = ./srcs/parsing

LIBFT_PATH = ./libft

EXEC = $(addprefix $(EXEC_PATH)/, $(SRCS_EXECUTION))

PARSE = $(addprefix $(PARSE_PATH)/, $(SRCS_PARSING))

LIBFT = $(addprefix $(LIBFT_PATH)/, $(SRCS_LIBFT))

CC = cc
CFLAGS = -Wall -Wextra -Werror -g #-fsanitize=address
RM = rm -fr

all: $(NAME)

$(NAME): $(LIB)
		$(CC) $(CFLAGS) $(LIB) -lreadline -o $(NAME)

$(LIB): $(SRCS:=.o) $(LIBFT:=.o) $(EXEC:=.o) $(PARSE:=.o)
		ar rc $(LIB) $(SRCS:=.o) $(LIBFT:=.o) $(EXEC:=.o) $(PARSE:=.o)

clean:
	$(RM)	$(SRCS:=.o) $(LIBFT:=.o) $(EXEC:=.o) $(PARSE:=.o)

lclean:
	$(RM)	$(LIB)

fclean: clean lclean
		$(RM)	$(NAME)

re:	fclean	$(NAME)

.PHONY: clean fclean re lclean

# valgrind --suppressions=readline.supp --track-fds=all --leak-check=full --show-leak-kinds=all --track-origins=yes ./minishell