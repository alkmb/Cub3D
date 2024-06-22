/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akambou <akambou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 16:40:15 by gprada-t          #+#    #+#             */
/*   Updated: 2024/06/19 21:07:18 by akambou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	*str_to_int_array(char *map, int x, int y)
{
	int	*array;
	int	i;
	int	index;

	i = 0;
	index = 0;
	array = malloc(sizeof(int) * x * y + 1);
	if (!array)
		return (NULL);
	while (map[i] && index < (x * y + 1))
	{
		handle_char(map[i], array, &index, x);
		i++;
	}
	return (array);
}

void	handle_char(char c, int *array, int *index, int x)
{
	if (c == '0')
		array[(*index)++] = 0;
	else if (c == '1')
		array[(*index)++] = 1;
	else if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
		array[(*index)++] = 3;
	else if (c == ' ')
		array[(*index)++] = 2;
	else if (c == '\n')
		fill_spaces(array, index, x);
	else if (c == '\t')
		fill_tabs(array, index);
	else if (c == 'D')
		array[(*index)++] = 7;
	else if (c == 'O')
		array[(*index)++] = 8;
}

void	fill_tabs(int *array, int *index)
{
	int	k;

	k = -1;
	while (++k < 4)
		array[(*index)++] = 2;
}

void	fill_spaces(int *array, int *index, int x)
{
	while ((*index) % x != 0)
		array[(*index)++] = 2;
}
