/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akambou <akambou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 05:49:01 by kmb               #+#    #+#             */
/*   Updated: 2024/06/12 15:12:35 by akambou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void    draw_cealing(t_game *game)
{
    game->rays->win_i = 0;
    while (game->rays->win_i < game->rays->line_offset)
    {
        game->rays->win_j = 0;
        while (game->rays->win_j < game->rays->ray_width)
        {
            my_mlx_pixel_put(&game->data, \
            game->rays->ray * game->rays->ray_width + game->rays->win_j, \
            game->rays->win_i, game->map.ceiling.color);
            game->rays->win_j++;
        }
        game->rays->win_i++;
    }
}

void    draw_floor(t_game *game)
{
    while (game->rays->win_i < game->map.win_h)
    {
        game->rays->win_j = 0;
        while (game->rays->win_j < game->rays->ray_width)
        {
            my_mlx_pixel_put(&game->data, \
            game->rays->ray * game->rays->ray_width + game->rays->win_j, \
            game->rays->win_i, game->map.floor.color);
            game->rays->win_j++;
        }
        game->rays->win_i++;
    }
}

int get_texture_color(int *texture, int tex_x, int tex_y, int tex_width, int tex_height)
{
    if (tex_x < 0 || tex_x >= tex_width || tex_y < 0 || tex_y >= tex_height)
    {
        return 0;
    }

    int index = tex_y * tex_width + tex_x;

    return texture[index];
}

void    draw_walls(t_game *game)
{
    while (game->rays->win_i < game->rays->line_height + game->rays->line_offset)
    {
        game->rays->win_j = 0;
        while (game->rays->win_j < game->rays->ray_width)
        {
            if (game->rays->win_i < game->map.win_h 
            && game->rays->h_length < game->rays->v_length)
            {
                int tex_x = (int)(game->data.texture_width \
                * (game->rays->win_j / (float)game->rays->ray_width));
                int tex_y = (int)(game->data.texture_height \
                * (game->rays->win_i / (float)game->rays->line_height / 8));
                int color = get_texture_color((int *)game->data.n_addr, tex_x, tex_y, game->data.texture_width, game->data.texture_height);

                my_mlx_pixel_put(&game->data, game->rays->ray * \
                game->rays->ray_width + game->rays->win_j, \
                game->rays->win_i, color);
            }
            else if (game->rays->win_i < game->map.win_h 
            && game->rays->h_length > game->rays->v_length)
            {
                int tex_x = (int)(game->data.texture_width \
                * (game->rays->win_j / (float)game->rays->ray_width));
                int tex_y = (int)(game->data.texture_height \
                * (game->rays->win_i / (float)game->rays->line_height / 8));
                int color = get_texture_color((int *)game->data.s_addr, tex_x, tex_y, game->data.texture_width, game->data.texture_height);
                
                my_mlx_pixel_put(&game->data, game->rays->ray * \
                game->rays->ray_width + game->rays->win_j, \
                game->rays->win_i, color);
            }
            game->rays->win_j++;
        }
        game->rays->win_i++;
    }
}

void draw_window(t_game *game)
{
    set_window(game);
    // minmap(game);
    // draw_player(game, 5, 5, 0x0000FF);
    draw_cealing(game);
    draw_walls(game);
    draw_floor(game);
    mlx_put_image_to_window(game->data.mlx_ptr, game->data.win_ptr, \
    game->data.n_texture, 0, 0);
    mlx_put_image_to_window(game->data.mlx_ptr, game->data.win_ptr, \
    game->data.img, 0, 0);
}
