/*
I did not copy the actual subject. But it did go along the line 
"fix the code" ;)
*/

#include <stdio.h>
#include <stdlib.h>

void	*ft_memcopy(void *dest, const void *src, size_t n)
{
	char *d = dest;
	const char *s = src;
	int		i;

	if (!src || !n)
		return (NULL);
	else if (src == dest)
		return (src);
	if (d < s && d + n > s)
		ft_memmove(d, s, n);
	else
	{
		while (--n >= 0)
			d[n] = s[n];
	}
	return d;
}


//ok
void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*d;
	const char	*s;
	int			i;

	d = (char *)dest;
	s = (const char *)src;
	if (!s || !n)
		return (NULL);
	i = -1;
	if (d < s)
	{
		while (++i < n && s[i])
			d[i] = s[i];
	}
	else
	{
		while (n-- >= 0 && s[n])
			d[n] = s[n];
	}
	return (d);
}

//ok
size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

//ok
char	*ft_strchr(char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == c)
			return (s);
		s++;
	}
	return (NULL);
}

int	main(int ac, char **av)
{
	char	*s1 = "Hi";

	s1 = malloc(10);
	char *s2 = s1 + 10;
	s2 = "jin";
	//s1 = "HI";
	printf("before:[%s]\n", s1);
	ft_memcpy(s1, s2, 1);
	printf("after:[%s]\n", s2);
	return (0);
}

/*


int	str_append_mem(char **s1, char *s2, size_t size2)
{
	size_t size1 = ft_strlen(*s1);
	char *tmp = malloc(size2 + size1 + 1);
	if (!tmp)
		return 0;
	ft_memcpy (tmp, *s1, size1);
	ft_memcpy (tmp + size1, s2, size2);
	tmp[size1 + size2] = 0;
	free(*s1);
	*s1 = tmp;
	return 1;
}

int	str_append_str(char **s1, char *s2)
{
	return str_append_mem(s1, s2, ft_strlen(s2));
}


char	*get_next_line(int fd)
{
	static char b[BUFFER_SIZE + 1] = "";
	char *ret = NULL;

	char *tmp = ft_strchr(b, '\n');
	while (!tmp) {
		if (!str_append_str(&ret, b))
			return NULL;
		int read_ret = read(fd, b, BUFFER_SIZE);
		if (read_ret == -1)
			return NULL;
		b[read_ret] = 0;
	}
	if (!str_append_mem(&ret, b, tmp - b + 1))
	{
		free(ret);
		return NULL;
	}
	return ret;
}
*/