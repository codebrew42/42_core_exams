#include <unistd.h>

int	ft_strlen(char *str)
{
	int	i = 0;
	while(str[i])
		i++;
	return i;
}

int	is_space_or_tab(char c)
{
	if (c == ' ' || c == '\t' || c == '\v')
		return 1;
	return 0;
}

int	idx_end_of_last_word(char *str)
{
	int	str_len = ft_strlen(str);
	int	i;	

	i = str_len - 1;
	while(str[i] && is_space_or_tab(str[i]) == 1) 
		i--;
	/* "_a__" str[0] = str[2] = str[3] = ' '
	   str_len = 4
	   start_i = 3
	   res_i   = 1

	    "__abc__" s[0][1][5][6] = ' '
	end_idx = 4
	start_idx = 

	*/
	return i;
}

int	idx_start_of_last_word(char *str, int idx)
{
	if (idx == 0)
		return 0;
	while (str[idx] && is_space_or_tab(str[idx]) == 0)
		idx--;
	return idx;
}

int	main(int ac, char **av)
{
	if (ac != 2)
	{
		write(1, "\n", 1);
		return 1;
	}

	int	end_idx = idx_end_of_last_word(av[1]);
	int	start_idx = idx_start_of_last_word(av[1], end_idx);
	
	if (end_idx == start_idx)
	{
		write(1, "\n", 1);
		return 1;
	}
	start_idx++;
	while (start_idx <= end_idx)
		write(1, &av[1][start_idx++], 1);
	write(1, "\n", 1);
	return 0;
}
