/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_text_and_colors.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akambou <akambou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 13:21:33 by gprada-t          #+#    #+#             */
/*   Updated: 2024/07/02 04:06:14 by akambou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	handle_texture_paths(t_game *game, char *new_line)
{
	if (ft_strncmp(new_line, "NO", 2) == 0)
		game->map.north_texture = get_path(new_line + 2);
	else if (ft_strncmp(new_line, "SO", 2) == 0)
		game->map.south_texture = get_path(new_line + 2);
	else if (ft_strncmp(new_line, "EA", 2) == 0)
		game->map.east_texture = get_path(new_line + 2);
	else if (ft_strncmp(new_line, "WE", 2) == 0)
		game->map.west_texture = get_path(new_line + 2);
	else if (ft_strncmp(new_line, "F", 1) == 0)
		return (handle_floor_texture(game, new_line));
	else if (ft_strncmp(new_line, "C", 1) == 0)
		return (handle_ceiling_texture(game, new_line));
	return (SUCCESS);
}

int	handle_floor_texture(t_game *game, char *new_line)
{
	game->map.floor.texture = get_path(new_line + 2);
	if (!game->map.floor.texture)
		return (cub_error("Error\nInvalid texture\n", FAILURE));
	if (game->map.floor.texture[0] == '.'
		&& game->map.floor.texture[1] == '/')
		game->map.floor_texture = game->map.floor.texture;
	else
		free(game->map.floor.texture);
	if (parse_color(game, new_line) == -3)
		return (cub_error("Error\nInvalid color\n", FAILURE));
	return (SUCCESS);
}

int	handle_ceiling_texture(t_game *game, char *new_line)
{
	game->map.ceiling.texture = get_path(new_line + 2);
	if (!game->map.ceiling.texture)
		return (cub_error("Error\nInvalid texture\n", FAILURE));
	if (game->map.ceiling.texture[0] == '.'
		&& game->map.ceiling.texture[1] == '/')
		game->map.ceiling_texture = game->map.ceiling.texture;
	else
		free(game->map.ceiling.texture);
	if (parse_color(game, new_line) == -3)
		return (FAILURE);
	return (SUCCESS);
}

int	parse_texture_and_colors(t_game *game, char *line)
{
	char	*new_line;
	int		i;

	i = 0;
	if (!line)
		return (cub_error("Error\nInvalid texture\n", FAILURE));
	while (ft_isspace(line[i]) == TRUE)
		i++;
	new_line = ft_strdup(line + i);
	if (handle_texture_paths(game, new_line) == FAILURE)
		return (FAILURE);
	free(new_line);
	return (SUCCESS);
}
