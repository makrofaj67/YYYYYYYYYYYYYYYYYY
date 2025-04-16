/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rakman <rakman@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 19:37:25 by rakman            #+#    #+#             */
/*   Updated: 2024/11/19 06:47:13 by rakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	startindex;
	size_t	endindex;
	char	*trimmed;

	startindex = 0;
	endindex = ft_strlen(s1);
	while (s1[startindex] && ft_strchr(set, s1[startindex]))
		startindex++;
	while (endindex > startindex && ft_strchr(set, s1[endindex - 1]))
		endindex--;
	trimmed = malloc(sizeof(char) * (endindex - startindex + 1));
	if (trimmed == NULL)
		return (NULL);
	ft_strlcpy(trimmed, &s1[startindex], endindex - startindex + 1);
	return (trimmed);
}
