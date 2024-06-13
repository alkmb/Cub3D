/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akambou <akambou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 05:49:01 by kmb               #+#    #+#             */
/*   Updated: 2024/06/13 03:29:59 by akambou          ###   ########.fr       */
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
    if (game->rays->h_length < game->rays->v_length)
        game->data.wall_x = fmod(game->rays->horizontal_x, game->data.texture_width);
    else
        game->data.wall_x = fmod(game->rays->vertical_y, game->data.texture_width);

    game->data.texture_x = (int)(game->data.wall_x);
    game->data.texture_y = (int)((game->rays->win_i - \
    game->rays->line_offset) / (float)game->rays->line_height * game->data.texture_height);
}

void    select_wall(t_game *game)
{
    if (game->rays->win_i < game->map.win_h 
    && game->rays->h_length < game->rays->v_length && game->rays->angle > M_PI)
    {  
        get_texture_pos(game);
        game->data.color = get_texture_color((int *)game->data.n_addr, \
        game->data.texture_x, game->data.texture_y, \
        game->data.texture_width, game->data.texture_height);
    }
    else if (game->rays->win_i < game->map.win_h 
    && game->rays->h_length < game->rays->v_length && game->rays->angle < M_PI)
    {  
        get_texture_pos(game);
        game->data.color = get_texture_color((int *)game->data.s_addr, \
        game->data.texture_x, game->data.texture_y, \
        game->data.texture_width, game->data.texture_height);
    }
    else if (game->rays->win_i < game->map.win_h 
    && game->rays->angle > M_PI_2 && game->rays->angle < 3 * M_PI_2)
    {
        get_texture_pos(game);
        game->data.color = get_texture_color((int *)game->data.e_addr, \
        game->data.texture_x, game->data.texture_y, \
        game->data.texture_width, game->data.texture_height);
    }
    else
    {
        get_texture_pos(game);
        game->data.color = get_texture_color((int *)game->data.w_addr, \
        game->data.texture_x, game->data.texture_y, \
        game->data.texture_width, game->data.texture_height);
    }
}

void    set_window(t_game *game)
{
    game->map.win_h = game->map.mapY * game->map.mapS;
    game->map.win_w = game->map.mapX * game->map.mapS;
    game->rays->ray_width = game->map.win_w / 120;
    game->rays->line_height = (game->map.mapS * \
    game->map.win_h) / game->rays->total_length;

    if (game->rays->line_height > game->map.win_h)
        game->rays->line_height = game->map.win_h;
    game->rays->line_offset = game->map.win_h / 2 - \
    game->rays->line_height / 2;
}

void    draw_walls(t_game *game)
{
    while (game->rays->win_i < game->rays->line_height + game->rays->line_offset)
    {
        game->rays->win_j = 0;
        while (game->rays->win_j < game->rays->ray_width)
        {
            select_wall(game);
            my_mlx_pixel_put(&game->data, game->rays->ray * \
            game->rays->ray_width + game->rays->win_j, \
            game->rays->win_i, game->data.color);
            game->rays->win_j++;
        }
        game->rays->win_i++;
    }
}

void draw_window(t_game *game)
{
    set_window(game);
    minimap(game);
    draw_cealing(game);
    draw_walls(game);
    draw_floor(game);
}
