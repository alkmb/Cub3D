/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akambou <akambou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 03:07:46 by kmb               #+#    #+#             */
/*   Updated: 2024/07/02 04:03:11 by akambou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	check_before_init(t_game *game)
{
	if (game->map.ceiling_texture && game->map.floor_texture)
		return (SUCCESS);
	else if (!game->map.ceiling_texture && game->map.ceiling.color > -1)
		return (SUCCESS);
	else if (!game->map.floor_texture && game->map.floor.color > -1)
		return (SUCCESS);
	else
		return (cub_error("Error\nInvalid texture or color\n", FAILURE));
}

int	parser(t_game *game, char **argv)
{
	if (parse_file(game, argv[1]))
		return (FAILURE);
	if (!game->map.temp_map)
		return (FAILURE);
	if (check_before_init(game))
		return (FAILURE);
	if (mapping(game))
		return (FAILURE);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		return (cub_error("Error\nInvalid number of arguments\n", FAILURE));
	else if (ft_strncmp(argv[1] + ft_strlen(argv[1]) - 4, ".cub", 4))
		cub_error("Error\nInvalid file extension\n", FAILURE);
	parser(&game, argv);
	init_game(&game);
	mlx_hook(game.data.win_ptr, MotionNotify, \
	PointerMotionMask, &mouse_move, &game);
	mlx_mouse_hook(game.data.win_ptr, shoot, &game);
	mlx_hook(game.data.win_ptr, 2, 1, key_press, &game);
	mlx_loop_hook(game.data.mlx_ptr, loop, &game);
	mlx_loop(game.data.mlx_ptr);
	return (SUCCESS);
}
