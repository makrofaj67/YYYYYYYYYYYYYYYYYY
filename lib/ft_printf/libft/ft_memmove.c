/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rakman <rakman@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 22:33:03 by rakman            #+#    #+#             */
/*   Updated: 2024/11/18 15:43:13 by rakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	iter;
	char	*dstprt;
	char	*srcprt;

	iter = 0;
	dstprt = (char *)dst;
	srcprt = (char *)src;
	if ((dstprt == NULL) && (srcprt == NULL))
		return (NULL);
	if (dstprt > srcprt)
	{
		while (len-- > 0)
		{
			dstprt[len] = srcprt[len];
		}
	}
	else
	{
		while (iter < len)
		{
			dstprt[iter] = srcprt[iter];
			iter++;
		}
	}
	return (dst);
}
