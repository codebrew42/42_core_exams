#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define BF_SIZE 1


char	*ft_memmove(char *dst, char *src, int src_len)
{
	if (!dst)
		return (NULL);
	if (!src || src_len == 0)
		return (NULL);

	int cp_src_len = src_len;
	if (src + src_len > dst)
	{
		while (src[--src_len])
			dst[src_len] = src[src_len];
	}
	else
	{
		int i = -1;
		while(++i < src_len)
			dst[i] = src[i];
	}
	dst[src_len] = 0;
	return (dst);
}


char	*join_free(char *s, char *b)
{
	int	line_len = strlen(b);
	if(s)
		line_len += strlen(s);
	char	*dest = malloc(line_len+1);
	if (!dest)
		return (NULL);
	if (s)
		ft_memmove(dest, s, strlen(s));
	ft_memmove(dest + strlen(s), b, strlen(b));
	dest[line_len] = 0;
	return (dest);
}

char	*ft_strchr(char *s, char c)
{
	while (*s != c && *s)
	{
		s++;
	}
	return (s);
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
	while (*s != newline_pos)
		(*s)++;
	(*s)++;
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
	if (ft_strchr(stash, '\n'))
		return (extract_line(&stash));

	//loop: if (stash doesn't contain \n) {read(fd, buff, BF_SIZE)}
	char *buff = malloc(BF_SIZE + 1);
	if (!buff)
		return (NULL);

	while (!ft_strchr(stash, '\n'))
	{
		bytes_read = read(fd, buff, BF_SIZE);
		//err: if(bytes_read < 0)
		if (bytes_read < 0)
		{
			free(buff);
			free(stash);
			return (NULL);
		}
		//bhv: join_free(stash, buff)
		else if (bytes_read > 0)
		{
			buff[bytes_read] = 0;
			stash = join_free(stash, buff);
		}
		//normal ret: if (bytes_read == 0 || stash has '\n') {break}
		else if (bytes_read == 0 || ft_strchr(stash, '\n'))
		{
			free(buff);
			break;
		}
	}

	//if (bytes_read=0 & !stash) {ret NULL}
	if (!bytes_read && !stash)
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
		printf("%s", line);
		if (!line)
			break ;
		free(line);
	}
	return (0);
}
