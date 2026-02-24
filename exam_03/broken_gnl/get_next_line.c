#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char buffer[BUFFER_SIZE + 1] = "";
	char *tmp;
	char *res = NULL;
	
	int	count;

	while (1)
	{
		tmp = ft_strchr(buffer, '\n')
		if (tmp)
		{
			if (!str_append_mem(&res, buffer, tmp - buffer - 1))
		}
	}
}