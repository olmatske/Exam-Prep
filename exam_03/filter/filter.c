
#define _GNU_SOURCE  // Para memmem()
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

void ft_filter(char *buffer, const char *target);

int main(int argc, char **argv)
{
	if (argc != 2 || argv[1][0] == '\0')
		return 1;
	char temp[BUFFER_SIZE];
	char *result = NULL;
	char *buffer;
	int total_read = 0;
	ssize_t bytes;

	while ((bytes = read(0, temp, BUFFER_SIZE)) > 0)
	{
		buffer = realloc(result, total_read + bytes + 1);
		if (!buffer)
		{
			free(result);
			perror("realloc");
			return 1;
		}
		result = buffer;
		memmove(result + total_read, temp, bytes);
		total_read += bytes;
		result[total_read] = '\0';
	}
	if (bytes < 0)
	{
		perror("read");
		free(result);
		return 1;
	}
	if (!result)
		return 0;
	ft_filter(result, argv[1]);
	free(result);
	return 0;
}

void ft_filter(char *buffer, const char *target)
{
	int i = 0;
	int target_len = strlen(target);
	int j, k;

	while (buffer[i])
	{
		j = 0;
		while (target[j] && (buffer[i + j] == target[j]))
			j++;
		
		if (j == target_len)
		{
			k = 0;
			while (k < target_len)
			{
				write(1, "*", 1);
				k++;
			}
			i += target_len;
		}
		else
		{
			write(1, &buffer[i], 1);
			i++;
		}
	}
}









// #define _GNU_SOURCE
// #ifndef BUFFER_SIZE
// #	define BUFFER_SIZE 42
// #endif
// #include <string.h>
// #include <stdio.h>
// #include <fcntl.h>
// #include <unistd.h>
// #include <stdlib.h>

// // Allowed functions: read, write, strlen, memmem, memmove, malloc, calloc,
// // realloc, free, printf, fprintf, stdout, stderr, perror


// char	*filter(char *str, char *to_change, char *res);

// // only use realloc and memmove to dynamically allocate memory from each read
// int	main(int argc, char **argv)
// {
// 	char	*needle;
// 	char	*res = NULL;
// 	char	haystack[BUFFER_SIZE];
// 	ssize_t	nread;

// 	if (argc != 2)
// 		return (perror("Error"), 1);
// 	needle = argv[1];
// 	nread = read(0, haystack, sizeof(haystack) - 1);
// 	if (nread < 0)
// 		return (perror("Error: read - "), 1);
// 	res = malloc(sizeof(char) * nread + 1);
// 	haystack[nread] = '\0';
// 	res = filter(haystack, needle, res);
// 	if (!res)
// 		return (perror("Error: AAA"), 1);
// 	return (printf("%s\n", res), 0);
// }


// char	*filter(char *str, char *to_change, char *res)
// {
// 	int	i;
// 	int	k;
// 	int	j;

// 	i = 0;
// 	k = 0;
// 	j = 0;
// 	while (str[i])
// 	{
// 		j = 0;
// 		while (to_change[j] && str[i + j] == to_change[j])
// 			j++;
// 		if (to_change[j] == '\0')
// 		{
// 			j = 0;
// 			while (to_change[j])
// 			{
// 				res[k] = '*';
// 				k++;
// 				j++;
// 			}
// 			i += j;
// 		}
// 		else
// 			res[k++] = str[i++];
// 	}
// 	res[k] = '\0';
// 	return (res);
// }


	// res = memmem(haystack, nread, needle, strlen(needle));


	// char	*str = "It's Britney Bitch oiiai";
	// char	*to_change = "i";
	// char	*res;

	// res = malloc(sizeof(char) * strlen(str) + 1);

	// printf("%s\n", res);


// printf("AAAAAAAAAAAAAAAAAAAA\n");





















































// void ft_filter(char *buffer, const char *target)
// {
// 	int i = 0;
// 	int target_len = strlen(target);
// 	int j, k;

// 	while (buffer[i])
// 	{
// 		j = 0;
// 		while (target[j] && (buffer[i + j] == target[j]))
// 			j++;
		
// 		if (j == target_len)
// 		{
// 			k = 0;
// 			while (k < target_len)
// 			{
// 				write(1, "*", 1);
// 				k++;
// 			}
// 			i += target_len;
// 		}
// 		else
// 		{
// 			write(1, &buffer[i], 1);
// 			i++;
// 		}
// 	}
// }

// int main(int argc, char **argv)
// {
// 	if (argc != 2 || argv[1][0] == '\0')
// 		return 1;

// 	char temp[BUFFER_SIZE];
// 	char *result = NULL;
// 	char *buffer;
// 	int total_read = 0;
// 	ssize_t bytes;

// 	while ((bytes = read(0, temp, BUFFER_SIZE)) > 0)
// 	{
// 		buffer = realloc(result, total_read + bytes + 1);
// 		if (!buffer)
// 		{
// 			free(result);
// 			perror("realloc");
// 			return 1;
// 		}
		
// 		result = buffer;
		
// 		memmove(result + total_read, temp, bytes);
// 		total_read += bytes;
// 		result[total_read] = '\0';
// 	}

// 	if (bytes < 0)
// 	{
// 		perror("read");
// 		free(result);
// 		return 1;
// 	}

// 	if (!result)
// 		return 0;

// 	ft_filter(result, argv[1]);
// 	free(result);
// 	return 0;
// }