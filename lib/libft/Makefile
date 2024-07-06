# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gprada-t <gprada-t@student.42barcelona.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/14 09:50:01 by akambou           #+#    #+#              #
#    Updated: 2024/07/05 12:53:32 by gprada-t         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror -MMD -MP
RM = rm -rf

SRC_PATH = src/
OBJ_PATH = obj/
INC = -I includes/

SRC = ft_atof.c ft_atoi.c ft_bzero.c ft_calloc.c ft_crazy_free.c \
      ft_get_next_line.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
      ft_isdigit.c ft_ishexdigit.c ft_isprint.c ft_isspace.c ft_itoa.c \
      ft_lstadd_back_bonus.c ft_lstadd_front_bonus.c ft_lstclear_bonus.c \
      ft_lstdelone_bonus.c ft_lstiter_bonus.c ft_lstlast_bonus.c \
      ft_lstmap_bonus.c ft_lstnew_bonus.c ft_lstsize_bonus.c ft_memchr.c \
      ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c \
      ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_realloc.c \
      ft_split.c ft_strchr.c ft_strcmp.c ft_strcspn.c ft_strdup.c \
      ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c \
      ft_strmapi.c ft_strncmp.c ft_strncpy.c ft_strnstr.c ft_strpbrk.c \
      ft_strrchr.c ft_strspn.c ft_strtok.c ft_strtok_r.c ft_strtrim.c \
      ft_substr.c ft_tolower.c ft_toupper.c ft_printf.c put_numbers.c \
      put_strings.c

SRCS = $(addprefix $(SRC_PATH), $(SRC))
OBJS = $(addprefix $(OBJ_PATH), $(SRC:.c=.o))
DEPS = $(OBJS:.o=.d)

all: $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)
	@echo -e "\033[0;32m$(NAME) created 📚\033[0m"

clean:
	@$(RM) $(OBJ_PATH)
	@echo -e "\033[0;32mCleaned objects 🧹\033[0m"

fclean: clean
	@$(RM) $(NAME)
	@echo -e "\033[0;32mCleaned $(NAME) 🧹\033[0m"

re: fclean all

-include $(DEPS)

.PHONY: all clean fclean re
