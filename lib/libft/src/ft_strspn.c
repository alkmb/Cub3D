/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strspn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprada-t <gprada-t@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 15:58:08 by kmb               #+#    #+#             */
/*   Updated: 2024/07/05 12:54:41 by gprada-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strspn(char *str, const char *str2)
{
	size_t	i;
	char	*s2;

	i = 0;
	s2 = (char *)str2;
	while (str[i])
	{
		if (ft_strchr(s2, str[i]) == 0)
			break ;
		++i;
	}
	return (i);
}
