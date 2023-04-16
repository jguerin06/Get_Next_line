#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"

static char *return_buffer(char *buffer, int fd)
{
	char	*str;
	int		r;
	r = 1;

	str = ft_calloc(BUFFER_SIZE, sizeof(char));
	while(r > 0)
	{
		r = read(fd, str, BUFFER_SIZE);
		if (r < 0)
		{
			// free
		}
		buffer = ft_strjoin(buffer, str);
		if(find_nl(buffer) == 1)
			break;
	}
	return(buffer);
}

static char *return_read(char *buffer)
{
	int		i;
	char	*str;
	i = 0;
	while(buffer[i])
	{
		if(buffer[i] == '\n')
			break;
		i++;
	}
	malloc(sizeof(char) * i + 1);
	i = 0;
	return(i);
}

static char *delete_return(char *buffer)
{

}

char *get_next_line(int fd)
{
	char *po;
	static char *buffer = NULL;

	if(fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	// 1ere etape ; renvoie tout ce qui a ete lu au buffer
	buffer = return_buffer(buffer, fd);

	// 2eme etape ; renvoie la ligne qui a ete lue
	po = return_read(buffer);

	// 3eme etape ; supprimer ce qui a ete renvoye par *po
	buffer = delete_return(buffer);
	return (po);
}

int main(void)
{
	char	*line;
	int		fd;

	fd = open("test.txt", O_RDONLY);
	while(line != NULL)
	{
		printf("%s", line);
	}
}
