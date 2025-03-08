#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#define BF_SIZE 1

int		ft_strlen(char *s);

int		ft_strlen(char *s)
{
	if (!s)
		return (0);
	int len = 0;
	while(s[len])
		len++;
	return (len);
}

char	*ft_strchr(char *s, char c)
{
	if (!s)
		return (NULL);
	while (*s && *s != c)
		s++;
	if (*s == c)
		return (s);
	return (NULL);
}

char	*ft_memmove(char *dest, char *src, int src_len)
{
	if (!dest)
		return (NULL);
	if (!src || !src_len)
		return (dest);
	int		i = -1;
	if (src < dest && src + src_len > dest)
	{
		i = src_len;
		while(--i >= 0)
			dest[i] = src[i];
	}
	else
	{
		while(++i < src_len)
			dest[i] = src[i];
	}
	dest[src_len] = '\0';
	return (dest);
}

char	*extract_line(char **s)
{
	if (!s || !*s)
	{
		// Removed incorrect free(s)
		return (NULL);
	}
	char	*newline_pos = ft_strchr(*s, '\n');
	int		line_len;
	line_len = ft_strlen(*s);
	if (newline_pos)
		line_len = newline_pos + 1 - *s;
	char	*line = malloc(line_len+1);
	if (!line)
	{
		return (NULL);
	}
	ft_memmove(line, *s, line_len);
	line[line_len] = '\0';
	if (!newline_pos)
	{
		free(*s);
		*s = NULL;
	}
	else //check! always malloc here
	{
		char	*new_stash = malloc(line_len + 1);
		new_stash = strdup(newline_pos + 1);
		free(*s);
		*s = new_stash;
	}
	return (line);
}

char	*join_free_old_stash(char *stash, char *buff)
{
	if (!stash && !buff)
		return (NULL);
	int	stash_len = ft_strlen(stash);
	int buff_len = ft_strlen(buff);
	char	*dest = malloc(stash_len + buff_len + 1);
	if (!dest)
	{
		if (stash)
			free(stash);
		return (NULL);
	}
	if(stash)
	{
		ft_memmove(dest, stash, stash_len);
		free(stash);
	}
	ft_memmove(dest+stash_len, buff, buff_len);
	dest[stash_len + buff_len] = '\0';
	return (dest);
}

char	*gnl(int fd)
{
	if (fd < 0 || BF_SIZE <= 0)
		return (NULL);
	static char		*stash = NULL;
	if (stash && ft_strchr(stash, '\n'))
		return (extract_line(&stash));
	char			*buff;
	int				bytes_read;
	while (stash == NULL || ft_strchr(stash, '\n') == NULL)
	{
		buff = malloc(BF_SIZE + 1);
		if (!buff)
		{
			free(stash);
			return (NULL);
		}
		bytes_read = read(fd, buff, BF_SIZE);
		if (bytes_read <= 0)
		{
			free(buff);
			if (bytes_read < 0)
				free(stash);
			break;
		}
		buff[bytes_read] = '\0';
		char *new_stash = join_free_old_stash(stash, buff);
		free(buff);
		stash = new_stash;
	}
	if (!stash || !*stash)
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	return (extract_line(&stash));
}

int	main(int ac, char **av)
{
	if (ac != 2 || !av[1])
		return (1);
	int fd = open(av[1], O_RDONLY);
	char *line;
	while ((line = gnl(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
}
