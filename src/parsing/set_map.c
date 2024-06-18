/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akambou <akambou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 15:47:08 by gprada-t          #+#    #+#             */
/*   Updated: 2024/06/17 17:00:10 by akambou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int		calculate_size(const char *map)
{
	int	i;
	int	size;

	i = -1;
	size = 0;
	while (map[++i])
	{
		if (map[i] != '\t' && map[i] != '\n')
			size++;
		else if (map[i] == '\t')
			size += 4;
	}
	return (size);
}

int		*str_to_int_array(char *map, int max_x)
{
	int i;
	int j;
	int *array;
	int len;
	int index;
	
	i = 0;
	j = 0;
	len = calculate_size(map) * 4;
	printf("mapsize-->: %d\n", len);
	array = malloc(sizeof(int) * len * 2);
	if (!array)
		return (NULL);
	i = 0;
	index = 0;
	while (map[i] && index < len)
	{
		if (map[i] == '0') {
			array[index++] = 0;
		}
		else if (map[i] == '1')
			array[index++] = 1;
		else if (map[i] == 'N' || map[i] == 'S' || map[i] == 'W' || map[i] == 'E')
			array[index++] = 3;
		else if (map[i] == ' ')
			array[index++] = 2;
		else if (map[i] == '\n' && (index % max_x) != 0)
			while (index % max_x != 0)
				array[index++] = 2;
		else if (map[i] == '\t') {
			for (int k = 0; k < 4; k++){
				array[index++] = 2;
			}
		}
		else if (map[i] == 'D')
			array[index++] = 7;
		else if (map[i] == 'C')
			array[index++] = 8;
		else if (map[i] == 'P')
			array[index++] = 9;
		i++;
	}
	return (array);
}

void	setting_map_x_map_y(char *str_map, t_game *game)
{
	int i;
	int line = 0;

	i = -1;
	while (str_map[++i])
	{
		if (str_map[i] == '\n')
		{
			if (line > game->map.mapx)
				game->map.mapx = line;
			line = 0;
			game->map.mapy++;
		}
		else
		{
			if (str_map[i] == '\t')
				line += 4;
			else
				line++;
		}
	}
	game->map.mapy ++;
}

int		check_closed_map(t_game *game)
{
	int i;
	int j;

	i = 0;
	if (game->map.mapx < 3 || game->map.mapy < 3)
		return (cub_error("Error\nToo Small map\n", FAILURE));
	while (i < game->map.mapx * game->map.mapy)
	{
		if (game->map.map[i] == 0 && (game->map.map[i + 1] == 2 || game->map.map[i - 1] == 2))
			return (cub_error("Error\nInvalid map\n", FAILURE));
		i++;
	}
	return (SUCCESS);
}

int		mapping(t_game *game)
{
	while (*game->map.temp_map == '\n')
		game->map.temp_map++;
	if (!game->map.temp_map)
		return (cub_error("Error\nInvalid map\n", FAILURE));
	int i = 0;
	while (game->map.temp_map[i])
	{
		if ((game->map.temp_map[i] == '\n' && game->map.temp_map[i + 1] == '\0') \
			|| (game->map.temp_map[i] == '\n' && game->map.temp_map[i + 1] == '\n'))
			game->map.temp_map[i] = '\0';
		i++;
	}
	setting_map_x_map_y(game->map.temp_map, game);
	game->map.map = str_to_int_array(game->map.temp_map, game->map.mapx);
	//if (check_closed_map(game))
	//	return (cub_error("Error\nMap is open\n", FAILURE));
	return (SUCCESS);
}
