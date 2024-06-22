NAME	= cub3d

CC		= gcc
CFLAGS	= -O3 -fsanitize=address -MMD -MP
RM		= rm -rf

MLX_PATH	= lib/minilibx/
#MLX_PATH	= lib/minilibx_mac/
MLX_NAME	= libmlx.a
MLX			= $(MLX_PATH)$(MLX_NAME)
LIBFT_PATH	= lib/libft/
LIBFT_NAME	= libft.a
LIBFT		= $(LIBFT_PATH)$(LIBFT_NAME)
INC			=	-I ./includes/ -I ./lib/minilibx/ -I ./lib/libft/

DISPLAY		= draw init_window sprites texture window
GAMEPLAY	= hud minimap player
PARSING		= check_closed_map check color_text fill_map init parsing set_map set_x_and_y
RAYCAST		= caster horizontal vertical
UTILS		= utils utilsplayer
MAIN		= main

F_DISPLAY	= $(addprefix src/display/, $(DISPLAY))
F_GAMEPLAY	= $(addprefix src/gameplay/, $(GAMEPLAY))
F_PARSING	= $(addprefix src/parsing/, $(PARSING))
F_RAYCAST	= $(addprefix src/raycast/, $(RAYCAST))
F_UTILS		= $(addprefix src/utils/, $(UTILS))
F_MAIN		= $(addprefix src/, $(MAIN))

SRCS		= $(addsuffix .c, $(F_DISPLAY) $(F_GAMEPLAY) $(F_PARSING) $(F_RAYCAST) $(F_UTILS) $(F_MAIN))

OBJ_PATH	= obj/
OBJS		= $(addprefix $(OBJ_PATH), $(notdir $(SRCS:.c=.o)))
DEPS		= $(OBJS:.o=.d)

all: $(MLX) $(LIBFT) $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@ $(INC)

$(OBJ_PATH)%.o: src/display/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@ $(INC)

$(OBJ_PATH)%.o: src/gameplay/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@ $(INC)

$(OBJ_PATH)%.o: src/parsing/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@ $(INC)

$(OBJ_PATH)%.o: src/raycast/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@ $(INC)

$(OBJ_PATH)%.o: src/utils/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@ $(INC)

$(OBJ_PATH)%.o: src/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@ $(INC)

$(MLX):
	@make -C $(MLX_PATH)

$(LIBFT):
	@make -C $(LIBFT_PATH)

$(NAME): $(OBJS) Makefile $(MLX) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -L./lib/libft -lft -L./$(MLX_PATH) -lmlx -L/usr/include/../lib -lXext -lX11 -lm -lbsd
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

-include $(DEPS)

.PHONY: all clean fclean re
