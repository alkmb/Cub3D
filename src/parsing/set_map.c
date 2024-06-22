/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprada-t <gprada-t@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 15:47:08 by gprada-t          #+#    #+#             */
/*   Updated: 2024/06/19 17:01:15 by gprada-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	print_int_array(int *array, int mapx, int mapy)
{
	int	i;
	int	j;

	j = -1;
	while (++j < mapy)
	{
		i = -1;
		while (++i < mapx)
			printf("%d ", array[j * mapx + i]);
		printf("\n");
	}
}

void	clean_map(t_game *game)
{
	int	j;

	j = -1;
	while (++j < game->map.mapx * game->map.mapy)
	{
		if (game->map.map[j] == 2)
			game->map.map[j] = 1;
	}
}

int	mapping(t_game *game)
{
	while (*game->map.temp_map == '\n')
		game->map.temp_map++;
	if (!game->map.temp_map)
		return (cub_error("Error\nInvalid map\n", FAILURE));
	setting_map_x_map_y(game->map.temp_map, game);
	game->map.map = str_to_int_array(game->map.temp_map, \
	game->map.mapx, game->map.mapy);
	printf("Mapa convertido a array de enteros:\n");
	print_int_array(game->map.map, game->map.mapx, game->map.mapy);
	if (game->map.player == 0)
		return (cub_error("Error\nNo player\n", FAILURE));
	if (check_closed_map(game))
		return (cub_error("Error\nMap is open\n", FAILURE));
	clean_map(game);
	return (SUCCESS);
}
