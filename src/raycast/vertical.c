/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertical.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akambou <akambou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 22:44:22 by akambou           #+#    #+#             */
/*   Updated: 2024/06/15 00:01:28 by akambou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	set_vertical(t_game *game)
{
	game->rays->mx = (int)game->rays->ray_x >> 6;
	game->rays->my = (int)game->rays->ray_y >> 6;
	if (game->rays->mx >= 0 && game->rays->mx < game->map.width
		&& game->rays->my >= 0 && game->rays->my < game->map.height)
		game->rays->mp = game->rays->my * game->map.width + game->rays->mx;
}

void	cast_vertical(t_game *game)
{
	while (game->rays->deapht_of_field < 30)
	{
		set_vertical(game);
		if (game->rays->mp > 0 && game->rays->mp < \
		game->map.width * game->map.height \
		&& game->map.map[game->rays->mp] == 1)
		{
			game->rays->vertical_x = game->rays->ray_x;
			game->rays->vertical_y = game->rays->ray_y;
			game->rays->v_length = distance(game->player.x, game->player.y, \
			game->rays->vertical_x, game->rays->vertical_y);
			game->rays->deapht_of_field = 30;
		}
		else
		{
			game->rays->ray_x += game->rays->x_offset;
			game->rays->ray_y += game->rays->y_offset;
			game->rays->v_length = distance(game->player.x, game->player.y, \
			game->rays->ray_x, game->rays->ray_y);
			game->rays->deapht_of_field++;
		}
	}
}

void	vertical_direction(t_game *game)
{
	float	ntan;

	ntan = -tan(game->rays->angle);
	if (game->rays->angle > M_PI_2 && game->rays->angle < 3 * M_PI_2)
	{
		game->rays->ray_x = (((int)game->player.x >> 6) << 6) - 0.0001;
		game->rays->ray_y = (game->player.x - game->rays->ray_x) * \
		ntan + game->player.y;
		game->rays->x_offset = -64;
		game->rays->y_offset = -game->rays->x_offset * ntan;
	}
	if (game->rays->angle < M_PI_2 || game->rays->angle > 3 * M_PI_2)
	{
		game->rays->ray_x = (((int)game->player.x >> 6) << 6) + 64;
		game->rays->ray_y = (game->player.x - game->rays->ray_x) * \
		ntan + game->player.y;
		game->rays->x_offset = 64;
		game->rays->y_offset = -game->rays->x_offset * ntan;
	}
	if (game->rays->angle == M_PI_2 || game->rays->angle == 3 * M_PI_2)
	{
		game->rays->ray_x = game->player.x;
		game->rays->ray_y = game->player.y;
		game->rays->deapht_of_field = 30;
	}
}

void	reset_vertical(t_game *game)
{
	game->rays->v_length = 200000000;
	game->rays->vertical_x = game->player.x;
	game->rays->vertical_y = game->player.y;
	game->rays->deapht_of_field = 0;
}
