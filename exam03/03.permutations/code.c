/*plan

0.check validaty
1.re-organize av[1] in alpha-order
2.malloc new string use idx
3.using index, print it
	how)01 / 10      (each sum 1)
		= 2 cases

	how)012 / 021    (each sum 1+2)
		102 / 120
		201 / 210
		= 3*2 cases

	how)0123 / 0132   (each sum 1+2+3)
		0213 / 0231
		0312 / 0321

		1023 / 1032
		1203 / 1230
		1302 / 1320
		= 4*3*2 cases

# to think
-mixed : upper+lower?
-> just think, there's only lowercase

*/
#include <stdio.h>
#include <unistd.h>

int	ft_strlen(char *s)
{
	int i = 0;
	while (s[i])
		i++;
	return (i);
}

int all_used(int *arr, int len)
{
	int i = 0;
	while (i <= len)
	{
		if (arr[i] == 0)
			return (0);
		i++;
	}
	return (1);
}

void display_permutation(char *sorted, int *used, char *res, int len)
{
	if (ft_strlen(res) == len)
	{
		puts(res);
		return ;
	}
	int i = 0;
	while (i < len)
	{
		if (!used[i])
		{
			//use sorted[i] and mark it as 1(used)
			res[ft_strlen(res)] = sorted[i];
			used[i] = 1;
			res[ft_strlen(res) + 1] = '\0';

			display_permutation(sorted, used, res, len);
			//unmark last char
			used[i] = 0;
			//rm  last char from res
			res[ft_strlen(res) - 1] = '\0';
		}
		i++;
	}
}

void sort_str(char *s)
{
	int i = 0;
	int j;
	char temp;

	while (s[i])
	{
		j = 0;
		while (s[j+1])
		{
			if (s[j] > s[j+1])
			{
				temp = s[j];
				s[j] = s[j+1];
				s[j+1] = temp;
			}
			j++;
		}
		i++;
	}
}

void init_arr(int *int_arr, char *s, int len)
{
	int i = 0;
	while (i < len)
	{
		int_arr[i] = 0;
		i++;
	}
	s[0] = '\0';
}

int	main(int ac, char **av)
{
	if (ac != 2 || av[1][0] == '\0')
		return (1);
	int len = ft_strlen(av[1]);
	sort_str(av[1]);
	// printf("sorted: %s", av[1]);

	int used[len];
	char res[len+1];
	init_arr(used, res, len);
	display_permutation(av[1], used, res, len);
}