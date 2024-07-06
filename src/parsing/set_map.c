/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akambou <akambou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 15:47:08 by gprada-t          #+#    #+#             */
/*   Updated: 2024/07/02 04:21:40 by akambou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	get_line(t_game *game, char *line, char *temp, int fd)
{
	while (line && !textures_and_colors_get(game))
	{
		temp = line;
		while (ft_isspace(*temp))
			temp++;
		if (!*temp)
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		if (parse_texture_and_colors(game, temp))
		{
			free(line);
			close(fd);
			return (FAILURE);
		}
		free(line);
		line = get_next_line(fd);
	}
	free(line);
}

int	check_line(t_game *game, char *line, char *temp, int fd)
{
	line = get_next_line(fd);
	if (!line)
	{
		close(fd);
		return (cub_error("Error: Empty file\n", 2));
	}
	get_line(game, line, temp, fd);
	if (!have_to_paint(&game->map))
	{
		close(fd);
		return (cub_error("Error\nInvalid color\n", FAILURE));
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
	if (!(*game->map.temp_map))
		return (cub_error("Error\nInvalid map\n", FAILURE));
	while (*game->map.temp_map == '\n')
		game->map.temp_map++;
	setting_map_x_map_y(game->map.temp_map, game);
	game->map.map = str_to_int_array(game->map.temp_map, \
	game->map.mapx, game->map.mapy);
	if (game->map.player == 0)
		return (cub_error("Error\nNo player\n", FAILURE));
	if (check_closed_map(game))
		return (cub_error("Error\nMap is open\n", FAILURE));
	clean_map(game);
	return (SUCCESS);
}
