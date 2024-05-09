/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmb <kmb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 09:18:04 by gprada-t          #+#    #+#             */
/*   Updated: 2024/05/06 01:56:11 by kmb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

// int	parse_map(char *line)
// {
// 	int		i;

// 	i = -1;
// 	while (line[++i])
// 	{
// 		if (line[i] != ' ' || line[i] != '1' || line[i] != '0'
// 			|| line[i] != 'N' || line[i] != 'S'
// 			|| line[i] != 'E' || line[i] != 'W')
// 		{
// 			ft_putstr_fd("Error\nInvalid map\n", 2);
// 			return (FAILURE);
// 		}
// 	}
// 	return (SUCCESS);
// }

// void	parse_color(t_game *game, char *line)
// {
// 	int		i;
// 	int		r;
// 	int		g;
// 	int		b;

// 	i = 0;
// 	while (line[i] != ',')
// 		i++;
// 	r = ft_atoi(line + 1);
// 	g = ft_atoi(line + i + 1);
// 	b = ft_atoi(line + i + 1);
// }

// void	parse_texture(t_game *game, char *line)
// {
// 	int		i;
// 	char	*path;

// 	i = 0;
// 	while (line[i] != ' ')
// 		i++;
// 	path = ft_strdup(line + i);
// }

// int	parse_file(t_game *game, char *argv)
// {
// 	int		i;
// 	int		fd;
// 	char	*line;

// 	i = -1;
// 	fd = open(argv, O_RDONLY);
// 	if (fd < 0)
// 	{
// 		ft_putstr_fd("Error\nInvalid file\n", 2);
// 		return (FAILURE);
// 	}
// 	line = get_next_line(fd);
// 	while (line != NULL)
// 	{
// 		if (line[0] == 'F' || line[0] == 'C')
// 			parse_color(game, line);
// 		else if (line[0] == 'N' || line[0] == 'S' || line[0] == 'E' || line[0] == 'W')
// 			parse_texture(game, line);
// 		else if (line[0] == '1' || line[0] == '0' || line[0] == 'N' || line[0] == 'S' || line[0] == 'E' || line[0] == 'W')
// 			parse_map(game, line);
// 		else
// 		{
// 			ft_putstr_fd("Error\nInvalid map\n", 2);
// 			return (FAILURE);
// 		}
// 		free(line);
// 		line = get_next_line(fd);
// 	}
// }
