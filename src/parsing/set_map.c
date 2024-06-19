/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akambou <akambou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 15:47:08 by gprada-t          #+#    #+#             */
/*   Updated: 2024/06/19 07:18:24 by akambou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	*str_to_int_array(char *map, int x, int y)
{
	int	i;
	int	index;
	int	*array;

	i = 0;
	index = 0;
	array = malloc(sizeof(int) * (x * y + 1));
	if (!array)
		return (NULL);
	while (map[i] && index < (x * y + 1))
	{
		if (map[i] == '0')
			array[index++] = 0;
		else if (map[i] == '1')
			array[index++] = 1;
		else if (map[i] == 'N' || map[i] == 'S'
			|| map[i] == 'W' || map[i] == 'E')
			array[index++] = 3;
		else if (map[i] == ' ')
			array[index++] = 2;
		else if (map[i] == '\n')
			while ((index % x) != 0)
				array[index++] = 2;
		else if (map[i] == '\t')
			for (int k = 0; k < 4; k++)
				array[index++] = 2;
		else if (map[i] == 'D')
			array[index++] = 7;
		else if (map[i] == 'O')
			array[index++] = 8;
		i++;
	}
	return (array);
}

void	setting_map_x_map_y(char *str_map, t_game *game)
{
	int	i;
	int	line;

	i = 0;
	line = 0;
	while (str_map[i] == '\n')
		i++;
	while (str_map[i])
	{
		if (str_map[i] == '\n')
		{
			while (str_map[i] == '\n' && str_map[i + 1] == '\n')
				i++;
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
		i++;
	}
	if (line > 0)
	{
		if (line > game->map.mapx)
			game->map.mapx = line;
		game->map.mapy++;
	}
	game->map.mapy;
}

void	print_int_array(int *array, int mapx, int mapy)
{
	for (int j = 0; j < mapy; j++) {
		for (int i = 0; i < mapx; i++) {
			printf("%d ", array[j * mapx + i]);
		}
	printf("\n");
	}
}

int	check_closed_map(t_game *game)
{
	int	i;
	int	j;
	int	idx;

	j = 0;
	i = 0;
	idx = 0;
	if (game->map.mapx < 3 || game->map.mapy < 3)
		return (cub_error("Error\nToo Small map\n", FAILURE));
	while (j < game->map.mapy)
	{
		i = 0;
		while (i < game->map.mapx)
		{
			idx = j * game->map.mapx + i;
			if (game->map.map[idx] == 0)
			{
				if (i == 0 || i == game->map.mapx - 1 || j == 0
					|| j == game->map.mapy - 1)
					return (cub_error("Error\nInvalid map: Open bord\
					ers\n", FAILURE));
				if (i > 0 && game->map.map[idx - 1] == 2)
					return (cub_error("Error\nInvalid map: AAA Near\
					 forbidden element\n", FAILURE));
				if (i < game->map.mapx - 1 && game->map.map[idx + 1] == 2)
					return (cub_error("Error\nInvalid map: BBB Near forbidd\
					en element\n", FAILURE));
				if (j > 0 && game->map.map[idx - game->map.mapx] == 2)
					return (cub_error("Error\nInvalid map: Near forbidden \
					element\n", FAILURE));
				if (j < game->map.mapy - 1
					&& game->map.map[idx + game->map.mapx] == 2)
					return (cub_error("Error\nInvalid map: Near forbidden \
					element\n", FAILURE));
			}
			i++;
		}
		j++;
	}
	return (SUCCESS);
}

void	clean_map(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (j < game->map.mapx * game->map.mapy)
	{
		if (game->map.map[j] == 2)
			game->map.map[j] = 1;
		j++;
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
