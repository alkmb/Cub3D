/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprada-t <gprada-t@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 14:09:29 by kmb               #+#    #+#             */
/*   Updated: 2024/07/05 12:54:41 by gprada-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtok(char *str, const char *delim)
{
	static char	*src = NULL;
	char		*p;
	char		*ret;

	ret = NULL;
	if (str != NULL)
		src = str;
	if (src == NULL)
		return (NULL);
	p = ft_strpbrk(src, delim);
	if (p != NULL)
	{
		*p = 0;
		ret = src;
		src = ++p;
	}
	else if (*src)
	{
		ret = src;
		src = NULL;
	}
	return (ret);
}
