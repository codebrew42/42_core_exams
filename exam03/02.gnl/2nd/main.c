/*
I did not copy the actual subject. But it did go along the line 
"fix the code" ;)
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#define BF_SIZE 1024

int		handle_error(int i, char *s1, char *s2);
void	*ft_memcopy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
size_t	ft_strlen(char *s);
char	*ft_strchr(char *s, int c);
int		str_append_mem(char **s1, char *s2, size_t size2);

int	handle_error(int i, char *s1, char *s2)
{
	if (i == 0)
	{
		if (s1)
			free(s1);
		if (s2)
			free(s2);
		fprintf(stderr, "malloc failed");
		return (1);
	}
	else if (i == 1)
	{
		perror("read failed\n");
		return (1);
	}
	else if (i == 2)
	{
		printf("Error: str_append_mem failed\n");
		return (1);
	}
	return (0);
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

//append s2 to s1 (concatenate)
//fixed
int	str_append_mem(char **s1, char *s2, size_t size2)
{
	size_t	size1;
	char	*tmp;

	size1 = ft_strlen(*s1);
	tmp = malloc(size2 + size1 + 1);
	if (!tmp)
		return (handle_error(0, NULL, NULL));
	if (*s1)
		ft_memcopy(tmp, *s1, size1);
	if (*s2)
		ft_memcopy(tmp + size1, s2, size2);
	tmp[size1 + size2] = '\0';
	*s1 = tmp;
	return (0);
}

char	*get_next_line(int fd)
{
	char			tmp;
	char			*buff;
	static char		*ret;
	int				new_bytes_read;
	int				total_read;

//	tmp = ft_strchr(b, '\n');
	buff = malloc(BF_SIZE + 1);
	if (!buff)
	{
		handle_error(0, buff, NULL);
		return (NULL);
	}
		total_read = 0;
	while (!tmp)
	{
		new_bytes_read = read(fd, buff, BF_SIZE);
		if (new_bytes_read == -1)
		{
			handle_error(1, buff, NULL);
			return (NULL);
		}
		else if (!new_bytes_read)
			break ;
		ret = realloc(ret, total_read + new_bytes_read + 1);
		if (!ret)
		{
			handle_error(0, buff, NULL);
			return (NULL);
		}
		if (str_append_mem(ret + total_read, buff, new_bytes_read))
			exit (handle_error(2, buff, ret));
		total_read += new_bytes_read;
		if (ft_strchr(ret, '\n'))
		{
			break ;
			//update stash(ret should be next position of \n)
			//break;
		}
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
	}
	printf("* * *debugging point* * *\n");
	return (0);
}

/*

int	main()
{
	//check str_append_mem
	char	*s1;
	char	*s2;
	int		res;

	s1 = "hi ";
	s2 = "jieun ";
	res = str_append_mem(&s1, s2, 6);
	if (res)
		printf("str_append_mem: failed\n");
	else
		printf("res : [%s]\n", s1);
	free(s1);
}

int	str_append_str(char **s1, char *s2)
{
	return str_append_mem(s1, s2, ft_strlen(s2));
}

*/