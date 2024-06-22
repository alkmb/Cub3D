/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_x_and_y.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprada-t <gprada-t@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 16:20:43 by gprada-t          #+#    #+#             */
/*   Updated: 2024/06/19 16:38:51 by gprada-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static void	update_line_length(char c, int *line)
{
	if (c == '\t')
		*line += 4;
	else
		(*line)++;
}

static void	handle_newline(char *str_map, int *i, int *line, t_game *game)
{
	while (str_map[*i] == '\n' && str_map[*i + 1] == '\n')
		(*i)++;
	if (*line > game->map.mapx)
		game->map.mapx = *line;
	*line = 0;
	game->map.mapy++;
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
			handle_newline(str_map, &i, &line, game);
		else
			update_line_length(str_map[i], &line);
		i++;
	}
	if (line > 0)
	{
		if (line > game->map.mapx)
			game->map.mapx = line;
		game->map.mapy++;
	}
}
