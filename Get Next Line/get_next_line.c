/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguerin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 12:31:57 by jguerin           #+#    #+#             */
/*   Updated: 2023/04/16 12:31:58 by jguerin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"

// 1ere etape ; renvoie tout ce qui a ete lu au buffer

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

// 2eme etape ; renvoie la ligne qui a ete lue

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

// 3eme etape ; supprimer ce qui a ete renvoye par *po

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
	static char	*buffer = NULL;

	str = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, str, 0) < 0)
		return (NULL);
	buffer = return_buffer(buffer, fd);
	if (!buffer)
		return (NULL);
	str = return_read(buffer);
	buffer = delete_return(buffer);
	if (!buffer)
		free(buffer);
	return (str);
}

/* int	main(void)
{
	char	*line;
	int		fd;

	fd = open("test.txt", O_RDONLY);
	line = get_next_line(fd);
	while (line != NULL)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
}
*/
