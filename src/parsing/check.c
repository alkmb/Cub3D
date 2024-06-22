/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akambou <akambou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 03:57:05 by gprada-t          #+#    #+#             */
/*   Updated: 2024/06/21 06:36:35 by akambou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	textures_and_colors_get(t_game *game)
{
	if (game->map.north_texture && game->map.south_texture
		&& game->map.east_texture && game->map.west_texture
		&& game->map.floor.r != -1 && game->map.floor.g != -1
		&& game->map.floor.b != -1 && game->map.ceiling.r != -1
		&& game->map.ceiling.g != -1 && game->map.ceiling.b != -1)
		return (TRUE);
	return (FALSE);
}

int	is_north(t_game *game)
{
	return (game->map.map[game->rays->mp] != 7
		&& game->rays->win_i < game->map.win_h
		&& game->rays->h_length < game->rays->v_length
		&& game->rays->angle > M_PI);
}

int	is_west(t_game *game)
{
	return (game->map.map[game->rays->mp] != 7
		&& game->rays->win_i < game->map.win_h
		&& game->rays->angle > M_PI_2
		&& game->rays->angle < 3 * M_PI_2);
}

int	invalid_texture(t_game *game)
{
	game->data.n_texture = mlx_xpm_file_to_image(game->data.mlx_ptr, \
	game->map.north_texture, &game->data.texture_width, \
	&game->data.texture_height);
	if (!game->data.n_texture)
		return (cub_error("Error\nInvalid NORTH texture\n", FAILURE));
	game->data.s_texture = mlx_xpm_file_to_image(game->data.mlx_ptr, \
	game->map.south_texture, &game->data.texture_width, \
	&game->data.texture_height);
	if (!game->data.s_texture)
		return (cub_error("Error\nInvalid SOUTH texture\n", FAILURE));
	game->data.w_texture = mlx_xpm_file_to_image(game->data.mlx_ptr, \
	game->map.west_texture, &game->data.texture_width, \
	&game->data.texture_height);
	if (!game->data.w_texture)
		return (cub_error("Error\nInvalid WEST texture\n", FAILURE));
	game->data.e_texture = mlx_xpm_file_to_image(game->data.mlx_ptr, \
	game->map.east_texture, &game->data.texture_width, \
	&game->data.texture_height);
	if (!game->data.e_texture)
		return (cub_error("Error\nInvalid EAST texture\n", FAILURE));
	return (SUCCESS);
}
