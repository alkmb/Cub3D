/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprada-t <gprada-t@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 21:47:42 by akambou           #+#    #+#             */
/*   Updated: 2024/07/05 12:54:41 by gprada-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_len(int n)
{
	int				len;
	long long int	temp;

	len = 0;
	temp = n;
	if (n < 0)
	{
		len++;
		temp = -(long long int)n;
	}
	if (temp == 0)
	{
		len = 1;
	}
	else
	{
		while (temp > 0)
		{
			temp /= 10;
			len++;
		}
	}
	return (len);
}

static void	itoa1(char *str, int n, int len)
{
	long long int	temp;

	temp = n;
	if (n < 0)
	{
		str[0] = '-';
		temp = -(long long int)n;
	}
	str[len] = '\0';
	if (temp == 0)
	{
		str[0] = '0';
	}
	else
	{
		while (temp > 0)
		{
			len--;
			str[len] = (char)((temp % 10) + '0');
			temp /= 10;
		}
	}
}

char	*ft_itoa(int n)
{
	int		len;
	char	*str;

	len = get_len(n);
	str = (char *)malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	itoa1(str, n, len);
	return (str);
}
