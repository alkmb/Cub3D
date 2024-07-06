/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akambou <akambou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 09:18:04 by gprada-t          #+#    #+#             */
/*   Updated: 2024/07/02 04:19:29 by akambou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

char	*get_path(char *str)
{
	char	*path;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	while (str[i + j] && !ft_isspace(str[i + j]))
		j++;
	path = malloc(j + 1);
	if (!path)
		return (NULL);
	ft_strlcpy(path, str + i, j + 1);
	return (path);
}

void	chose_direction(t_game *game, char c)
{
	if (c == 'N')
	{
		game->player.angle = -1;
	}
	else if (c == 'S')
	{
		game->player.angle = M_PI - 1;
	}
	else if (c == 'E')
	{
		game->player.angle = M_PI_2 - 1;
	}
	else if (c == 'W')
	{
		game->player.angle = (3 * M_PI_2 - 1);
	}
}

int	parse_map(t_game *game, char *line)
{
	int	i;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '0'
			|| line[i] == '1' || line[i] == '2'
			|| line[i] == 'N' || line[i] == 'S'
			|| line[i] == 'E' || line[i] == 'W'
			|| line[i] == '7'))
	{
		if (line[i] == 'N' || line[i] == 'S'
			|| line[i] == 'E' || line[i] == 'W')
		{
			game->player.x = i;
			game->player.y = game->map.mapy;
			game->map.player += 1;
			chose_direction(game, line[i]);
			if (game->map.player > 1)
			{
				return (cub_error("Error\n\
				Only 1 player videogame sorry\n", FAILURE));
			}
		}
		i++;
	}
	game->map.temp_map = ft_strjoin(game->map.temp_map, line);
	return (SUCCESS);
}

int	parse_file(t_game *game, char *argv)
{
	int		fd;
	char	*line;
	char	*temp;

	init_parsing_data(game);
	fd = open(argv, O_RDONLY);
	if (fd < 0)
		return (cub_error("Error: Invalid FILE\n", 2));
	check_line(game, line, temp, fd);
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (parse_map(game, line) != SUCCESS)
		{
			free(line);
			close(fd);
			return (FAILURE);
		}
		free (line);
		line = get_next_line(fd);
	}
	free (line);
	close(fd);
	return (SUCCESS);
}
