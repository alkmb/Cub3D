/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akambou <akambou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 21:12:01 by akambou           #+#    #+#             */
/*   Updated: 2024/06/19 08:04:46 by akambou          ###   ########.fr       */
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
	game->map.win_w = 1200;
	game->map.win_h = 800;
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

void find_sprite(t_game *game)
{
	for (int i = 0; i < game->map.mapy; i++)
	{
		for (int j = 0; j < game->map.mapx; j++)
		{
			if (game->map.map[i * game->map.mapx + j] == 8)
			{
				game->sprite.sprite_x = j * 64;
				game->sprite.sprite_y = i * 64;
			}
		}
	}
}

void calculate_sprite_position(t_game *game)
{
	game->sprite.relative_x = game->sprite.sprite_x - game->player.x;
	game->sprite.relative_y = game->sprite.sprite_y - game->player.y;

	game->sprite.distance = sqrt(game->sprite.relative_x * \
	game->sprite.relative_x + game->sprite.relative_y * \
	game->sprite.relative_y);
	printf("distance: %f\n", game->sprite.distance);

	game->sprite.angle_to_sprite = atan2(game->sprite.relative_y, \
	game->sprite.relative_x) - game->player.angle;
	if (game->sprite.angle_to_sprite < -M_PI)
		game->sprite.angle_to_sprite += 2 * M_PI;
	if (game->sprite.angle_to_sprite > M_PI)
		game->sprite.angle_to_sprite -= 2 * M_PI;

	game->sprite.sprite_screen_x = (game->map.win_w / 2) + \
	tan(game->sprite.angle_to_sprite) * (game->map.win_w / 2 + 10);
	game->sprite.sprite_screen_y = (game->map.win_h / 2) - \
	(1 / game->sprite.distance) * game->map.win_h / 2 + 128;
}

void	get_sprite(t_game *game)
{
	if (!game->sprite.texture)
	{
		game->sprite.texture = mlx_xpm_file_to_image(game->data.mlx_ptr, \
		"./textures/doom.xpm", &game->sprite.texture_width, \
		&game->sprite.texture_height);
		game->sprite.addr = mlx_get_data_addr(game->sprite.texture, \
		&game->sprite.bits_per_pixel, &game->sprite.line_length, \
		&game->sprite.endian);
	}
}

void draw_sprite(t_game *game)
{
	find_sprite(game);
	calculate_sprite_position(game);
	get_sprite(game);
	game->sprite.y = 0;
	while (game->sprite.y < game->sprite.texture_height)
	{
		game->sprite.x = 0;
		while ( game->sprite.x < game->sprite.texture_width)
		{
			game->data.color = get_texture_color2((int *)game->sprite.addr, \
			game->sprite.x, game->sprite.y, game);
			if (game->data.color != 0x0000FF && (game->sprite.distance < \
			game->rays->v_length 
			&& game->sprite.distance < game->rays->h_length && \
			game->sprite.angle_to_sprite < M_PI_2 / 2 
			&& game->sprite.angle_to_sprite > -M_PI_2 / 2))
				my_mlx_pixel_put(&game->data, game->sprite.sprite_screen_x - \
				game->sprite.texture_width + game->sprite.x, \
				game->sprite.sprite_screen_y - game->sprite.texture_height + \
				game->sprite.y, game->data.color);
				game->sprite.x++;
		}
		game->sprite.y++;
	}
}


void	draw_window(t_game *game)
{
	set_window(game);
	draw_ceiling(game);
	draw_walls(game);
	draw_floor(game);
}
