#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define BF_SIZE 1


char	*ft_memmove(char *dst, char *src, int len);


int	ft_strlen(char *s)
{
	int len = 0;
	if (!s) return (0);
	while (s[len])
		len++;
	return (len);
}

char	*join_free(char *s, char *b)
{
	int s_len = s ? ft_strlen(s) : 0; // Safe NULL check
	int b_len = b ? ft_strlen(b) : 0;
	char	*dest = malloc(s_len + b_len + 1);
	
	if (!dest)
		return (NULL);
	if (s)
	{
		ft_memmove(dest, s, s_len);
		free(s); // Free old stash
	}
	if (b)
		ft_memmove(dest + s_len, b, b_len);
	dest[s_len + b_len] = 0;
	return (dest);
}



char	*ft_memmove(char *dst, char *src, int len)
{
	int	i;
	if (len <= 0 || !src)
		return (dst);
	if (src < dst && dst < src + len)
	{
		i = len;
		while (--i >= 0)
			dst[i] = src[i];
	}
	else
	{
		i = -1;
		while (++i < len)
			dst[i] = src[i];
	}
	dst[len] = 0;
	return (dst);
}

char	*ft_strchr(char *s, char c)
{
	if (!s)
		return (NULL);
	while (*s != c && *s)
		s++;
	if (*s == c)
		return (s);
	return (NULL);
}


char	*extract_line(char **s)
{
	int line_len;
	if (!s || !*s)
		return (NULL);
	char	*newline_pos = ft_strchr(*s, '\n');

	//copy line
	if (!newline_pos)
		line_len = strlen(*s);
	else
		line_len = newline_pos - *s + 1;
	char *dest = malloc(line_len + 1);
	if (!dest)
		return (NULL);
	ft_memmove(dest, *s, line_len);
	dest[line_len] = 0; 

	//update stash
	if (!newline_pos)
	{
		free(*s);
		*s = NULL;
	}
	else
	{
		newline_pos++;
		line_len = ft_strlen(newline_pos);
		char *temp = malloc(line_len + 1);
		if (!temp)
			return (NULL);
		ft_memmove(temp, newline_pos, line_len);
		temp[line_len] = 0;
		*s = temp;
	}
	return (dest);
}

char	*gnl(int fd)
{
	//er_ret: fd<0, buff_size=0
	if (fd < 0 || BF_SIZE <= 0)
		return (NULL);

	//if (stash contains \n) {ret (extract_line($stash)}
	static char	*stash;
	int		bytes_read;
	char		*buff;
	if (stash && ft_strchr(stash, '\n'))
		return (extract_line(&stash));

	//loop: if (stash doesn't contain \n) {read(fd, buff, BF_SIZE)}
	while (!ft_strchr(stash, '\n'))
	{
		if (!(buff = malloc(BF_SIZE + 1)))
			return (NULL);
		bytes_read = read(fd, buff, BF_SIZE);
		if (bytes_read <= 0)
		{
			free(buff);
			if (bytes_read < 0)
				free(stash);
			break ;
		}
		buff[bytes_read] = 0;
		stash = join_free(stash, buff);
		free(buff); // Critical fix: Free temp buffer
	}
	if (!stash || !*stash)
		return (NULL);
	return (extract_line(&stash));
}

int	main(int ac, char **av)
{
	//early ret
	if (ac != 2 || !av || !*av)
		return (1);


	//open(av[1], O_RDONLY)
	int fd = open(av[1], O_RDONLY);
	if (fd < 0)
	{
		fprintf(stderr, "open failed");
		exit (1);
	}
	
	//if (not NULL) {loop: read}
	char *line;
	while(1)
	{
		line = gnl(fd);
		if (!line)
			break ;
		printf("%s", line);
		free(line);
	}
	close(fd); //!
	return (0);
}
