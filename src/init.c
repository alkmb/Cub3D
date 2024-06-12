/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprada-t <gprada-t@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 12:51:00 by gprada-t          #+#    #+#             */
/*   Updated: 2024/06/10 12:40:06 by gprada-t         ###   ########.fr       */
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
	game->map.mapX = 0;
	game->map.mapY = 0;
	game->map.width = 0;
	game->map.height = 0;
	game->map.mapS = 64;
	game->map.cellSize = 63;
}
