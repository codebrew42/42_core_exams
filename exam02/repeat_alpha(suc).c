#include <unistd.h>

int	alpha_idx(char c)
{
	int		res;

	if (c >= 'A' && c <= 'Z')
		res = (int)c - 'A' + 1;
	else if (c >= 'a' && c <= 'z')
		res = (int)c - 'a' + 1;
	else
		return (1);
	return (res);
}

int	main(int ac, char **av)
{
	int i;
	int	j;

	i = 0;
	while (ac == 2 && av[1][i])
	{
		j = -1;
		while (++j < alpha_idx(av[1][i]))
			write(1, &av[1][i], 1);
		i++;
	}
	write(1, "\n", 1);
}
