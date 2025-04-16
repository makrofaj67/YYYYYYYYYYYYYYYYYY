/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rakman <rakman@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 13:35:21 by rakman            #+#    #+#             */
/*   Updated: 2024/11/18 15:46:07 by rakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			iter;
	unsigned char	*ptr;

	iter = 0;
	ptr = (unsigned char *)b;
	while (len > 0)
	{
		ptr[iter] = (unsigned char)c;
		iter++;
		len--;
	}
	return (b);
}
