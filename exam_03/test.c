#include <stdio.h>

// s , d , c

int	main(void)
{
	char	type[1024];
	printf("input a string: ");
	if (scanf("%s", &type) == 1)
	{
		while (type == fgetc(stdin))
		{
			printf("\nthe input is %s\n", type);
			ungetc(type, 0);
		}
	}
	// return(printf("wrong\n"), 1);
	// printf("addition: %d + 3 = %d\n", number, number + 3);
	return (0);
}