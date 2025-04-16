/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rakman <rakman@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:20:32 by rakman            #+#    #+#             */
/*   Updated: 2024/11/18 22:40:54 by rakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			iter;
	unsigned char	*dstpt;
	unsigned char	*srcpt;

	iter = 0;
	dstpt = (unsigned char *)dst;
	srcpt = (unsigned char *)src;
	if ((srcpt == NULL) && (dstpt == NULL))
	{
		return (NULL);
	}
	while (n > 0)
	{
		dstpt[iter] = srcpt[iter];
		iter++;
		n--;
	}
	return (dst);
}
