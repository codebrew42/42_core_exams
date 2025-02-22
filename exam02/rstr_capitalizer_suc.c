#include <unistd.h>


int	is_space_or_tab(char c)
{
	if (c == ' ' || c == '\t' || c == '\v')
		return 1;
	return 0;
}

int	is_last_char(char *str)
{
	if (!*str)
		return (0);
	str++;
	if (is_space_or_tab(*str) == 1 || !*str)
		return 1;
	return 0;
}

int	is_uppercase(char c)
{
	if (c >= 'A' && c <= 'Z')
		return 1;
	return 0;
}

int	is_lowercase(char c)
{
	if (c >= 'a' && c <= 'z')
		return 1;
	return 0;
}

char	rev_case(char c)
{
	if (is_uppercase(c))
		return (c + 32);
	else if (is_lowercase(c))
		return (c - 32);
	else
		return c;
}


int	main(int ac, char **av)
{
	int i = 1;
	int j;

	if (ac == 1)
	{
		write(1, "\n", 1);
		return -1;
	}
	while (av[i])
	{
		j = 0;
		while(av[i][j])
		{
			char c= av[i][j];
			if (is_last_char(&av[i][j]) && is_lowercase(c))
			{
				c = rev_case(c);
				write(1, &c, 1);
			}
			else if (!is_last_char(&av[i][j]) && is_uppercase(c))
			{
				c = rev_case(c);
				write(1, &c, 1);
			}
			else
				write(1, &c, 1);
			j++;
		}
		write(1, "\n", 1);
		i++;

	}
	return 0;
}
