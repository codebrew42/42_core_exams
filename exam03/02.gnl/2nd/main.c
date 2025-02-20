/*
I did not copy the actual subject. But it did go along the line 
"fix the code" ;)
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#define BF_SIZE 1024

char	*handle_error2(int i, char *s1, char *s2);
int		handle_error(int i, char *s1, char *s2);
void	*ft_memcopy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
size_t	ft_strlen(char *s);
char	*ft_strchr(char *s, int c);
int		str_append_mem(char **s1, char *s2, size_t size2);

char	*handle_error2(int i, char *s1, char *s2)
{
	handle_error(i, s1, s2);
	return (NULL);
}


int	handle_error(int i, char *s1, char *s2)
{
	if (i == 0)
	{
		if (s1)
			free(s1);
		if (s2)
			free(s2);
		fprintf(stderr, "malloc failed");
	}
	else if (i == 1)
	{
		perror("read failed\n");
	}
	else if (i == 2)
	{
		printf("Error: str_append_mem failed\n");
	}
	return (1);
}
//ok
void	*ft_memcopy(void *dest, const void *src, size_t n)
{
	char		*d;
	const char	*s;

	d = dest;
	s = src;
	if (!src || !n)
		return (NULL);
	if (s == d)
		return (d);
	if (d < s && d + n > s)
		ft_memmove(dest, src, n);
	else
	{
		while (n > 0)
		{
			n--;
			d[n] = s[n];
		}
	}
	return (d);
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

char	*update_stash(char *s)
{
	while (!ft_strchr(s, '\n') && s)
		s++;
	return (s);
}

char	*get_next_line(int fd)
{
	char			*buff;
	static char		*stash;
	char			*ret = NULL;
	int				new_bytes_read;
	int				total_read;

//	tmp = ft_strchr(b, '\n');
	buff = malloc(BF_SIZE + 1);
	if (!buff)
		return (handle_error2(0, buff, NULL));
	total_read = 0;
	while (1)
	{
		new_bytes_read = read(fd, buff, BF_SIZE);
		if (new_bytes_read == -1)
			return (handle_error2(1, buff, NULL));
		else if (!new_bytes_read)
			break ;
		buff[new_bytes_read] = '\0';
		ret = realloc(ret, total_read + new_bytes_read + 1);
		if (!ret || !ft_memmove(ret + total_read, buff, new_bytes_read))
			return (handle_error2(0, buff, NULL));
		total_read += new_bytes_read;
		stash = update_stash(ret);
		if (ft_strchr(ret, '\n'))
			break ;
	}
	buff[total_read] = '\0';
	return (ret);
}

int	main(int ac, char **av)
{
	int		fd;
	char	*line;

	if (ac != 2)
	{
		printf("argument is not given\n");
		return (1);
	}
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
	{
		perror("open failed\n");
		exit (1);
	}
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		printf("%s", line);
	}
	return (0);
}
