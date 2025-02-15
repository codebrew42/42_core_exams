/**
 * 
 *    echo "ababc" | ./filter abc     -> res : ab***
 * 
 */
#define BUFF_SIZE 1024
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

void	handle_error(int i, char *s)
{
	if (i == 0)
	{
		fprintf(stderr, "ERROR: malloc failed");
		exit(1);
	}
	else if (i == 1)
	{
		perror("read failed");
		free(s);
		exit(1);
	}

}

void	filter_str(char *filter, char *s)
{
	char	*p;
	int		f_len;

	p = memmem(s, strlen(s), filter, strlen(filter));
	if (!p)
		return ;
	f_len = strlen(filter);
	while (--f_len >= 0)
	{
		p[f_len] = '*';
	}
}

char	*read_stdin(void)
{
	char	*buff;
	int		bytes_read;
	int		total;
	char	*final_dest = NULL;

	buff = malloc(BUFF_SIZE + 1);
	if (!buff)
		handle_error(0, NULL);
	total = 0;
	while (1)
	{
		bytes_read = read(0, buff, BUFF_SIZE);
		if (bytes_read < 0)
			handle_error(1, buff);
		else if (!bytes_read)
			break ;

		buff[bytes_read] = '\0';
		final_dest = realloc(final_dest, total + bytes_read + 1); 
		if (!final_dest)
			handle_error(1, buff);
		memmove(final_dest + total, buff, bytes_read);
		total += bytes_read;
	}
	if (final_dest)
		final_dest[total] = '\0';
	free(buff);
	return (final_dest);
}

int	main(int ac, char **av)
{
	char *dest;

	if (ac != 2)
		return (1);
	dest = read_stdin();
	filter_str(av[1], dest);
	if (dest)
	{
		printf("%s", dest);
		free(dest);
	}
	return (0);
}
