NAME	= cub3d

CC		= gcc
CFLAGS	= -O3 -fsanitize=address#-Werror -Wextra -Wall
RM		= rm -rf

MLX_PATH	= lib/minilibx/
#MLX_PATH	= lib/minilibx_mac/
MLX_NAME	= libmlx.a
MLX			= $(MLX_PATH)$(MLX_NAME)
LIBFT_PATH	= lib/libft/
LIBFT_NAME	= libft.a
LIBFT		= $(LIBFT_PATH)
INC			=	-I ./includes/ -I ./lib/minilibx/ -I ./lib/libft/

SRC_PATH	=	src/
SRC			=	$(shell find $(SRC_PATH) -name "*.c")
OBJ_PATH	=	obj/
OBJ			=	$(SRC:$(SRC_PATH)%.c=$(OBJ_PATH)%.o)

all: $(MLX) $(LIBFT) $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@ $(INC)

$(OBJ_PATH):
	@mkdir -p $(OBJ_PATH)

$(MLX):
	@make -C $(MLX_PATH)

$(LIBFT):
	@make -C $(LIBFT_PATH)

$(NAME): $(OBJ_PATH) $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -L./lib/libft -lft -L./$(MLX_PATH) -lmlx -L/usr/include/../lib -lXext -lX11 -lm -lbsd
	@echo -e "\033[0;32m$(NAME) created 📚\033[0m"

#$(NAME): $(OBJ_PATH) $(OBJ)
#	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -L $(MLX_PATH) -lmlx1-framework Cocoa -framework OpenGL -framework IOKit -lm > /dev/null

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
