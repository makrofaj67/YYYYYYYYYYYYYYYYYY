/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rakman <rakman@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:41:41 by rakman            #+#    #+#             */
/*   Updated: 2024/11/19 01:33:55 by rakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t dstsize)
{
	size_t	i;
	int		len;

	i = 0;
	len = ft_strlen(src);
	if (src == NULL)
	{
		return (0);
	}
	if (dstsize == 0)
	{
		return (len);
	}
	while ((i < (dstsize - 1)) && src[i] != 0)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (len);
}
//Copy string src to buffer dst of size dsize.
//buffera source'un dstsize kadarını kopyalar

//en fazla dstsize - 1 kadar kopyalar
//kesinlikle NUL terminate eder

//dstsize buffer uzunluğundan büyük veya eşitse srclengt döndür
