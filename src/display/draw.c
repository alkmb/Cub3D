/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprada-t <gprada-t@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 17:09:49 by gprada-t          #+#    #+#             */
/*   Updated: 2024/06/21 09:37:19 by gprada-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	draw_ceiling(t_game *game)
{
	game->rays->win_i = 0;
	while (game->rays->win_i < game->rays->line_offset)
	{
		game->rays->win_j = 0;
		while (game->rays->win_j < game->rays->ray_width)
		{
			texture_pos_cf(game);
			if (game->map.ceiling_texture)
				game->data.color = get_texture_color1((int *) \
				game->data.ceiling_addr, game->data.texture_x / 2, \
				game->data.texture_y / 4, game);
			if (game->map.ceiling_texture)
				my_mlx_pixel_put(&game->data, game->rays->ray * \
				game->rays->ray_width + game->rays->win_j, \
				game->rays->win_i, game->data.color);
			else
				my_mlx_pixel_put(&game->data, game->rays->ray * \
				game->rays->ray_width + game->rays->win_j, \
				game->rays->win_i, game->map.ceiling.color);
			game->rays->win_j++;
		}
		game->rays->win_i++;
	}
}

void	draw_floor(t_game *game)
{
	while (game->rays->win_i < game->map.win_h)
	{
		game->rays->win_j = 0;
		while (game->rays->win_j < game->rays->ray_width)
		{
			texture_pos_cf(game);
			if (game->map.floor_texture)
				game->data.color = get_texture_color1((int *) \
				game->data.floor_addr, \
				game->data.texture_x / 2, game->data.texture_y / 4, game);
			if (game->map.floor_texture)
				my_mlx_pixel_put(&game->data, game->rays->ray * \
				game->rays->ray_width + game->rays->win_j, \
				game->rays->win_i, game->data.color);
			else
				my_mlx_pixel_put(&game->data, game->rays->ray * \
				game->rays->ray_width + game->rays->win_j, \
				game->rays->win_i, game->map.floor.color);
			game->rays->win_j++;
		}
		game->rays->win_i++;
	}
}

void	draw_walls(t_game *game)
{
	while (game->rays->win_i < \
	game->rays->line_height + game->rays->line_offset)
	{
		game->rays->win_j = 0;
		while (game->rays->win_j < game->rays->ray_width)
		{
			select_wall(game);
			my_mlx_pixel_put(&game->data, game->rays->ray * \
			game->rays->ray_width + game->rays->win_j, \
			game->rays->win_i, game->data.color);
			game->rays->win_j++;
		}
		game->rays->win_i++;
	}
}

void	draw_window(t_game *game)
{
	set_window(game);
	draw_ceiling(game);
	draw_walls(game);
	draw_floor(game);
}
