/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rakman <rakman@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 09:19:12 by rakman            #+#    #+#             */
/*   Updated: 2025/04/10 10:10:24 by rakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	remainder = ft_strdupx(&str[i + 1]);
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
	static char	*remainder;
	char		*rawline;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	rawline = hl_get_preproc_line(remainder, fd);
	if (rawline == NULL)
	{
		remainder = NULL;
		return (NULL);
	}
	line = hl_trim_the_line(rawline);
	remainder = hl_calculate_remainder(rawline);
	free(rawline);
	return (line);
}
