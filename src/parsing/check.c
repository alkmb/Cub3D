/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprada-t <gprada-t@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 03:57:05 by gprada-t          #+#    #+#             */
/*   Updated: 2024/06/19 03:04:58 by gprada-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

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
