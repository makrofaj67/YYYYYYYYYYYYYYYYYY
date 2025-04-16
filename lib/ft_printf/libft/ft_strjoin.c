/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rakman <rakman@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 05:54:10 by rakman            #+#    #+#             */
/*   Updated: 2024/11/18 05:54:13 by rakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	startlen;
	size_t	endlen;
	char	*newstring;

	if ((s1 || s2) == 0)
		return (NULL);
	startlen = ft_strlen(s1);
	endlen = ft_strlen(s2);
	newstring = (char *)malloc(sizeof(char) * (startlen + endlen + 1));
	if (newstring == NULL)
		return (NULL);
	ft_strlcpy(newstring, s1, startlen + 1);
	ft_strlcat(newstring, s2, startlen + endlen + 1);
	return (newstring);
}
