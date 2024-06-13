/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akambou <akambou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 05:49:01 by kmb               #+#    #+#             */
/*   Updated: 2024/06/13 01:39:12 by akambou          ###   ########.fr       */
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
        return 0;

    int index = tex_y * tex_width + tex_x;

    return texture[index];
}

void get_texture_pos(t_game *game)
{
    float wall_x;
    if (game->rays->h_length < game->rays->v_length)
        wall_x = fmod(game->rays->horizontal_x, game->data.texture_width);
    else
        wall_x = fmod(game->rays->vertical_y, game->data.texture_width);

    game->data.texture_x = (int)(wall_x);
    game->data.texture_y = (int)((game->rays->win_i - \
    game->rays->line_offset) / (float)game->rays->line_height * game->data.texture_height);
}


void    draw_walls(t_game *game)
{
    while (game->rays->win_i < game->rays->line_height + game->rays->line_offset)
    {
        game->rays->win_j = 0;
        while (game->rays->win_j < game->rays->ray_width)
        {
            int color;
            if (game->rays->win_i < game->map.win_h 
            && game->rays->h_length < game->rays->v_length && game->rays->angle > M_PI)
            {  
                get_texture_pos(game);
                color = get_texture_color((int *)game->data.n_addr, \
                game->data.texture_x, game->data.texture_y, \
                game->data.texture_width, game->data.texture_height);
            }
            else if (game->rays->win_i < game->map.win_h 
            && game->rays->h_length < game->rays->v_length && game->rays->angle < M_PI)
            {  
                get_texture_pos(game);
                color = get_texture_color((int *)game->data.s_addr, \
                game->data.texture_x, game->data.texture_y, \
                game->data.texture_width, game->data.texture_height);
            }
            else if (game->rays->win_i < game->map.win_h 
            && game->rays->angle > M_PI_2 && game->rays->angle < 3 * M_PI_2)
            {
                get_texture_pos(game);
                color = get_texture_color((int *)game->data.e_addr, \
                game->data.texture_x, game->data.texture_y, \
                game->data.texture_width, game->data.texture_height);
            }
            else
            {
                get_texture_pos(game);
                color = get_texture_color((int *)game->data.w_addr, \
                game->data.texture_x, game->data.texture_y, \
                game->data.texture_width, game->data.texture_height);
            }
            my_mlx_pixel_put(&game->data, game->rays->ray * \
            game->rays->ray_width + game->rays->win_j, \
            game->rays->win_i, color);
            game->rays->win_j++;
        }
        game->rays->win_i++;
    }
}

void draw_window(t_game *game)
{
    set_window(game);
    draw_cealing(game);
    draw_walls(game);
    draw_floor(game);
    mlx_put_image_to_window(game->data.mlx_ptr, game->data.win_ptr, \
    game->data.img, 0, 0);
}
