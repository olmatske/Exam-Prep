// Allowed functions: fgetc, ungetc, ferror, feof, isspace, isdigit, stdin, va_start, va_arg, va_copy, va_end


// - It will manage only the following conversions: s, d, and c

#ifndef BUFFER
# define BUFFER 1024


#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>
# endif

int match_space(FILE *f)
{
	int	c;

	c = getc(f);
	if (c == EOF)
		return (1);
	while (isspace(c))
	{
		c = fgetc(f);
		if (c == EOF)
			return (1);
	}
	if (ungetc(c, f) == EOF)
		return (1);
	return (0);
}

int match_char(FILE *f, char c)
{
	int	ch;

	ch = fgetc(f);
	if (ch == EOF)
		return (1);
	if (ch != (unsigned char)c)
	{
		if (ungetc(ch, f) == EOF)
			return (1);
		return (0);
	}
	return (1);
}

int scan_char(FILE *f, va_list ap)
{
	int	c;
	char *dest;

	c = fgetc(f);
	if (c == EOF)
		return (0);
	dest = va_arg(ap, char *);
	*dest = (char)c;
	return (1);
}

int scan_int(FILE *f, va_list ap)
{
	int	i;
	int	sign = 1;
	long	num = 0;
	int		ndigits = 0;
	int		*dest;

	i = fgetc(f);
	if (i == '-')
		sign = -1;
	else
	{
		if (i != EOF && ungetc(i, f) == EOF)
			return (0);
	}
	while (1)
	{
		i = fgetc(f);
		if (i == EOF)
			break;
		if (!isdigit((unsigned char)i))
		{
			if (ungetc(i, f) == EOF)
				return (0);
			break;
		}
		num = num * 10 + (i - '0');
		ndigits++;
	}
	if (ndigits == 0)
		return (0);
	dest = va_arg(ap, int *);
	*dest = (int)(sign * num);
	return (1);
}

int scan_string(FILE *f, va_list ap)
{
	char	*dest;
	int		c;
	int		i;

	i = 0;
	dest = va_arg(ap, char *);
	while (1)
	{
		c = fgetc(f);
		if (c == EOF)
			break;
		if (isspace((unsigned char)c))
		{
			if (ungetc(c, f) == EOF)
				return (0);
			break;
		}
		dest[i++] = (char)c;
	}
	if (i == 0)
		return (0);
	dest[i] = '\0';
	return (1);
}


int	match_conv(FILE *f, const char **format, va_list ap)
{
	switch (**format)
	{
		case 'c':
			return scan_char(f, ap);
		case 'd':
			match_space(f);
			return scan_int(f, ap);
		case 's':
			match_space(f);
			return scan_string(f, ap);
		case EOF:
			return -1;
		default:
			return -1;
	}
}

int ft_vfscanf(FILE *f, const char *format, va_list ap)
{
	int nconv = 0;

	int c = fgetc(f);
	if (c == EOF)
		return EOF;
	ungetc(c, f);

	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (match_conv(f, &format, ap) != 1)
				break;
			else
				nconv++;
		}
		else if (isspace(*format))
		{
			if (match_space(f) == -1)
				break;
		}
		else if (match_char(f, *format) != 1)
			break;
		format++;
	}
	
	if (ferror(f))
		return EOF;
	return nconv;
}


int ft_scanf(const char *format, ...)
{
	va_list	ap;
	int		ret;

	va_start(ap, format);
	ret = ft_vfscanf(stdin, format, ap);
	va_end(ap);
	return ret;
}




int	main(void)
{
	char	type[BUFFER];
	printf("input a type: ");
	if (scanf("%s", type) != 1)
		return(printf("wrong\n"), 1);
	printf("\nthe input is %s\n", type);
	return (0);
}


	// {
		// while (type == fgetc(stdin))
		// {
		// 	printf("\nthe input is %c\n", type);
		// 	ungetc(type, 0);
		// }
	// }
		// printf("addition: %d + 3 = %d\n", type, type + 3);