
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "gnl.h"

size_t	ft_strlen(char *s)
{
	size_t ret = 0;
	while (s[ret])
	{
		ret++;
	}
	return (ret);
}

/** fixed **/
char	*ft_strchr(char *s, int c)
{
	while (*s)
	{
		if (*s == c)
		{
			//printf("*s[%c] == c[%c]\n", *s, c);
			return (s);
		}
		s++;
	}
	return (NULL);
}

/** fixed */
void	*ft_memcpy(char *dest, char *src, size_t n)
{
	size_t i = 0;

	while (i < n)
	{
		dest[i] = src[i];
		i++;
	}
	dest[n] = '\0';
	return dest;
}

/* fixed */
void	*ft_memmove (void *dest, const void *src, size_t n)
{
	unsigned char *d = (unsigned char *)dest;
	const unsigned char *s = (const unsigned char *)src;
	if (!dest || !src)
		return (NULL);
	//case 1 : dest  - - - src
	/* ft_memmove(s, s + 2, 5) - overwriting
	 *      s s s s s
	 * [A B C D E F G]
	 *  d d d
	 * 
	 * ft_memmove(d, d + 3, 3)
	 * [A B C D E F G]
	 * 
	 * res: [D E F D E F G]
	 */
	if (d < s)
	{
		d += n;
		s += n;
		while (n-- > 0 && *s)
			*d-- = *s--;
	}
	else //case 2 : src - - - dest
	{
		while (n-- > 0 && *s)
			*d++ = *s++;

	}	
	return d;
}

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

void	handle_error(int flag)
{
	if (flag == 0)
	{
		perror("Read failed");
		exit(1);
	}
	else if (flag == 1)
	{
		perror("malloc failed");
		exit(1);
	}
	else if (flag == 2)
	{
		perror("Error opening file");
		exit(1);
	}
}

void	update_stash(char **s)
{
	char *p = ft_strchr((char *)s, '\n');
	if (!p)
		*s = NULL;
	else
		*s = p + 1;
}

char	*get_single_line(const char *s)
{
	char *p = ft_strchr((char *)s, '\n');
	int len = p - s;
	char *dst;
	
	dst = malloc(len + 1);
	if (!dst)
		handle_error(1);
	ft_memmove(dst, s, len);
	dst[len] = '\0';
	return (dst);
}

char	*get_next_line(int fd)
{
	static char		*dest = NULL;
	char			*buff = NULL;
	char			*final_dest;
	int				bytes_read;
	int				prev_len;
//	char *tmp = ft_strchr(b, '\n');
	prev_len = 0;
	buff = malloc (BUFFER_SIZE + 1);
	if (!buff)
		handle_error(1);
	while (1)
	{
		bytes_read = read(fd, buff, BUFFER_SIZE);
		if (bytes_read == -1)
			handle_error(0);
		if (!bytes_read)
			break ;
		dest = realloc(dest, prev_len + bytes_read);
		if (!dest)
			handle_error(1);
		memmove(dest + prev_len, buff, bytes_read);
		prev_len += bytes_read;
		char *p = ft_strchr(dest, '\n');
		if (!p)
			break ;
		else
		{
			dest = get_single_line(dest);
			//update_stash(&dest);
			//printf("STASH: %s", dest);
		}
	}
	return (dest);
}

int main(int ac, char **av)
{
	//test ft_memcpy
	char	*dst;
	char	*src;

	dst = malloc(3);
	if (!dst)
	{
		fprintf(stderr, "ERROR: malloc failed");
		exit (1);
	}
	dst = ft_memcpy(dst, "hi", 2);
	//printf("%s", dst);

	char *p = ft_strchr("hi jin", 'j');
	printf("%s", p);
	p = ft_strchr("hi jin", 'q');
	printf("%s\n", p);
	printf("len: %zu\n", ft_strlen("hi jin"));

	char *str = "ABCDE";
	char *new_s = str+1;
	new_s = malloc(10);
	if (!new_s)
	{
		fprintf(stderr, "ERROR: malloc failed");
		exit (1);
	}
	printf("new_s: %s\n", new_s);

	ft_memmove(new_s, str, 3);
	new_s[3] = '\0';
	printf("str: %s\n", str);
	printf("new_s: %s\n", new_s);
	printf(" * * * * * * testing func finished * * * * * *\n");
	if (ac != 2)
	{
		printf("argument is not given\n");
		exit (1);
	}
	int fd = open(av[1], O_RDONLY);
	if (fd == -1)
		handle_error(2);
	char *dst2 = get_next_line(fd);
	printf("%s", dst2);
	close(fd);
		return 0;
}