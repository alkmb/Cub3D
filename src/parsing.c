/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nobmk <nobmk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 09:18:04 by gprada-t          #+#    #+#             */
/*   Updated: 2024/05/23 01:29:34 by nobmk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

// aqui compruebo que no tenga mas de 1 jugador por mapa, cuento X e Y, y le meto a una
// variable temporal el mapa en str para luego transformarelo en int
int	parse_map(t_game *game, char *line)
{
	int			i;
	static int	tab_count = 0;
	static int	player = 0;
	i = 0;
	while (line[i])
	{
		if (player > 1)
		{
			ft_putstr_fd("Error\nInvalid map, cannot be more than 1 player\n", 2);
			free(game->map.temp_map);
			return (FAILURE);
		}
		//revisa este if porque no se si es como lo  necesitas o no
		if (line[i] == 'N' || line[i] == 'S' 
			|| line[i] == 'E' || line[i] == 'W')
		{
			game->player.x = i;
			game->player.y = game->map.mapY;
			game->player.angle = line[i];
			player++;
		}
		else if (line[i] == '1' || line[i] == '0' 
			|| line[i] == ' ' || line[i] == '\t')
		{
			if (line[i] == '\t')
				tab_count += 3;
		}
		i++;
	}
	i = i - 1 + tab_count;
	if (game->map.mapX < i)
		game->map.mapX = i;
	game->map.temp_map = ft_strjoin(game->map.temp_map, line);
	game->map.mapY++;
	return (SUCCESS);
}

// esto es una guarrada  guarrissima que funciona, te da los colores en rgb
// los puedes imprimir para comprogbarlos, ya lo limpiaré xD
void	parse_color(t_game *game, char *line)
{
	int		i;
	char	*color;

	color = line;
	if (!line)
	{
		ft_putstr_fd("Error\nInvalid color\n", 2);
		return ;
	}
	if (line[0] == 'F')
	{
		i = 0;
		color = ft_strdup(line + 2);
		while (line[i] != ',')
			i++;
		char *j = malloc(sizeof(char) * i - 1);
		ft_strlcpy(j, color, i - 1);
		game->map.floor_color.r = ft_atoi(j);
		free(j);
		free(color);
		color = ft_strdup(line + i + 1);
		int i2 = i;
		i = 0;
		while (color[i] != ',')
			i++;
		char *k = malloc(sizeof(char) * i + 1);
		ft_strlcpy(k, color, i + 1);
		game->map.floor_color.g = ft_atoi(k);
		free(k);
		free(color);
		color = ft_strdup(line + i2 + i + 1);
		i = 0;
		while (color[i] != ',' && color[i] != '\0')
			i++;
		char *l = malloc(sizeof(char) * i);
		ft_strlcpy(l, color, i - 1);
		game->map.floor_color.b = ft_atoi(l);
		free(l);
		free(color);
	}
	else if (line[0] == 'C')
	{
		i = 0;
		color = ft_strdup(line + 2);
		while (line[i] != ',')
			i++;
		char *j = malloc(sizeof(char) * i - 1);
		ft_strlcpy(j, color, i - 1);
		game->map.ceiling_color.r = ft_atoi(j);
		free(j);
		free(color);
		color = ft_strdup(line + i + 1);
		int i2 = i;
		i = 0;
		while (color[i] != ',')
			i++;
		char *k = malloc(sizeof(char) * i + 1);
		ft_strlcpy(k, color, i + 1);
		game->map.ceiling_color.g = ft_atoi(k);
		free(k);
		free(color);
		color = ft_strdup(line + i2 + i + 1);
		i = 0;
		while (color[i] != ',' && color[i] != '\0')
			i++;
		char *l = malloc(sizeof(char) * i);
		ft_strlcpy(l, color, i - 1);
		game->map.ceiling_color.b = ft_atoi(l);
		free(l);
		free(color);
	}
}

void	parse_texture_and_colors(t_game *game, char *line)
{
	int		i;

	i		= 0;
	if (!line)
	{
		ft_putstr_fd("Error\nInvalid texture\n", 2);
		return ;
	}
	while (ft_isspace(*line) == TRUE)
		line++;
	if (strncmp(line, "NO", 2) == 0)
	{
		game->map.north_texture = ft_strdup(line + 2);
		printf("%s\n", game->map.north_texture);
	}
	else if (ft_strncmp(line, "SO", 2) == 0)
	{
		game->map.south_texture = ft_strdup(line + 2);
		printf("%s\n", game->map.south_texture);
	}
	else if (ft_strncmp(line, "EA", 2) == 0)
	{
		game->map.east_texture = ft_strdup(line + 2);
		printf("%s\n", game->map.east_texture);
	}
	else if (ft_strncmp(line, "WE", 2) == 0)
	{
		game->map.west_texture = ft_strdup(line + 2);
		printf("%s\n", game->map.west_texture);
	}
	else if (strncmp(line, "F", 1) == 0)
	{
		parse_color(game, line);
		printf("floor color: %d %d %d\n", game->map.floor_color.r, \
		game->map.floor_color.g, game->map.floor_color.b);
	}
	else if (strncmp(line, "C", 1) == 0)
	{
		parse_color(game, line);
		printf("ceiling color: %d %d %d\n", game->map.ceiling_color.r, \
		game->map.ceiling_color.g, game->map.ceiling_color.b);
	}
}

int	textures_and_colors_get(t_game *game)
{
	if (game->map.north_texture && game->map.south_texture
		&& game->map.east_texture && game->map.west_texture
		&& game->map.floor_color.r != -1 && game->map.floor_color.g != -1
		&& game->map.floor_color.b != -1 && game->map.ceiling_color.r != -1
		&& game->map.ceiling_color.g != -1 && game->map.ceiling_color.b != -1)
		return (TRUE);
	return (FALSE);
}

// Inicializo los valores de map y chekeo archivo y relleno datos en \
las funciones parse_map
int	parse_file(t_game *game, char *argv)
{
	int		fd;
	char	*line;

	game->map.floor_color.b = -1;
	game->map.floor_color.g = -1;
	game->map.floor_color.r = -1;
	game->map.ceiling_color.b = -1;
	game->map.ceiling_color.g = -1;
	game->map.ceiling_color.r = -1;
	game->map.north_texture = NULL;
	game->map.south_texture = NULL;
	game->map.east_texture = NULL;
	game->map.west_texture = NULL;
	game->map.map = NULL;
	game->map.temp_map = NULL;
	game->map.mapX = 0;
	game->map.mapY = 0;
	game->map.width = 0;
	game->map.height = 0;
	game->map.mapS = 64;
	game->map.cellSize = 63;
	fd = open(argv, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Error\nInvalid file\n", 2);
		return (FAILURE);
	}
	while (line)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		while (line[0] == ' ')
			line++;
		parse_texture_and_colors(game, line);
		if (textures_and_colors_get(game) == TRUE)
			break;
	}
	while (line)
	{
		line = get_next_line(fd);
		if (!line)
			break;
		parse_map(game, line);
	}
	close(fd);
	printf("longitud de la string: %d\n", ft_strlen(game->map.temp_map));
	printf("HOLA SOY LA POLLA temp_map: %s\n", game->map.temp_map);
	return (SUCCESS);
}
