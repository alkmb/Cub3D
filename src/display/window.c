/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprada-t <gprada-t@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 21:12:01 by akambou           #+#    #+#             */
/*   Updated: 2024/06/19 17:11:13 by gprada-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

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
