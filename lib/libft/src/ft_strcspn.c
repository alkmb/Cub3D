/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcspn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprada-t <gprada-t@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 15:56:32 by kmb               #+#    #+#             */
/*   Updated: 2024/07/05 12:54:41 by gprada-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strcspn(char *str, const char *str2)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (str[i])
	{
		j = 0;
		while (str2[j])
		{
			if (str[i] == str2[j])
				return (i);
			j++;
		}
		i++;
	}
	return (i);
}
