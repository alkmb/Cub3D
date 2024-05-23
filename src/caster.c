/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   caster.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nobmk <nobmk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 00:36:56 by kmb               #+#    #+#             */
/*   Updated: 2024/05/23 02:35:22 by nobmk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

float distance(float x1, float y1, float x2, float y2)
{
    // Esto devuelve la distancia entre dos puntos
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

void    chose_lenght(t_game *game)
{
    if (game->rays->h_length < game->rays->v_length)
    {
        game->rays->total_length = game->rays->h_length;
        draw_player_angle(game, 0, game->rays->h_length);
    }
    else
    {
        game->rays->total_length = game->rays->v_length;
        draw_player_angle(game, 0, game->rays->v_length);
    }
}

void    get_angle(t_game *game)
{
    // Angulo de vision del jugador - 30 grados (izquierda) para el primer rayo
    game->rays->angle = game->player.angle - (M_PI / 6);
    if (game->rays->angle < 0)
        game->rays->angle += 2 * M_PI;
    if (game->rays->angle > 2 * M_PI)
        game->rays->angle -= 2 * M_PI;
}
void    reset_angle(t_game *game)
{
    // Angulo de vision del jugador - 30 grados (izquierda) para el primer rayo
    if (game->rays->angle < 0)
        game->rays->angle += 2 * M_PI;
    if (game->rays->angle > 2 * M_PI)
        game->rays->angle -= 2 * M_PI;
}

void cast_rays(t_game *game)
{
    get_angle(game);
    game->rays->ray = 0;
    while (game->rays->ray < 60)
    {
        reset_angle(game);
        reset_horizontal(game);
        horizontal_direction(game);
        cast_horizontal(game);
        reset_vertical(game);
        vertical_direction(game);
        cast_vertical(game);
        chose_lenght(game);
        draw_3D(game);
        game->rays->angle += DR;
        game->rays->ray++;
    }
}