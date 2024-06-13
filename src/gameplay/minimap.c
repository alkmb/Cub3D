/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akambou <akambou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 05:42:43 by kmb               #+#    #+#             */
/*   Updated: 2024/06/13 03:02:43 by akambou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void draw_ray(t_game *game, int rayIndex, int length)
{
    int dx, dy, steps, k;
    float xIncrement, yIncrement, x, y;

    if (rayIndex < 0 || rayIndex >= game->map.width) return;

    t_ray *ray = &game->rays[rayIndex];

    int end_x = (game->player.x + length * cos(ray->angle)) / 4;
    int end_y = (game->player.y + length * sin(ray->angle)) / 4;

    dx = end_x - (game->player.x / 4);
    dy = end_y - (game->player.y / 4); 

    if (abs(dx) > abs(dy))
        steps = abs(dx);
    else
        steps = abs(dy);

    xIncrement = dx / (float) steps;
    yIncrement = dy / (float) steps;

    x = game->player.x / 4; 
    y = game->player.y / 4;

    k = 0;
    while (k < steps)
    {
        x += xIncrement;
        y += yIncrement;
        mlx_pixel_put(game->data.mlx_ptr, \
        game->data.win_ptr, round(x), round(y), 0xFFFFFF);
        k++;
    }
}


void draw_player(t_game *game, int width, int height, int color)
{
    int i;
    int j;

    i = 0;
    while (i < height)
    {
        j = 0;
        while (j < width)
        {   
            mlx_pixel_put(game->data.mlx_ptr, game->data.win_ptr, \
             (game->player.x / 4) + j, (game->player.y / 4) + i, color);
            j++;
        }
        i++;
    }
}

void minimap(t_game *game)
{
    draw_player(game, 5, 5, 0x0000FF);
    game->map.y = 0;
    game->map.mapS /= 4;
    game->map.cellSize /= 4;

    while ( game->map.y <  game->map.mapY)
    {
        game->map.x = 0;
        while ( game->map.x <  game->map.mapX)
        {
            game->map.cell = game->map.map[ game->map.y * \
            game->map.mapX +  game->map.x];
            game->map.color =  game->map.cell \
            == 1 ? 0x0000FF : 0x808080;
            game->map.i = 0;
            while ( game->map.i <  game->map.cellSize)
            {
                game->map.j = 0;
                while ( game->map.j <  game->map.cellSize)
                {
                    my_mlx_pixel_put(&game->data,\
                    game->map.x * game->map.mapS + game->map.j, \
                    game->map.y * game->map.mapS + game->map.i, \
                    game->map.color);
                    game->map.j++;
                }
                game->map.i++;
            }
            game->map.j = 0;
            game->map.x++;
        }
        game->map.y++;
    }
    game->map.mapS *= 4;
    game->map.cellSize *= 4;
    

}
