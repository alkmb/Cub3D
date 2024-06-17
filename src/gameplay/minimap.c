/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akambou <akambou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 21:40:38 by akambou           #+#    #+#             */
/*   Updated: 2024/06/17 01:32:00 by akambou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	display_ray(t_game *game)
{
	while (game->line.k < game->line.steps)
	{
		game->line.x += game->line.xincrement;
		game->line.y += game->line.yincrement;
		mlx_pixel_put(game->data.mlx_ptr, \
		game->data.win_ptr, round(game->line.x), round(game->line.y), 0xFFFFFF);
		game->line.k++;
	}
}

void	draw_ray(t_game *game, int rayIndex, int length)
{
	game->line.ray = &game->rays[rayIndex];
	game->line.end_x = (game->player.x + length * \
	cos(game->line.ray->angle)) / 8;
	game->line.end_y = (game->player.y + length * \
	sin(game->line.ray->angle)) / 8;
	if (rayIndex < 0 || rayIndex >= game->map.width)
		return ;
	game->line.dx = game->line.end_x - (game->player.x / 8);
	game->line.dy = game->line.end_y - (game->player.y / 8);
	if (abs(game->line.dx) > abs(game->line.dy))
		game->line.steps = abs(game->line.dx);
	else
		game->line.steps = abs(game->line.dy);
	game->line.xincrement = game->line.dx / (float) game->line.steps;
	game->line.yincrement = game->line.dy / (float) game->line.steps;
	game->line.x = game->player.x / 8;
	game->line.y = game->player.y / 8;
	game->line.k = 0;
	display_ray(game);
}

void	draw_player(t_game *game, int width, int height, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			mlx_pixel_put(game->data.mlx_ptr, game->data.win_ptr, \
			(game->player.x / 8) + j, (game->player.y / 8) + i, color);
			j++;
		}
		i++;
	}
	game->map.maps /= 8;
	game->map.cellsize /= 8;
}

void	set_cell(t_game *game)
{
	game->map.cell = game->map.map[game->map.y \
	* game->map.mapx + game->map.x];
	if (game->map.cell == 1)
		game->map.color = 0x0000FF;
	else
		game->map.color = 0x808080;
	game->map.i = 0;
}

void	minimap(t_game *game)
{
	game->rays->angle = game->player.angle - (DR);
	draw_ray(game, 0, 200);
	game->rays->angle = game->player.angle + (DR);
	while (game->map.y < game->map.mapy)
	{
		game->map.x = 0;
		while (game->map.x < game->map.mapx)
		{
			set_cell(game);
			while (game->map.i < game->map.cellsize)
			{
				game->map.j = 0;
				while (game->map.j < game->map.cellsize)
				{
					my_mlx_pixel_put(&game->data, \
					game->map.x * game->map.maps + game->map.j, \
					game->map.y * game->map.maps + game->map.i, \
					game->map.color);
					game->map.j++;
				}
				game->map.i++;
			}
			game->map.j = 0;
			game->map.x++;
		}
		game->map.y++;
	}
}
