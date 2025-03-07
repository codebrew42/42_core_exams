

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#define BF_SIZE 1

char	*ft_memmove(char *dest, char *src, int len);

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
	while (*s && *s != c) //check: *s
		s++;
	if (*s == c)
		return (s);
	return (NULL);
}

char	*ft_strdup(char *str)
{
	if (!str)
		return (NULL);
	int		str_len = ft_strlen(str);
	char *dest = malloc(str_len + 1);
	if (!dest)
		return (NULL);
	dest = ft_memmove(dest, str, str_len);
	if (!dest)
	{
		free(dest);
		return (NULL);
	}
	dest[str_len] = '\0';
	return (dest);
}

char	*ft_memmove(char *dest, char *src, int len)
{
	if (!dest)
		return (NULL);
	if (!src || !len)
		return (dest);
	int	i = -1;
	if (src < dest && src + len > dest)
	{
		i = len;
		while (--len >= 0)
			dest[i] = src[i];
	}
	else
	{
		while (++i < len)
			dest[i] = src[i];
	}
	dest[len] = '\0';
	return (dest);
}

char	*extract_line(char **stash)
{
	if (!stash || !*stash)
	{
		if (*stash) //check
			free(*stash);
		return (NULL);
	}
	char	*newline_pos = ft_strchr(*stash, '\n');
	//extract first
	int		line_len;
	line_len = ft_strlen(*stash);
	if (newline_pos)
		line_len = newline_pos + 1 - *stash;
	char	*dest = malloc(line_len + 1);
	if (!dest)
		return (NULL);
	dest = ft_memmove(dest, *stash, line_len);
	if (!dest)
	{
		free(dest);
		return (NULL);
	}
	dest[line_len]= '\0';

	//update stash
	if (!newline_pos)
	{
		free(*stash);
		*stash = NULL;
	}
	else
	{
		newline_pos++;
		char	*temp = ft_strdup(newline_pos);
		free(*stash);
		*stash = temp;
	}
	return (dest);
}

char	*join_free(char *s1, char *s2)
{
	char	*dest;

	if (!s1)
	{
		dest = ft_strdup(s2);
		if (!dest)
			return (NULL);
		return (dest);
	}
	int		len1 = ft_strlen(s1);
	int		len2 = ft_strlen(s2);
	dest = malloc(len1+len2+1);
	if (!dest)
		return (NULL);
	dest = ft_memmove(dest, s1, len1);
	free(s1);
	ft_memmove(dest + len1, s2, len2);
	dest[len1+len2] = '\0';
	return (dest);
}

char	*gnl(int fd)
{
	if (fd < 0 || BF_SIZE <= 0)
		return (NULL);
	static char		*stash = NULL;
	if (stash && ft_strchr(stash, '\n'))
		return (extract_line(&stash));
	int		bytes_read;
	while (ft_strchr(stash, '\n') == NULL)
	{
		char	*buff = malloc(BF_SIZE + 1);
		if (!buff)
			return (NULL);
		bytes_read = read(fd, buff, BF_SIZE);
		if (bytes_read <= 0)
		{
			free(buff);
			if (bytes_read < 0)
				free(stash);
			break;
		}
		buff[bytes_read] = '\0';
		stash = join_free(stash, buff);
		free(buff);
	}
	if (!stash || !*stash)
	{
		if (stash && !*stash)
		{
			free(stash);
			stash = NULL;
		}
		return (NULL);
	}
	return (extract_line(&stash));
}

int	main(int ac, char **av)
{
	if (ac != 2 || !av[1])
		return (1);
	int fd = open(av[1], O_RDONLY);
	char	*line;
	while ((line = gnl(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	return (0);
}