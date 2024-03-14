# **************************************************************************** #
#	                                                                          #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: manumart <manumart@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/07 06:19:12 by manumart          #+#    #+#              #
#    Updated: 2024/03/07 06:48:58 by manumart         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC_PATH = ./srcs
OBJ_PATH = ./objects

SRCS_BUILTINS = ex_builtins ex_builtins2 exec_cd exec_echo exec_env exec_exit exec_export exec_pwd exec_unset
SRCS = utils
SRCS_LIBFT = ft_bzero ft_calloc ft_split ft_strlcpy ft_strlen ft_substr ft_lstadd_back ft_lstnew ft_lstlast ft_strncmp ft_strdup ft_memcpy ft_strjoin ft_strdigit ft_atoi ft_strchr ft_isalnum ft_isalpha ft_isdigit ft_itoa
SRCS_EXECUTION = executor forks ex_utils1 ex_utils2
SRCS_PARSING = lexer parser syntax expander exp_utils exp_utils1 heredoc

OBJS = $(addprefix $(OBJ_PATH)/, $(SRCS:=.o))
OBJS += $(addprefix $(OBJ_PATH)/, $(SRCS_LIBFT:=.o))
OBJS += $(addprefix $(OBJ_PATH)/, $(SRCS_EXECUTION:=.o))
OBJS += $(addprefix $(OBJ_PATH)/, $(SRCS_PARSING:=.o))
OBJS += $(addprefix $(OBJ_PATH)/, $(SRCS_BUILTINS:=.o))

OBJS += $(OBJ_PATH)/main.o

LIB = $(NAME).a

LIBFT_PATH = ./libft
EXEC_PATH = $(SRC_PATH)/execution
PARSE_PATH = $(SRC_PATH)/parsing
BUILTINS_PATH = $(SRC_PATH)/builtins

LIBFT = $(addprefix $(LIBFT_PATH)/, $(addsuffix .c, $(SRCS_LIBFT)))
EXEC = $(addprefix $(EXEC_PATH)/, $(addsuffix .c, $(SRCS_EXECUTION)))
PARSE = $(addprefix $(PARSE_PATH)/, $(addsuffix .c, $(SRCS_PARSING)))
BUILTINS = $(addprefix $(BUILTINS_PATH)/, $(addsuffix .c, $(SRCS_BUILTINS))) 

CC = cc
CFLAGS = -Wall -Wextra -Werror -g #-fsanitize=address
RM = rm -fr

all: $(NAME)

$(NAME): $(LIB)
	$(CC) $(CFLAGS) $(LIB) -lreadline -o $(NAME)

$(LIB): $(OBJS)
	ar rc $(LIB) $(OBJS)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c | $(OBJ_PATH)
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_PATH)/%.o: $(SRC_PATH)/execution/%.c | $(OBJ_PATH)
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@\

$(OBJ_PATH)/%.o: $(SRC_PATH)/builtins/%.c | $(OBJ_PATH)
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_PATH)/%.o: $(SRC_PATH)/parsing/%.c | $(OBJ_PATH)
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_PATH)/%.o: $(LIBFT_PATH)/%.c | $(OBJ_PATH)
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_PATH)/main.o: main.c | $(OBJ_PATH)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_PATH):
	mkdir -p $(OBJ_PATH)

clean:
	$(RM) $(OBJ_PATH)

fclean: clean
	$(RM) $(LIB) $(NAME)

re: fclean all

.PHONY: all clean fclean re

# valgrind --suppressions=readline.supp --track-fds=all --leak-check=full --show-leak-kinds=all --track-origins=yes ./minishell