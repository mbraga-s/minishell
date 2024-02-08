# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbraga-s <mbraga-s@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/22 15:43:04 by mbraga-s          #+#    #+#              #
#    Updated: 2024/02/08 20:26:20 by mbraga-s         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = lexer parser expander testing

SRCS_LIBFT = ft_bzero ft_calloc ft_split ft_strlcpy\
	ft_strlen ft_substr ft_lstadd_back ft_lstnew ft_lstlast\
	ft_strncmp ft_strdup ft_memcpy

LIBFT_PATH = ./libft

LIB = $(NAME).a

LIBFT = $(addprefix $(LIBFT_PATH)/, $(SRCS_LIBFT))

CC = cc
CFLAGS = -Wall -Wextra -Werror -g -lreadline -fsanitize=address

RM = rm -fr

all: $(NAME)

$(NAME): $(LIB)
		$(CC) $(CFLAGS) $(LIB) -o $(NAME)

$(LIB): $(SRCS:=.o) $(LIBFT:=.o)
		ar rc $(LIB) $(SRCS:=.o) $(LIBFT:=.o)

clean:
	$(RM)	$(SRCS:=.o) $(LIBFT:=.o)

lclean:
	$(RM)	$(LIB)

fclean: clean lclean
		$(RM)	$(NAME)

re:	fclean	$(NAME)

.PHONY: clean fclean re