/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akambou <akambou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 21:12:01 by akambou           #+#    #+#             */
/*   Updated: 2024/06/17 01:42:04 by akambou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	draw_cealing(t_game *game)
{
	game->rays->win_i = 0;
	while (game->rays->win_i < game->rays->line_offset)
	{
		game->rays->win_j = 0;
		while (game->rays->win_j < game->rays->ray_width)
		{
			texture_pos_cf(game);
			game->data.color = get_texture_color1((int *) \
			game->data.ceiling_addr, game->data.texture_x / 3, \
			game->data.texture_y / 3, game);
			my_mlx_pixel_put(&game->data, game->rays->ray * \
			game->rays->ray_width + game->rays->win_j, \
			game->rays->win_i, game->data.color);
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
			game->data.color = get_texture_color1((int *)game->data.floor_addr, \
			game->data.texture_x / 3, game->data.texture_y / 3, game);
			my_mlx_pixel_put(&game->data, game->rays->ray * \
			game->rays->ray_width + game->rays->win_j, \
			game->rays->win_i, game->data.color);
			game->rays->win_j++;
		}
		game->rays->win_i++;
	}
}

void	set_window(t_game *game)
{
	if (game == NULL || game->rays == NULL || game->rays->total_length == 0)
		return ;
	game->map.win_w = 1200;
	game->map.win_h = 800;
	game->rays->ray_width = game->map.win_w / 120;
	game->rays->line_height = (game->map.maps * \
	game->map.win_w) / game->rays->total_length * 0.35;
	if (game->rays->line_height > game->map.win_h)
		game->rays->line_height = game->map.win_h;
	if (game->rays->line_height == 0)
		return ;
	game->rays->line_offset = game->map.win_h / 2 - game->rays->line_height / 2;
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
	draw_cealing(game);
	draw_walls(game);
	draw_floor(game);
}
