
//bca -> abc acb bac bca cab cba

#include <string.h>
#include <stdio.h>
#include <unistd.h>

void	print_arr(char *s)
{
	int		i = 0;
	while (s[i])
	{
		printf("%c", s[i]);
		i++;
	}
	printf("\n");
}

void	sort_alpha(char *s)
{
	int		i = 0;
	int		j;
	int		len = strlen(s);
	char	tmp;

	while (i < len - 1)
	{
		j = 0;
		while (j < len - i - 1)
		{
			if (s[j] > s[j+1])
			{
				tmp = s[j];
				s[j] = s[j+1];
				s[j+1] = tmp;
			}
			j++;
		}
		i++;
	}
}

void	generate(char *s, int *printed, char *res, int pos)
{
	//normal return = all found
	if (pos == strlen(s))
	{
		write(1, res, pos);
		write(1, "\n", 1);
		return ;
	}
	//looping
	int i = 0;
	while (i < strlen(s))
	{
		if (!printed[i])
		{
			printed[i] = 1;
			res[pos] = s[i]; //pos ; saved
			generate(s, printed, res, pos + 1);
			printed[i] = 0;
		}
		i++;
	}

}

int		main(int ac, char **av)
{
	if (ac != 2 || !*av)
		return (1);
	sort_alpha(av[1]); //ok
	//print_arr(av[1]); //ok
	int len = strlen(av[1]);

	//! : created int printed[len], char res[len + 1] => init *printed, null-term *res;
	int printed[len];
	char res[len + 1];
	int i = -1;
	while (++i < len)
		printed[i] = 0;
	res[len] = 0;
	generate(av[1], printed, res, 0); //abc acb bac bca ...
	return (0);
}