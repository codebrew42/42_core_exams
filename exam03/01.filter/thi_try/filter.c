#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#define BUFF_SIZE 1024

void	*ft_memmem(const void *haystack, size_t hs_len, const void *needle, size_t n_len)
{
	size_t			i;
	const char		*h = haystack;
	const char		*n = needle;

	if (!haystack || !needle || n_len == 0 || hs_len < n_len)
		return (NULL);
	i = 0;
	while (i <= hs_len - n_len)
	{
		if (h[i] == n[0] && !__builtin_memcmp(h + i, n, n_len))
			return ((void *)(h + i));
		i++;
	}
	return (NULL);
}

void	filter(char *s, char *f)
{
	size_t	s_len;
	size_t	f_len;
	char	*current;
	char	*match;

	if (!s || !f || !*s || !*f)
		return ;
	s_len = strlen(s);
	f_len = strlen(f);
	if (f_len == 0 || f_len > s_len)
		return ;
	current = s;
	while ((match = ft_memmem(current, s_len - (current - s), f, f_len)))
	{
		for (size_t i = 0; i < f_len; i++)
			match[i] = '*';
		current = match + f_len;
	}
}

char	*read_stdin(void)
{
	char	buff[BUFF_SIZE + 1];
	char	*dest;
	ssize_t	bytes_read;
	size_t	total;

	dest = NULL;
	total = 0;
	while ((bytes_read = read(0, buff, BUFF_SIZE)) > 0)
	{
		buff[bytes_read] = '\0';
		char *new_dest = malloc(total + bytes_read + 1);
		if (!new_dest)
		{
			free(dest);
			return (NULL);
		}
		if (dest)
			__builtin_memcpy(new_dest, dest, total);
		__builtin_memcpy(new_dest + total, buff, bytes_read);
		free(dest);
		dest = new_dest;
		total += bytes_read;
		dest[total] = '\0';
	}
	return (dest);
}

int	main(int ac, char **av)
{
	char	*res;

	if (ac != 2)
		return (1);
	res = read_stdin();
	if (!res)
		return (1);
	filter(res, av[1]);
	write(1, res, strlen(res));
	free(res);
	return (0);
}