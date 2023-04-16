#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H

#define BUFFER_SIZE 42

#include <unistd.h>
#include <stdlib.h>

void	*ft_calloc(size_t count, size_t size);
char	*ft_strjoin(char *s1, char *s2);
char	*get_next_line(int fd);
int		find_nl(char *s);

#endif
