/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akambou <akambou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 09:18:04 by gprada-t          #+#    #+#             */
/*   Updated: 2024/06/17 07:46:52 by akambou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	textures_and_colors_get(t_game *game)
{
	if (game->map.north_texture && game->map.south_texture
		&& game->map.east_texture && game->map.west_texture
		&& game->map.floor.r != -1 && game->map.floor.g != -1
		&& game->map.floor.b != -1 && game->map.ceiling.r != -1
		&& game->map.ceiling.g != -1 && game->map.ceiling.b != -1)
		return (TRUE);
	return (FALSE);
}

void	parse_texture_and_colors(t_game *game, char *line)
{
	int	length;
	char *newline;
	
	if (!line)
		return ((void)cub_error("Error\nInvalid texture\n", FAILURE));
	while (ft_isspace(*line) == TRUE)
		line++;
	if (ft_strncmp(line, "NO", 2) == SUCCESS)
	{
		newline = ft_strchr(line, '\n');
		if (newline != NULL)
			length = newline - (line + 3);
		else
			length = ft_strlen(line + 3);
		game->map.north_texture = malloc(length + 1);
		if (game->map.north_texture != NULL)
		{
			ft_strncpy(game->map.north_texture, line + 3, length);
			game->map.north_texture[length] = '\0';
		}
	}
	else if (ft_strncmp(line, "SO", 2) == SUCCESS)
	{
		newline = ft_strchr(line, '\n');
		if (newline != NULL)
			length = newline - (line + 3);
		else
			length = ft_strlen(line + 3);
		game->map.south_texture = malloc(length + 1);
		if (game->map.south_texture != NULL)
		{
			ft_strncpy(game->map.south_texture, line + 3, length);
			game->map.south_texture[length] = '\0';
		}
	}
	else if (ft_strncmp(line, "WE", 2) == SUCCESS)
	{
		newline = ft_strchr(line, '\n');
		if (newline != NULL)
			length = newline - (line + 3);
		else
			length = ft_strlen(line + 3);
		game->map.west_texture = malloc(length + 1);
		if (game->map.west_texture != NULL)
		{
			ft_strncpy(game->map.west_texture, line + 3, length);
			game->map.west_texture[length] = '\0';
		}
	}
	else if (ft_strncmp(line, "EA", 2) == SUCCESS)
	{
		newline = ft_strchr(line, '\n');
		if (newline != NULL)
			length = newline - (line + 3);
		else
			length = ft_strlen(line + 3);
		game->map.east_texture = malloc(length + 1);
		if (game->map.east_texture != NULL)
		{
			ft_strncpy(game->map.east_texture, line + 3, length);
			game->map.east_texture[length] = '\0';
		}
	}
	else if (ft_strncmp(line, "F", 1) == SUCCESS)
		parse_color(game, line);
	else if (ft_strncmp(line, "C", 1) == SUCCESS)
		parse_color(game, line);
}

int	parse_map(t_game *game, char *line)
{
	int			i;
	static int	tab_count = 0;
	static int	player = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == 'N' || line[i] == 'S'
			|| line[i] == 'E' || line[i] == 'W')
		{
			game->player.x = i;
			game->player.y = game->map.mapy;
			game->player.angle = line[i];
			player++;
			if (player > 1)
				return (free(game->map.temp_map), cub_error("Error\nInvalid map, \
					cannot be more than 1 player\n", FAILURE));
		}
		i++;
	}
	game->map.temp_map = ft_strjoin(game->map.temp_map, line);
	printf ("line : %s\n", line);
	return (SUCCESS);
}

int	parse_file(t_game *game, char *argv)
{
	int		fd;
	char	*line;

	fd = open(argv, O_RDONLY);
	if (fd < 0)
		return (cub_error("Error: Invalid FILE", 2));
	init_parsing_data(game);
	line = get_next_line(fd);
	while (line && !textures_and_colors_get(game))
	{
		while (ft_isspace(line[0]))
			line++;
		parse_texture_and_colors(game, line);
		line = get_next_line(fd);
	}
	game->map.floor.color = rgb_to_int(game->map.floor);
	printf("floor color: %d\n", game->map.floor.color);
	game->map.ceiling.color = rgb_to_int(game->map.ceiling);
	printf("ceiling color: %d\n", game->map.ceiling.color);
	while (line)
	{
		line = get_next_line(fd);
		if (!line)
			break;
		parse_map(game, line);
	}
	close(fd);
	return (SUCCESS);
}
