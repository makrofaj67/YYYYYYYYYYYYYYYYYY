/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rakman <rakman@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 05:26:45 by rakman            #+#    #+#             */
/*   Updated: 2024/11/19 01:33:19 by rakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*temp;
	int		s1lenght;

	s1lenght = ft_strlen(s1);
	temp = (char *)malloc(s1lenght + 1);
	if (temp == NULL)
		return (NULL);
	ft_memcpy(temp, s1, ft_strlen(s1) + 1);
	return (temp);
}
