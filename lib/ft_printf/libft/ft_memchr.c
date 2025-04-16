/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rakman <rakman@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:32:18 by rakman            #+#    #+#             */
/*   Updated: 2024/11/18 15:23:14 by rakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*targetstr;
	unsigned char	targetbyte;

	i = 0;
	targetstr = (unsigned char *)s;
	targetbyte = (unsigned char)c;
	while (i < n)
	{
		if (targetstr[i] == targetbyte)
			return ((void *)(targetstr + i));
		i++;
	}
	return (NULL);
}
