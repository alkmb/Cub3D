/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akambou <akambou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 22:01:52 by akambou           #+#    #+#             */
/*   Updated: 2024/06/17 05:02:35 by akambou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	spawn_player(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map.mapy)
	{
		x = 0;
		while (x < game->map.mapx)
		{
			if (game->map.map[y * game->map.mapx + x] == 3)
			{
				game->player.x = x * game->map.maps;
				game->player.y = y * game->map.maps;
				return ;
			}
			x++;
		}
		y++;
	}
}

void	player_movement(int keycode, t_game *game)
{
	if (keycode == KEY_W)
	{
		game->player.nextx += game->player.delta_x;
		game->player.nexty += game->player.delta_y;
	}
	else if (keycode == KEY_S)
	{
		game->player.nextx -= game->player.delta_x;
		game->player.nexty -= game->player.delta_y;
	}
	else if (keycode == KEY_A)
	{
		game->player.nextx -= cos(game->player.angle + (M_PI / 2)) * 5;
		game->player.nexty -= sin(game->player.angle + (M_PI / 2)) * 5;
	}
	else if (keycode == KEY_D)
	{
		game->player.nextx += cos(game->player.angle + (M_PI / 2)) * 5;
		game->player.nexty += sin(game->player.angle + (M_PI / 2)) * 5;
	}
}

void	player_angle(int keycode, t_game *game)
{
	if (keycode == KEY_RIGHT)
	{
		game->player.angle += 0.1;
		if (game->player.angle > 2 * M_PI)
			game->player.angle -= (2 * M_PI);
		game->player.delta_x = cos(game->player.angle) * 5;
		game->player.delta_y = sin(game->player.angle) * 5;
	}
	else if (keycode == KEY_LEFT)
	{
		game->player.angle -= 0.1;
		if (game->player.angle < 0)
			game->player.angle += (2 * M_PI);
		game->player.delta_x = cos(game->player.angle) * 5;
		game->player.delta_y = sin(game->player.angle) * 5;
	}
}

int	key_press(int keycode, t_game *game)
{
	game->player.nextx = game->player.x;
	game->player.nexty = game->player.y;
	player_movement(keycode, game);
	player_angle(keycode, game);
	if (keycode == KEY_ESC)
		exit(0);
	if (!is_wall(game, game->player.nextx, game->player.nexty))
	{
		game->player.x = game->player.nextx;
		game->player.y = game->player.nexty;
	}
	return (0);
}

int	is_wall(t_game *game, float x, float y)
{
	int	mapx;
	int	mapy;

	mapx = (int)(x / game->map.maps);
	mapy = (int)(y / game->map.maps);
	return (game->map.map[mapy * game->map.width + mapx] == 1);
}
