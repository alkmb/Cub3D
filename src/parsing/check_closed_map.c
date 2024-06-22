/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_closed_map.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprada-t <gprada-t@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 16:36:09 by gprada-t          #+#    #+#             */
/*   Updated: 2024/06/19 16:43:20 by gprada-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	check_edges(int idx, t_game *game, int i, int j)
{
	if (i == 0 || i == game->map.mapx - 1 || j == 0 || j == game->map.mapy - 1)
		return (cub_error("Error\nInvalid map: Open borders\n", FAILURE));
	if (i > 0 && game->map.map[idx - 1] == 2)
		return (cub_error("Error\nInvalid map: Near forbidden element\n", \
		FAILURE));
	if (i < game->map.mapx - 1 && game->map.map[idx + 1] == 2)
		return (cub_error("Error\nInvalid map: Near forbidden element\n", \
		FAILURE));
	if (j > 0 && game->map.map[idx - game->map.mapx] == 2)
		return (cub_error("Error\nInvalid map: Near forbidden element\n", \
		FAILURE));
	if (j < game->map.mapy - 1 && game->map.map[idx + game->map.mapx] == 2)
		return (cub_error("Error\nInvalid map: Near forbidden element\n", \
		FAILURE));
	return (0);
}

int	validate_map(t_game *game)
{
	int	i;
	int	j;
	int	idx;

	j = -1;
	while (++j < game->map.mapy)
	{
		i = -1;
		while (++i < game->map.mapx)
		{
			idx = j * game->map.mapx + i;
			if (game->map.map[idx] == 0)
			{
				if (check_edges(idx, game, i, j))
					return (FAILURE);
			}
		}
	}
	return (SUCCESS);
}

int	check_closed_map(t_game *game)
{
	if (game->map.mapx < 3 || game->map.mapy < 3)
		return (cub_error("Error\nToo Small map\n", FAILURE));
	return (validate_map(game));
}
