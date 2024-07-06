/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprada-t <gprada-t@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 22:17:28 by akambou           #+#    #+#             */
/*   Updated: 2024/07/05 12:54:41 by gprada-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	char	*new;
	int		size;

	size = 0;
	while (str[size])
		size++;
	new = malloc((size + 1) * sizeof(char));
	if (!new)
		return (NULL);
	size = 0;
	while (str[size])
	{
		new[size] = str[size];
		size++;
	}
	new[size] = '\0';
	return (new);
}
