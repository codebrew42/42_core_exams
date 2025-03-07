/* all the doubt
1. size_t's lib?


*/

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#define BF_SIZE 1


int		ft_strlen(char *s)
{
	if (!s)
		return (0);
	int len = 0;
	while(s[len])
		len++;
	return (len);
}


/*
@return Null(if needle doesn't exist in hash), pointer (if exist)
*/
char	*ft_memmem(char *big, char *little)
{
	if (!big || !little)
		return (NULL);
	int l_len = ft_strlen(little);
	int	i = 0;
	int j;
	while (big[i])
	{
		j = 0;
		while (big[i+j] && big[i+j] == little[j])
			j++;
		if (j == l_len)
			return (&big[i]);
		i++;
	}
	return (NULL);
}



char	*ft_memmove(char *dest, char *src, int s_len)
{
	if (!dest || !src)
		return (NULL);
	int i;
	if (src < dest && src + s_len < dest)
	{
		i = s_len;
		while (--s_len >= 0)
			dest[i] = src[i];
	}
	else
	{
		i = -1;
		while (++i < s_len)
			dest[i] = src[i];
	}
	dest[s_len] = 0;
	return (dest);
}

/*
@brief	change str using filter to '*', if exactly same filter exist, 
		convert directly str
*/
void	filter_input(char *str, char *filter)
{
	return ;
}

/*
@ read from stdinput, till nth exist
*/
char	*read_input(void)
{
//malloc buff
	char *buff = malloc(BF_SIZE+1);
	if (!buff)
		return (NULL);
	int bytes_read;
	int total = 0;
	char *dest;
	char *temp_dest;

	while (1)
	{
//read and save to buff
		bytes_read = read(0, buff, BF_SIZE);
//if bytes_read <= 0
		if (bytes_read <= 0)
		{
			free(buff);
			if (bytes_read < 0)
				free(dest);
			break ;
		}
//buff[] =0
		buff[bytes_read] = 0;
//copy: dest+total <- bf(len:bytes_read)
//update total & dest[total] = 0
		temp_dest = malloc(total+bytes_read+1);
		if (!temp_dest)
		{
			free(buff);
			free(dest);
			break ;
		}
		if (dest)
			ft_memmove(temp_dest, dest, total);
		ft_memmove(temp_dest+total, buff, bytes_read);
		total += bytes_read;
		temp_dest[total+bytes_read] = 0;
	}
	return (dest); 
}



int	main(int ac, char **av)
{
	char	*input;

	if (ac !=2 || !*av || !av)
		return (1);
//test space
//	printf("little starts from here[%s]\n", ft_memmem("hi my name is jin from seoul!", "jin"));


//code space
	input = read_input();
	if (!input)
		return (0);
//	filter_input(input, av[1]);
		printf("%s", av[1]);

	free(input);
	return (0);
}
