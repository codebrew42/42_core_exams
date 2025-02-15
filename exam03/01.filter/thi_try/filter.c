#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

#define BUFF_SIZE 1024

void	filter(char *s, char *f)
{
	char	*p;
	int		f_len;

	p = memmem(s, strlen(s), f, strlen(f));
	if (!p || !s || !f)
	{
		return ;
	}
	f_len = strlen(f);
	while(--f_len >= 0)
	{
		p[f_len] = '*';
	}
}

char	*read_stdin(void)
{
	int		size_read;
	int		total;
	char	*buff;
	char	*dest;

	buff = malloc(BUFF_SIZE);
	if (!buff)
	{
		perror("malloc failed");
		exit(1);
	}
	dest = NULL;
	total = 0;
	while (1)
	{
		size_read = read(0, buff, BUFF_SIZE);
		if (size_read < 0)
		{
			perror("read failed");
			free(buff);
			free(dest);
			exit(1);
		}
		else if (size_read == 0)
			break;
		dest = realloc(dest, total + size_read + 1);
		if (!dest)
		{
			perror("realloc failed");
			free(buff);
			exit(1);
		}
		memmove(dest + total, buff, size_read);
		total += size_read;
	}
	if (dest)
		dest[total] = '\0';
	free(buff);
	return (dest);
}

int	main(int ac, char **av)
{
	char	*res;

	if (ac != 2)
	{
		return (1);
	}
	res = read_stdin();
	filter(res, av[1]);
	write(1, res, strlen(res));
}
