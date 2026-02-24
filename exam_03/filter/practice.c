#define _GNU_SOURCE
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif


#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

void	filter(char *res, const char *target);

int	main(int argc, char **argv)
{
	if (argc != 2 || argv[1][0] == '\0')
		return (1);
	char	*res;
	char	*buf;
	char	tmp[BUFFER_SIZE];
	int		nread = 0;
	ssize_t	bytes;

	while ((bytes = read(0, tmp, BUFFER_SIZE)) > 0)
	{
		buf = realloc(res, nread + bytes + 1);
		if (!buf)
		{
			free(res);
			perror("realloc");
			return (1);
		}
		res = buf;
		memmove(res + nread, tmp, bytes);
		nread += bytes;
		res[nread] = '\0';
	}
	if (bytes  < 0)
	{
		free (res);
		perror("read");
		return (1);
	}
	if (!res)
		return (0);
	filter(res, argv[1]);
	return (0);
}

void	filter(char *res, const char *target)
{
	int	i = 0;
	int j = 0;
	int	k = 0;
	int target_len = strlen(target);

	while (res[i])
	{
		j = 0;
		while (target[j] && res[i + j] == target[j])
			j++;
		if (j == target_len)
		{
			k = 0;
			while (k < target_len)
			{
				write(1, "*", 1);
				k++;
			}
		}
		else
		{
			write(1, &res[i], 1);
			i++;
		}
	}
}