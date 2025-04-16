/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rakman <rakman@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 19:13:40 by rakman            #+#    #+#             */
/*   Updated: 2024/11/19 00:52:57 by rakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*targetptr;

	targetptr = malloc(count * size);
	if (targetptr == NULL)
	{
		return (NULL);
	}
	ft_bzero(targetptr, count * size);
	return (targetptr);
}
