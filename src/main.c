/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akambou <akambou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 03:07:46 by kmb               #+#    #+#             */
/*   Updated: 2024/06/17 05:05:42 by akambou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	main(int argc, char **argv)
{
	t_game	game;
	int		fd;

	if (argc != 2)
	{
		ft_putstr_fd("Error\nInvalid number of arguments\n", 2);
		return (FAILURE);
	}
	else if (ft_strncmp(argv[1] + ft_strlen(argv[1]) - 4, ".cub", 4))
	{
		ft_putstr_fd("Error\nInvalid file extension\n", 2);
		return (FAILURE);
	}
	if (parse_file(&game, argv[1]))
		return (FAILURE);
	if (mapping(&game))
		return (cub_error("Error\nInvalid map\n", FAILURE));
	init_game(&game);
	mlx_hook(game.data.win_ptr, MotionNotify, \
	PointerMotionMask, &mouse_move, &game);
	mlx_mouse_hook(game.data.win_ptr, shoot, &game);
	mlx_hook(game.data.win_ptr, 2, 1, key_press, &game);
	mlx_mouse_hide(game.data.mlx_ptr, game.data.win_ptr);
	mlx_loop_hook(game.data.mlx_ptr, loop, &game);
	mlx_loop(game.data.mlx_ptr);
}
