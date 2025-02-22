#include <limits.h>
#include <stdio.h>

int	is_power_of_2(unsigned int n)
{
	if (n == 0)
		return 0;
	if (n % 2 == 0 || n == 1)
		return 1;
	else
		return 0;
}

/*
int	main()
{

	printf("%d", is_power_of_2(-1));
	printf("%d", is_power_of_2(0));
	printf("%d", is_power_of_2(1));
	printf("%d", is_power_of_2(2));
	printf("%d", is_power_of_2(3));
	printf("%d", is_power_of_2(UINT_MAX));
}*/
