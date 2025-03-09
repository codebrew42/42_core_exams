# include <stdio.h>
# include <unistd.h>
# include <stdarg.h>
# include <ctype.h>

static void	skip_whitespace(void)
{
	int	c;

	while ((c = fgetc(stdin)) != EOF && isspace(c))
		;
	if (c != EOF)
		ungetc(c, stdin);
}

static int	handle_str(char *str)
{
	int	c;
	int	i;

	i = 0;
	skip_whitespace();
	while ((c = fgetc(stdin)) != EOF && !isspace(c))
		str[i++] = c;
	if (i == 0)
		return (0);
	str[i] = '\0';
	if (c != EOF)
		ungetc(c, stdin);
	return (1);
}

static int	handle_int(int *num)
{
	int		c;
	int		sign;
	long	result;

	result = 0;
	sign = 1;
	skip_whitespace();
	c = fgetc(stdin);
	if ((c == '-' || c == '+') && (c = fgetc(stdin), 1))
		sign = 44 - c; // 43 for '+', 45 for '-'
	if (!isdigit(c))
	{
		ungetc(c, stdin);
		return (0);
	}
	while (isdigit(c))
	{
		result = result * 10 + (c - '0');
		c = fgetc(stdin);
	}
	*num = (int)(result * sign);
	if (c != EOF)
		ungetc(c, stdin);
	return (1);
}

static int	handle_char(char *c_ptr)
{
	int	c;

	c = fgetc(stdin);
	if (c == EOF)
		return (0);
	*c_ptr = (unsigned char)c;
	return (1);
}

int	ft_scanf(const char *format, ...)
{
	va_list	args;
	int		count;
	int		c_in;

	va_start(args, format);
	count = 0;
	while (*format)
	{
		if (*format == '%' && *(++format))
		{
			if (*format == 's' && handle_str(va_arg(args, char *)))
				count++;
			else if (*format == 'd' && handle_int(va_arg(args, int *)))
				count++;
			else if (*format == 'c' && handle_char(va_arg(args, char *)))
				count++;
			else
				break ;
		}
		else if (isspace(*format))
		{
			skip_whitespace();
		}
		else
		{
			if ((c_in = fgetc(stdin)) != *format)
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

/*
[res1](base) jieunpark@eng---macbook ref % ./scanf 
Enter c1 and c2:j hihihi l
Result of scanf; c1[j], c2[l]%
(base) jieunpark@eng---macbook ref % ./scanf
Enter c1 and c2: k ;
reading two characters failed%

[res2]
(base) jieunpark@eng---macbook ref % ./scanf
Enter Name and Age:jieun hihihi 30
Result of scanf; Name[jieun], Age[30]%     
*/
int main(void)
{
//	[res1]
	char name[100];
	int age;
	printf("Enter Name and Age:");
	int res = ft_scanf("%s hihihi %d", name, &age);

	printf("Result of scanf; Name[%s], Age[%d]", name, age);

// [res2]
	char c1;
	char c2;
	int age;
	printf("Enter c1 and c2:");
	int res = ft_scanf("%c hihihi %c", &c1, &c2);

	if (res == 2)
		printf("Result of scanf; c1[%c], c2[%c]", c1, c2);
	else
		printf("reading two characters failed");
	return (0);
}