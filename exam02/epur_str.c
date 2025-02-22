#include <unistd.h>

int	ft_strlen(char *c)
{
	int i = 0;
	while(c[i])
		i++;
	return i;
}


int	is_space_or_tab(char c)
{
	if (c == ' ')
		return 2;
	if (c == '\t' || c == '\v')
		return 1;
	else
		return 0;
}

int	main(int ac, char **av)
{
	int i = 0;
	int	len; 

	while (ac == 2 && av[1][i])
	{
		len = ft_strlen(av[1]);
		if (is_space_or_tab(av[1][i]) >= 1)
		{
			if (i != 0 && i != len -1)
			{
				write(1, " ", 1);
				i++;
			}
			while (is_space_or_tab(av[1][i]) >= 1)
				i++;
		}
		else
		{
			write(1, &av[1][i], 1);
			i++;
		}
	}
	write(1, "\n", 1);
}
