#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>

//can only: %c + whitespaces
void	skip_whitespaces(void)
{
	int next_c;

	next_c = fgetc(stdin);
	while (isspace(next_c))
		next_c = fgetc(stdin);
	if (next_c != -1)
		ungetc(next_c, stdin);
}
int		handle_char(char *c_ptr)
{
	int	c;
	c = fgetc(stdin);
	if (c == -1)
		return (0);
	*c_ptr = (unsigned char)c;
	return (1);
}

int		ft_scanf(const char *format, ...)
{

	va_list		args;
	int			count = 0;
	int			i;

	va_start(args, format);
	while (*format)
	{
		if (*format == '%' && ++format)
		{
			if (*format == 'c')
				count += handle_char(va_arg(args, char *));
			else
				break ;
		}
		else if (isspace(*format))
			skip_whitespaces();
		format++;
	}
	va_end(args);
	return (count);
}

int		main(void)
{
	char c1;
	char c2;

	printf("Enter one char:\n");
	int	res1 = ft_scanf("%c %c", &c1, &c2);
	printf("c1[%c], c2[%c]\n", c1, c2);

	//int res = ft_scanf("%s %d %c", name, age, char));

	return (0);
}