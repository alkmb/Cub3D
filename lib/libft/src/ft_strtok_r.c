/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok_r.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprada-t <gprada-t@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 15:53:31 by kmb               #+#    #+#             */
/*   Updated: 2024/07/05 12:54:41 by gprada-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

char	*ft_strtok_r(char *str, const char *delim, char **saveptr)
{
	char	*end;

	if (str == NULL)
		str = *saveptr;
	if (*str == '\0')
		return (NULL);
	str += ft_strspn(str, delim);
	if (*str == '\0')
		return (NULL);
	end = str + ft_strcspn(str, delim);
	if (*end == '\0')
		*saveptr = end;
	else
	{
		*end = '\0';
		*saveptr = end + 1;
	}
	return (str);
}
