/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nobmk <nobmk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 03:07:46 by kmb               #+#    #+#             */
/*   Updated: 2024/05/23 02:27:06 by nobmk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// En este caso, la función do_map() se encarga de asignar los valores de la \
matriz map[] a la estructura map del juego.
void	do_map(t_game *game)
{
	int i;
	int j;

	i = 0;
	j = 0;
	game->map.map = malloc(sizeof(int) * game->map.mapX * game->map.mapY);
	printf("game->map.mapX: %d\n", game->map.mapX);
	printf("game->map.mapY: %d\n", game->map.mapY);
	if (!game->map.map)
	{
		ft_putstr_fd("Error\nMalloc failed\n", 2);
		exit(1);
	}
	while (j < ft_strlen(game->map.temp_map) && game->map.temp_map[j] != '\0')
	{
		if (game->map.temp_map[j] == 9)
		{
			game->map.map[i] = 1;
			i++;
			game->map.map[i] = 1;
			i++;
			game->map.map[i] = 1;
			i++;
			j++;
		}
		else if (game->map.temp_map[j] == 10)
		{
			game->map.map[i] = 1;
			j++;
		}
		else if (game->map.temp_map[j] == ' ')
			game->map.map[i] = 1;
		else if (game->map.temp_map[j] == '1')
			game->map.map[i] = 1;
		else if (game->map.temp_map[j] == '0')
			game->map.map[i] = 0;
		else if (game->map.temp_map[j] == 'N' || game->map.temp_map[j] == 'S' 
		|| game->map.temp_map[j] == 'E' || game->map.temp_map[j] == 'W')
			game->map.map[i] = 3;
		i++;
		j++;
	}
}

int main(int argc, char **argv)
{
    t_game game;
	int fd;

	if (argc != 2)
	{
		ft_putstr_fd("Error\nInvalid number of arguments\n", 2);
		return (FAILURE);
	}
	else if (ft_strncmp(argv[1] + ft_strlen(argv[1]) - 4, ".cub", 4))
	{
		ft_putstr_fd("Error\nInvalid file extension\n", 2);
		return (FAILURE);
	}
	if (parse_file(&game, argv[1]))
		return (FAILURE);
	do_map(&game);
    init_game(&game);
    mlx_hook(game.mlx.win_ptr, 2, 1L<<0, key_press, &game);
    mlx_loop_hook(game.mlx.mlx_ptr, loop, &game);
    mlx_loop(game.mlx.mlx_ptr);
}
