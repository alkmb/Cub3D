/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertical.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nobmk <nobmk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 01:38:44 by kmb               #+#    #+#             */
/*   Updated: 2024/05/23 02:40:08 by nobmk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void    cast_vertical(t_game *game)
{
    // Mientras la profundidad de campo sea menor a 8
    while (game->rays->deapht_of_field < 8)
    {
        // Se obtiene la posicion en x y y del rayo dividido por 64
        game->rays->mx = (int)game->rays->ray_x >> 6;
        game->rays->my = (int)game->rays->ray_y >> 6;
        // Si la posicion en x es mayor o igual a 0 y menor que el ancho del mapa
        if (game->rays->mx >= 0 && game->rays->mx < game->map.width 
        && game->rays->my >= 0 && game->rays->my < game->map.height) 
            game->rays->mp = game->rays->my * game->map.width + game->rays->mx;
        // Si la posicion en x y y es mayor a 0 y menor \
        que el ancho del mapa por el alto del mapa
        if (game->rays->mp > 0 && game->rays->mp < game->map.width * game->map.height 
        && game->map.map[game->rays->mp] == 1)
        {
            // Se guarda la posicion en x y y del rayo y se \
            guarda la distancia entre el jugador y el rayo, tambien se \
            guarda la profundidad de campo para salir del bucle
            game->rays->vertical_x = game->rays->ray_x;
            game->rays->vertical_y = game->rays->ray_y;
            game->rays->v_length = distance(game->player.x, game->player.y, \
            game->rays->vertical_x, game->rays->vertical_y);
            game->rays->deapht_of_field = 8;
        }
        // Si no se ha encontrado una pared
        else
        {
            // Se suma el offset en x y y al rayo para \
            moverlo en la direccion correcta y se \
            guarda la distancia entre el jugador y el rayo y se \
            aumenta la profundidad de campo para seguir buscando una pared
            game->rays->ray_x += game->rays->x_offset;
            game->rays->ray_y += game->rays->y_offset;
            game->rays->v_length = distance(game->player.x, game->player.y, \
            game->rays->ray_x, game->rays->ray_y);
            game->rays->deapht_of_field++;
        }   
    }
}

void    vertical_direction(t_game *game)
{
    // Se obtiene la tangente negativa del angulo del jugador y se guarda en nTan \
    para obtener la direccion del rayo
    float nTan = -tan(game->rays->angle);
    if (game->rays->angle > M_PI_2 && game->rays->angle < 3 * M_PI_2)
    {
        // Si el angulo del jugador es mayor a 90 grados y menor a 270 grados \
        se obtiene la posicion en x del rayo y se obtiene la posicion en y del rayo \
        multiplicando la posicion en x del jugador menos 1 por la tangente negativa \
        del angulo del jugador y se suma la posicion en y del jugador
        game->rays->ray_x = (((int)game->player.x >> 6) << 6) - 0.0001;
        game->rays->ray_y = (game->player.x - game->rays->ray_x) * \
        nTan + game->player.y;
        game->rays->x_offset = -64;
        game->rays->y_offset = -game->rays->x_offset * nTan;
    }
    if (game->rays->angle < M_PI_2 || game->rays->angle > 3 * M_PI_2)
    {
        // Si el angulo del jugador es menor a 90 grados o mayor a 270 grados \
        se obtiene la posicion en x del rayo y se obtiene la posicion en y del rayo \
        multiplicando la posicion en x del jugador mas 1 por la tangente negativa \
        del angulo del jugador y se suma la posicion en y del jugador
        game->rays->ray_x = (((int)game->player.x >> 6) << 6) + 64;
        game->rays->ray_y = (game->player.x - game->rays->ray_x) * \
        nTan + game->player.y;
        game->rays->x_offset = 64;
        game->rays->y_offset = -game->rays->x_offset * nTan;
    }
    if (game->rays->angle == M_PI_2 || game->rays->angle == 3 * M_PI_2)
    {
        // Si el angulo del jugador es 90 grados o 270 grados \
        se obtiene la posicion en x y y del jugador y se \
        guarda la profundidad de campo para salir del bucle
        game->rays->ray_x = game->player.x;
        game->rays->ray_y = game->player.y;
        game->rays->deapht_of_field = 8;
    }
}

void    reset_vertical(t_game *game)
{
        game->rays->v_length = 100000000;
        game->rays->vertical_x = game->player.x;
        game->rays->vertical_y = game->player.y;
        game->rays->deapht_of_field = 0;
}