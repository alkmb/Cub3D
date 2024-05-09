NAME	= cub3d

CC		= gcc
CFLAGS	= -Werror -Wextra -Wall -fsanitize=address
RM		= rm -rf

MLX_PATH	= lib/minilibx
MLX_NAME	= libmlx.a
MLX			= $(MLX_PATH)$(MLX_NAME)
LIBFT_PATH	= lib/libft/
LIBFT_NAME	= libft.a
LIBFT		= $(LIBFT_PATH)$(LIBFT_NAME)
INC			=	-I ./includes/\

SRC_PATH	=	src/
SRC			=	$(wildcard $(SRC_PATH)*.c $(SRC_PATH)*/*.c)
OBJ_PATH	= obj/
OBJ			= $(SRC:$(SRC_PATH)%.c=$(OBJ_PATH)%.o)

all: $(MLX) $(LIBFT) $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@$(CC) $(CFLAGS) -c $< -o $@ $(INC) > /dev/null

$(OBJ_PATH):
	@mkdir -p $(OBJ_PATH) > /dev/null

$(MLX):
	@make -C $(MLX_PATH) > /dev/null

$(LIBFT):
	@make -C $(LIBFT_PATH) > /dev/null

$(NAME): $(OBJ_PATH) $(OBJ)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -L $(MLX_PATH) -lmlx -L $(LIBFT_PATH) \
	-lft -lX11 -lXpm -lXext -lm > /dev/null
	@echo -e "\033[0;32m$(NAME) created 📚\033[0m"

clean:
	@$(RM) $(OBJ_PATH)
	@make clean -C $(MLX_PATH) > /dev/null
	@make clean -C $(LIBFT_PATH) > /dev/null
	@echo -e "\033[0;32mCleaned objects 🧹\033[0m"

fclean: clean
	@$(RM) $(NAME)
	@echo -e "\033[0;32mCleaned $(NAME) 🧹\033[0m"

re: fclean all

.PHONY: all clean fclean re
