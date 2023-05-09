/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguerin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 16:27:35 by jguerin           #+#    #+#             */
/*   Updated: 2023/04/25 16:27:37 by jguerin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

// Returns everything that has been read to the buffer

static char	*return_buffer(char *buffer, int fd)
{
	char	str[BUFFER_SIZE + 1];
	int		r;

	r = 1;
	while (r != 0 && !find_nl(buffer))
	{
		r = read(fd, str, BUFFER_SIZE);
		if (r < 0)
		{
			free(buffer);
			return (NULL);
		}
		str[r] = '\0';
		buffer = ft_strjoin(buffer, str);
	}
	return (buffer);
}

// Returns the line that has been read

static char	*return_read(char *buffer)
{
	int		i;
	char	*str;

	i = 0;
	if (!buffer[0])
		return (NULL);
	str = ft_calloc(sizeof(char), ft_strlen(buffer) + 2);
	if (!str)
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
	{
		str[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
		str[i] = buffer[i];
	return (str);
}

// Remove what has been returned by str

static char	*delete_return(char *buffer)
{
	char	*new_storage;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (buffer = NULL);
	}
	new_storage = ft_calloc(sizeof(char), ft_strlen(buffer) - i + 1);
	if (!new_storage)
		return (NULL);
	i++;
	while (buffer[i])
		new_storage[j++] = buffer [i++];
	free(buffer);
	return (new_storage);
}

char	*get_next_line(int fd)
{
	char		*str;
	static char	*buffer[4096];

	str = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer[fd] = return_buffer(buffer[fd], fd);
	if (!buffer[fd])
		return (NULL);
	str = return_read(buffer[fd]);
	buffer[fd] = delete_return(buffer[fd]);
	if (!buffer[fd])
		free(buffer[fd]);
	return (str);
}
