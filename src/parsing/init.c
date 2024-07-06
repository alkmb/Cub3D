/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprada-t <gprada-t@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 12:51:00 by gprada-t          #+#    #+#             */
/*   Updated: 2024/06/24 21:58:31 by gprada-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	init_parsing_data(t_game *game)
{
	game->map.floor.b = -1;
	game->map.floor.g = -1;
	game->map.floor.r = -1;
	game->map.floor.color = 0;
	game->map.floor.texture = NULL;
	game->map.ceiling.g = -1;
	game->map.ceiling.b = -1;
	game->map.ceiling.r = -1;
	game->map.ceiling.color = 0;
	game->map.ceiling.texture = NULL;
	game->map.player = 0;
	game->map.north_texture = NULL;
	game->map.south_texture = NULL;
	game->map.east_texture = NULL;
	game->map.west_texture = NULL;
	game->map.map = NULL;
	game->map.temp_map = NULL;
	game->map.mapx = 0;
	game->map.mapy = 0;
	game->map.width = 0;
	game->map.height = 0;
	game->map.maps = 64;
	game->map.cellsize = 63;
}

void	init_map(t_game *game)
{
	game->map.height = (game->map.mapy * game->map.maps);
	game->map.width = (game->map.mapx * game->map.maps);
	game->map.cell = game->map.map[game->map.y * \
	game->map.mapx + game->map.x];
	game->map.cellsize = game->map.maps - 1;
}
