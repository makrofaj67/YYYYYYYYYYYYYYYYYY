/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rakman <rakman@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 16:15:09 by rakman            #+#    #+#             */
/*   Updated: 2024/11/19 06:59:49 by rakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*subptr;
	size_t	srclength;
	size_t	iter;

	iter = 0;
	srclength = ft_strlen(s);
	if (s == NULL)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	if (len > (srclength - start))
		len = srclength - start;
	subptr = (char *)malloc(sizeof(char) * (len + 1));
	if (subptr == NULL)
		return (NULL);
	while (iter < len && s[start + iter])
	{
		subptr[iter] = s[start + iter];
		iter++;
	}
	subptr[iter] = '\0';
	return (subptr);
}
