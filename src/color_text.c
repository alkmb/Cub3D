/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_text.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprada-t <gprada-t@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 18:03:29 by gprada-t          #+#    #+#             */
/*   Updated: 2024/06/10 12:37:24 by gprada-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	rgb_to_int(t_color color)
{
	return (color.r << 16 | color.g << 8 | color.b);
}

char	*get_color(char *line)
{
	int		i;
	char	*color;

	i = 0;
	while (line[i] != ',' && line[i] != '\0')
		i++;
	color = malloc(sizeof(char) * i + 1);
	if (!color)
		return (NULL);
	ft_strlcpy(color, line, i + 1);
	return (color);
}

int	get_rgb(t_color *color, char *line)
{
	if (color->r == -1)
	{
		color->r = ft_atoi(get_color(line));
		line += ft_strlen(get_color(line)) + 1;
	}
	if (color->g == -1)
	{
		color->g = ft_atoi(get_color(line));
		line += ft_strlen(get_color(line)) + 1;
	}
	if (color->b == -1)
		color->b = ft_atoi(get_color(line));
	if (color->r < 0 || color->r > 255 || color->g < 0 || color->g > 255
		|| color->b < 0 || color->b > 255)
		return (cub_error("\nValues out of range\n", FAILURE));
	return (SUCCESS);
}

int	parse_color(t_game *game, char *line)
{
	if (!line)
		return (cub_error("Error\nInvalid color\n", FAILURE));
	if (line[0] == 'F')
		return (get_rgb(&game->map.floor, line + 1));
	else if (line[0] == 'C')
		return (get_rgb(&game->map.ceiling, line + 1));
	return (SUCCESS);
}
