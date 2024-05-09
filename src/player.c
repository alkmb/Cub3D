/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmb <kmb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 05:42:43 by kmb               #+#    #+#             */
/*   Updated: 2024/05/06 01:20:49 by kmb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"


int key_press(int keycode, t_game *game)
{
    mlx_clear_window(game->mlx.mlx_ptr, game->mlx.win_ptr2);

    if (keycode == KEY_W)
    {
        game->player.x += game->player.delta_x;
        game->player.y += game->player.delta_y;
    }
    else if (keycode == KEY_S)
    {
        game->player.x -= game->player.delta_x;
        game->player.y -= game->player.delta_y;
    }
    else if (keycode == KEY_A)
    {
        game->player.x -= cos(game->player.angle + (M_PI / 2)) * 5;
        game->player.y -= sin(game->player.angle + (M_PI / 2)) * 5;
    }
    else if (keycode == KEY_D)
    {
        game->player.x += cos(game->player.angle + (M_PI / 2)) * 5;
        game->player.y += sin(game->player.angle + (M_PI / 2)) * 5;
    }
    else if (keycode == KEY_LEFT)
    {
        game->player.angle -= 0.1;
        if (game->player.angle > 0)
            game->player.angle += (2 * M_PI);
        game->player.delta_x = cos(game->player.angle) * 5;
        game->player.delta_y = sin(game->player.angle) * 5;
    }   
    else if (keycode == KEY_RIGHT)
    {
        game->player.angle += 0.1;
        if (game->player.angle > 0)
            game->player.angle -= (2 * M_PI);
        game->player.delta_x = cos(game->player.angle) * 5;
        game->player.delta_y = sin(game->player.angle) * 5;
    }
    else if (keycode == KEY_ESC)
        exit(0);
    return 0;
}