#include "filter.h"
#define BUFFER_SIZE 1024

int	ft_strlen(char *s)
{
	int i = 0;

	while (s[i])
		i++;
	return (i);
}

int	check_replace(char *src, char *replace)
{
	int i = 0;

	while (src[i] && replace[i])
	{
		if (src[i] != replace[i])
			return (0);
		i++;
	}
	return (1);
}

void replace_src(char *src, int replace_len)
{
	int i = 0;

	while(i < replace_len)
	{
		src[i] = '*';
		i++;
	}
}
void filtering(char *src, char *replace, int src_len)
{
	int	replace_len = ft_strlen(replace);
	int i = 0;
	int j = 0;

	while (src[i])
	{
		if (check_replace(&src[i], replace))
		{
			replace_src(&src[i], replace_len);
			i += replace_len;
		}
		else
			i++;
	}
}

int main(int ac, char **av)
{
	char		buffer[BUFFER_SIZE + 1];
	ssize_t		bytes_read;
	int			len;

	if (ac != 2)
		return(1);
	while (1)
	{
		bytes_read = read(0, buffer, BUFFER_SIZE);
		if (bytes_read > 0)
		{
			filtering(buffer, av[1], bytes_read);
			write(1, buffer, bytes_read);
		}
		else if (bytes_read == 0)
			break;
		else
		{
			write(2, "Error: ", 7);
			perror("");
			return (1);
		}
	}
	return (0);
}