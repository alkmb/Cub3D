/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprada-t <gprada-t@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 03:07:46 by kmb               #+#    #+#             */
/*   Updated: 2024/06/18 18:07:52 by gprada-t         ###   ########.fr       */
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
		return (FAILURE);//free
	if (mapping(&game))
		return (FAILURE);//free
	init_game(&game);
	mlx_hook(game.data.win_ptr, MotionNotify, \
	PointerMotionMask, &mouse_move, &game);
	mlx_mouse_hook(game.data.win_ptr, shoot, &game);
	mlx_hook(game.data.win_ptr, 2, 1, key_press, &game);
	mlx_mouse_hide(game.data.mlx_ptr, game.data.win_ptr);
	mlx_loop_hook(game.data.mlx_ptr, loop, &game);
	mlx_loop(game.data.mlx_ptr);
	return (SUCCESS);
}
