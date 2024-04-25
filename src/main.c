/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmb <kmb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 03:07:46 by kmb               #+#    #+#             */
/*   Updated: 2024/04/25 04:59:51 by kmb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>



t_map* parse_cub_file(const char* filename) 
{
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Failed to open file: %s\n", filename);
        return NULL;
    }

    t_map* cub = malloc(sizeof(t_map));
    // TODO: Initialize cub fields

    char line[256];
    while (fgets(line, sizeof(line), file))
    {
        if (strncmp(line, "NO", 2) == 0)
        {
            // TODO: Parse north texture path
        }
        else if (strncmp(line, "SO", 2) == 0)
        {
            // TODO: Parse south texture path
        }
        else if (strncmp(line, "WE", 2) == 0)
        {
            // TODO: Parse west texture path
        }
        else if (strncmp(line, "EA", 2) == 0)
        {
            // TODO: Parse east texture path
        }
        else if (line[0] == 'F')
        {
            // TODO: Parse floor color
        }
        else if (line[0] == 'C')
        {
            // TODO: Parse ceiling color
        }
        else
        {
            // TODO: Parse map line
        }
    }

    fclose(file);
    return cub;
}

void    init_game(t_game *game)
{
    game->mlx.mlx_ptr = mlx_init();
    game->mlx.win_ptr = mlx_new_window(game->mlx.mlx_ptr, 1200, 900, "cub3d");
    game->player.x = 0;
    game->player.y = 0;
    game->player.direction = 0;
    game->player.speed = 0.1;

    game->rays.direction = 0;
    game->rays.length = 0;
    game->rays.hit_wall = 0;

    game->map.width = 0;
    game->map.height = 0;
    game->map.floor_color.b = 0;
    game->map.floor_color.g = 0;
    game->map.floor_color.r = 0;
    game->map.ceiling_color.b = 0;
    game->map.ceiling_color.g = 0;
    game->map.ceiling_color.r = 0;
}

int main(void)
{
    t_game game;

    init_game(&game);
    mlx_loop(game.mlx.mlx_ptr);

    return (0);
}