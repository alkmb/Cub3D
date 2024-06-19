/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akambou <akambou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 21:12:01 by akambou           #+#    #+#             */
/*   Updated: 2024/06/19 07:07:56 by akambou          ###   ########.fr       */
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
			game->data.color = get_texture_color1((int *) \
			game->data.ceiling_addr, game->data.texture_x / 2, \
			game->data.texture_y / 4, game);
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
			game->data.texture_x / 2, game->data.texture_y / 4, game);
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
	game->map.win_w = 960;
	game->map.win_h = 640;
	game->rays->ray_width = game->map.win_w / 240;
	game->rays->line_height = (game->map.maps * \
	game->map.win_w) / game->rays->total_length * 0.7;
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

int	get_texture_color2(int *texture, int tex_x, \
int tex_y, t_game *game)
{
	int	index;

	if (tex_x < 0 || tex_x >= game->sprite.texture_width
		|| tex_y < 0 || tex_y >= game->sprite.texture_height)
		return (-1);
	index = tex_y * game->sprite.texture_width + tex_x;
	return (texture[index]);
}

void	draw_sprite(t_game *game)
{
	float sprite_x = 7 * 64;
	float sprite_y = 6 * 64;
	float relative_x = sprite_x - game->player.x;
	float relative_y = sprite_y - game->player.y;
	game->sprite.texture_width = 384;
	game->sprite.texture_height = 384;

	float distance = sqrt(relative_x * relative_x + relative_y * relative_y);
	float angle_to_sprite = atan2(relative_y, relative_x) - game->player.angle;
		if (angle_to_sprite < -M_PI)
		angle_to_sprite += 2 * M_PI;
	if (angle_to_sprite > M_PI)
		angle_to_sprite -= 2 * M_PI;
	float sprite_screen_x = (game->map.win_w / 2) + tan(angle_to_sprite) * (game->map.win_w / 2 + 10);
	float sprite_screen_y = (game->map.win_h / 2) - (1 / distance) * game->map.win_h / 2 + 24;
	if (!game->sprite.texture)
	{
		game->sprite.texture = mlx_xpm_file_to_image(game->data.mlx_ptr, \
		"./textures/doom.xpm", &game->sprite.texture_width, &game->sprite.texture_height);
		game->sprite.addr = mlx_get_data_addr(game->sprite.texture, \
		&game->sprite.bits_per_pixel, &game->sprite.line_length, &game->sprite.endian);
	}
	int x, y;
	for (y = 0; y < game->sprite.texture_height; y++)
	{
		for (x = 0; x < game->sprite.texture_width; x++)
		{
			game->data.color = get_texture_color2((int *)game->sprite.addr, x, y, game);
			if (game->data.color != 0x0000FF && (distance < game->rays->v_length 
			&& distance < game->rays->h_length && angle_to_sprite < M_PI_2 / 2 && angle_to_sprite > -M_PI_2 / 2))
				my_mlx_pixel_put(&game->data, sprite_screen_x - game->sprite.texture_width  + x, \
				sprite_screen_y - game->sprite.texture_height + y, game->data.color);
		}
	}
}


void	draw_window(t_game *game)
{
	set_window(game);
	draw_ceiling(game);
	draw_walls(game);
	draw_floor(game);
}
