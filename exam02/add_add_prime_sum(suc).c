#include <limits.h>
#include <unistd.h>
#include <stdio.h>

int	is_pos_nbr(char *str)
{
	if (!str)
		return (-1);
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		str++;
	}
	return (1);
}

int	pos_nbr_to_int(char *str)
{
	int	res = 0;
	
	while (*str)
	{
		res = res * 10 + (*str - '0');
		str++;
	}
	return (res);
}

char	*ft_itoa(int pos_nbr)
{
	char		res[12];
	int		i = 11;
	unsigned int	big_nbr;

	big_nbr = (unsigned int)pos_nbr;
	res[i--] = '\0'; 
	while (big_nbr >= 10)
	{
		res[i--] = pos_nbr % 10 + '0';
		pos_nbr /= 10;
	}
	res[i] = big_nbr + '0';
	return (res[i+1]);
}


int	main(int ac, char **av)
{
	int	nbr = 0;
	int	i = 0;
	int 	res = 0;

	if (ac != 2 || is_pos_nbr(av[1]) != 1)
	{
		write(1, &nbr, 1);
		write(1, "\n", 1);
		return (1);
	}
	//printf("%d\n", INT_MAX);
	//printf("%d\n", pos_nbr_to_int("21474"));

	nbr = pos_nbr_to_int(av[1]);
	if (nbr >= 1 && nbr <= 3)
	{
		write(1, &nbr, 1);
		write(1, "\n", 1);
		return (1);
	}
	while (i <= nbr / 2)
	{
		i = 2;	
		if (nbr % i == 0)	
			res += i;
		i++;
	}
	write(1, &res, 5);
	write(1, "\n", 1);
}
