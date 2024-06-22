/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akambou <akambou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 17:08:19 by gprada-t          #+#    #+#             */
/*   Updated: 2024/06/21 06:05:01 by akambou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	find_sprite(t_game *game)
{
	int	i;
	int	j;

	i = -1;
	while (++i < game->map.mapy)
	{
		j = -1;
		while (++j < game->map.mapx)
		{
			if (game->map.map[i * game->map.mapx + j] == 8)
			{
				game->sprite.sprite_x = j * 64;
				game->sprite.sprite_y = i * 64;
			}
		}
	}
}

void	calculate_sprite_position(t_game *game)
{
	game->sprite.relative_x = game->sprite.sprite_x - game->player.x;
	game->sprite.relative_y = game->sprite.sprite_y - game->player.y;
	game->sprite.distance = sqrt(game->sprite.relative_x * \
	game->sprite.relative_x + game->sprite.relative_y * \
	game->sprite.relative_y);
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

void	draw_sprite(t_game *game)
{
	find_sprite(game);
	calculate_sprite_position(game);
	get_sprite(game);
	game->sprite.y = 0;
	while (game->sprite.y < game->sprite.texture_height)
	{
		game->sprite.x = 0;
		while (game->sprite.x < game->sprite.texture_width)
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
