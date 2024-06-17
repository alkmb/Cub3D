/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akambou <akambou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 22:52:13 by akambou           #+#    #+#             */
/*   Updated: 2024/06/17 13:16:07 by akambou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	set_horizontal(t_game *game)
{
	game->rays->mx = (int)game->rays->ray_x >> 6;
	game->rays->my = (int)game->rays->ray_y >> 6;
	if (game->rays->mx >= 0 && game->rays->mx < game->map.width
		&& game->rays->my >= 0 && game->rays->my < game->map.height)
		game->rays->mp = game->rays->my * game->map.width + game->rays->mx;
}

void	cast_horizontal(t_game *game)
{
	while (game->rays->deapht_of_field < 30)
	{
		set_horizontal(game);
		if (game->rays->mp > 0 && game->rays->mp < game->map.width * \
		game->map.height && (game->map.map[game->rays->mp] == 1 || \
		(game->map.map[game->rays->mp] == 7)))
		{
			game->rays->horizontal_x = game->rays->ray_x;
			game->rays->horizontal_y = game->rays->ray_y;
			game->rays->h_length = distance(game->player.x, \
			game->player.y, game->rays->horizontal_x, game->rays->horizontal_y);
			game->rays->deapht_of_field = 30;
		}
		else
		{
			game->rays->ray_x += game->rays->x_offset;
			game->rays->ray_y += game->rays->y_offset;
			game->rays->h_length = distance(game->player.x, \
			game->player.y, game->rays->ray_x, game->rays->ray_y);
			game->rays->deapht_of_field++;
		}
	}
}

void	horizontal_direction(t_game *game)
{
	float	atan;

	atan = -1 / tan(game->rays->angle);
	if (game->rays->angle > M_PI)
	{
		game->rays->ray_y = (((int)game->player.y >> 6) << 6) - 0.0001;
		game->rays->ray_x = (game->player.y - game->rays->ray_y) * \
		atan + game->player.x;
		game->rays->y_offset = -64;
		game->rays->x_offset = -game->rays->y_offset * atan;
	}
	if (game->rays->angle < M_PI)
	{
		game->rays->ray_y = (((int)game->player.y >> 6) << 6) + 64;
		game->rays->ray_x = (game->player.y - game->rays->ray_y) * \
		atan + game->player.x;
		game->rays->y_offset = 64;
		game->rays->x_offset = -game->rays->y_offset * atan;
	}
	if (game->rays->angle == 0 || game->rays->angle == M_PI)
	{
		game->rays->ray_x = game->player.x;
		game->rays->ray_y = game->player.y;
		game->rays->deapht_of_field = 30;
	}
}

void	reset_horizontal(t_game *game)
{
	game->rays->h_length = 200000000;
	game->rays->horizontal_x = game->player.x;
	game->rays->horizontal_y = game->player.y;
	game->rays->deapht_of_field = 0;
}
