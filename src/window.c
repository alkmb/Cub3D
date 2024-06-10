/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nobmk <nobmk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 05:49:01 by kmb               #+#    #+#             */
/*   Updated: 2024/06/08 00:27:08 by nobmk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void draw_3D(t_game *game)
{
    int i;
    int j;

    // void *img_ptr = mlx_xpm_file_to_image(game->data.mlx_ptr, "texture/wood.xpm", &img_width, &img_height);

    // char *img_data = mlx_get_data_addr(img_ptr, &game->data.bits_per_pixel, &game->data.line_length, &game->data.endian);

    game->map.win_h = game->map.mapY * game->map.mapS;
    game->map.win_w = game->map.mapX * game->map.mapS;
    int ray_width = game->map.win_w / 120;
    game->rays->line_height = (game->map.mapS * \
    game->map.win_h) / game->rays->total_length;
    
    if (game->rays->line_height > game->map.win_h)
        game->rays->line_height = game->map.win_h;
    game->rays->line_offset = game->map.win_h / 2 - \
    game->rays->line_height / 2;
    i = 0;
    while (i < game->rays->line_offset)
    {
        j = 0;
        while (j < ray_width)
        {
            my_mlx_pixel_put(&game->data, \
            game->rays->ray * ray_width + j, i, 0x000037);
            j++;
        }
        i++;
    }

    while (i < game->rays->line_height + game->rays->line_offset)
    {
        j = 0;
        while (j < ray_width)
        {
            // img si i = height offset = lenght
            if (i < game->map.win_h && game->rays->h_length < game->rays->v_length) 
                my_mlx_pixel_put(&game->data, game->rays->ray * \
                ray_width + j, i, 0xA0A0A0);
            else if (i < game->map.win_h && game->rays->h_length > game->rays->v_length)
                my_mlx_pixel_put(&game->data, game->rays->ray * \
                ray_width + j, i, 0x808080);
            j++;
        }
        i++;
    }
    while (i < game->map.win_h)
    {
        j = 0;
        while (j < ray_width)
        {
            my_mlx_pixel_put(&game->data, \
            game->rays->ray * ray_width + j, i, 0x222020);
            j++;
        }
        i++;
    }
    mlx_put_image_to_window(game->data.mlx_ptr, game->data.win_ptr, \
    game->data.img, 0, 0);
}

void draw_map(t_game *game)
{
    
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
                    // mlx_pixel_put(game->data.mlx_ptr, game->data.win_ptr,\
                    // game->map.x * game->map.mapS + game->map.j, \
                    // game->map.y * game->map.mapS + game->map.i, \
                    // game->map.color);
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