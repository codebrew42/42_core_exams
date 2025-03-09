
#include <stdarg.h>
#include <stdio.h>


static void	skip_whitespaces(void)
{
	int c;

	while ((c = fgetc(stdin))!= EOF && isspace(c))
	;
	if (c != EOF)
		ungetc(c, stdin);
}

int	handle_char(char *c_ptr)
{
	int c = fgetc(stdin);
	if (c == -1)
		return (0);
	*c_ptr = (unsigned char)c;
	return (1);
}
/*
int	handle_iint(int *num)
{



	return (1);
}
*/

/**
@return 1 on success, 0 on fail
*/
/*
int	handle_str(char *str)
{


	return(1);
}
*/

int	ft_scanf(const char *format, ...)
{
	va_list		args;
	int			count;

	count = 0;
	va_start(args, format); //args= dest, src_start=format
	while (*format)
	{
		//handle: formats
		if (*format == '%' && ++format)
		{
			// if (*format == 's')
			// 	count += handle_str();
			// else if (*format == 'd')
			if (*format == 'c')
				count += handle_char(va_arg(args, char *));
			else
				break;
		}
		else //handle: literal
		{
			c_in = fgetc(stdin);
 			if (c_in != *format)  // Check for  unmatching (input char vs. format)
			{
				ungetc(c_in, stdin);
				break ;
			}
		}
		format++;
	}
	va_end(args);
	return (count);
}

int	main(void)
{
	int age;
	char name[100];
	char	c;
	printf("Enter char:\n");
	int res = ft_scanf("%c", c);
	printf("Result: [%c]", c);
	return (0);
}