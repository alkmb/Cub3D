/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akambou <akambou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 12:51:00 by gprada-t          #+#    #+#             */
/*   Updated: 2024/06/14 23:10:11 by akambou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void    init_parsing_data(t_game *game)
{
    game->map.floor.b = -1;
	game->map.floor.g = -1;
	game->map.floor.r = -1;
	game->map.floor.color = 0;
	game->map.ceiling.g = -1;
	game->map.ceiling.b = -1;
	game->map.ceiling.r = -1;
	game->map.ceiling.color = 0;
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
