/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rakman <rakman@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 09:19:12 by rakman            #+#    #+#             */
/*   Updated: 2025/01/18 18:23:05 by rakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*hl_get_preproc_line(char *remainder, int fd)
{
	char	*buffer;
	int		readed_bytes;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	readed_bytes = 1;
	while (hl_has_newline(remainder) == 0 && readed_bytes > 0)
	{
		readed_bytes = read(fd, buffer, BUFFER_SIZE);
		if (readed_bytes == 0)
			break ;
		if (readed_bytes == -1)
		{
			free(buffer);
			free(remainder);
			return (NULL);
		}
		buffer[readed_bytes] = '\0';
		remainder = ft_strjoinx(remainder, buffer);
	}
	free(buffer);
	return (remainder);
}

char	*hl_calculate_remainder(char *str)
{
	int		i;
	char	*remainder;

	i = 0;
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	if (str[i] == '\0')
		return (NULL);
	remainder = ft_strdup(&str[i + 1]);
	return (remainder);
}

char	*hl_trim_the_line(char *str)
{
	int		i;
	char	*line;

	i = 0;
	if ((str == NULL) || (str[0] == '\0'))
		return (NULL);
	while ((str[i] != '\0') && (str[i] != '\n'))
		i++;
	if (str[i] == '\n')
		i++;
	line = malloc(sizeof(char) * (i + 1));
	if (line == NULL)
		return (NULL);
	i = -1;
	while ((str[++i] != '\0') && (str[i] != '\n'))
		line[i] = str[i];
	if (str[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*remainder[MAX_FD];
	char		*rawline;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= MAX_FD)
		return (NULL);
	rawline = hl_get_preproc_line(remainder[fd], fd);
	if (rawline == NULL)
	{
		remainder[fd] = NULL;
		return (NULL);
	}
	line = hl_trim_the_line(rawline);
	remainder[fd] = hl_calculate_remainder(rawline);
	free(rawline);
	return (line);
}
