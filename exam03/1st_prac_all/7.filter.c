#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#define BF_SIZE 1

char	*ft_strchr(char *s, char c);
int		ft_strlen(char *s);
char	*ft_memmove(char *dest, char *src, int len);
char	*ft_strdup(char *s);
char	*extract_line(char **stash);
char	*join_free(char *stash, char *buff);

char	*ft_strchr(char *s, char c)
{
	if (!s)
		return (NULL);
	while (s && *s != c)
		s++;
	if (s && *s == c)
		return (s);
	return (NULL);
}

int	ft_strlen(char *s)
{
	if (!s)
		return (0);
	int len = 0;
	while(s && s[len])
		len++;
	return (len);
}

char	*ft_memmove(char *dest, char *src, int len)
{
	if (!src || !len)
		return (dest);
	int	i = -1;
	if (src < dest && src + len > dest)
	{
		i = len;
		while (--i >= 0)
			dest[i] = src[i];
	}
	else
	{
		while(++i < len)
			dest[i] = src[i];
	}
	dest[len] = '\0';
	return (dest);
}

char	*ft_strdup(char *s)
{
	if (!s)
		return (NULL);
	int s_len = ft_strlen(s);
	char *dest = malloc(s_len + 1);
	if (!dest)
		return (NULL);
	dest = ft_memmove(dest, s, s_len);
	dest[s_len] = '\0';
	return (dest);
}

char	*extract_line(char **stash)
{
	//early return
	if (!stash || !*stash)
		return (NULL);
	char	*newline_pos = ft_strchr(*stash, '\n');
	int		dest_len;
	char	*dest;
	//extract line 
	if (!newline_pos)
		dest_len = ft_strlen(*stash);
	else
		dest_len = newline_pos + 1 - *stash;
	dest = malloc(dest_len + 1);
	if (!dest)
		return (NULL);
	dest = ft_memmove(dest, *stash, dest_len);
	dest[dest_len] = '\0';
	//and then update stash (mem needed)
	if (!newline_pos)
	{
		free(*stash);
		*stash = NULL;
	}
	else
	{
		char *temp = ft_strdup(newline_pos + 1); //!
		free(*stash);
		if (!temp)
			return (NULL);
		*stash = temp;
	}
	//ret
	return (dest);
}

char	*join_free(char *stash, char *buff)
{
	if (!stash && !buff)
		return (NULL);
	//malloc
	int		stash_len = ft_strlen(stash);
	int		buff_len = ft_strlen(buff);
	char	*dest = malloc(stash_len + buff_len + 1);
	if (!dest)
		return (NULL);
	if (stash)
		dest = ft_memmove(dest, stash, stash_len);
	ft_memmove(dest+stash_len, buff, buff_len);

	//null term
	dest[stash_len + buff_len] = '\0';
	//free(stash)
	free(stash);
	return (dest);
}

char	*gnl(int fd)
{
	//early err return : fd < 0, BF_SIZE <= 0
	if (fd < 0 || BF_SIZE <= 0)
		return (NULL);
	static char *stash;
	//early normal return : if (stash & stash has 'newline') {ret(extract_line)}
	if (stash && ft_strchr(stash, '\n'))
		return (extract_line(&stash));
	//behavior : while(stash doesn't have newline) {read to bf & cp bf -> stash}
		//static char *stash
		//malloc bf -> read from fd -> cp to buff
		//if (bytes_read <= 0) {1.free(bf) 2.if(bytes < 0){free(stash)} 3.break}
		//bf[bytes] = 0;
		//cp bf to stash && null-term:stash
		//free(bf)
	int		bytes_read;
	char	*buff;
	while (!ft_strchr(stash, '\n'))
	{
		buff = malloc(BF_SIZE + 1);
		if (!buff)
			return (NULL);
		bytes_read = read(fd, buff, BF_SIZE);
		if (bytes_read <= 0)
		{
			free(buff);
			if (bytes_read < 0)
				free(stash);
			break ;
		}
		buff[bytes_read] = '\0';
		stash = join_free(stash, buff);
		free(buff);
	}
	//early normal ret: if (!stash) {return (NULL)}
	if (!stash)
		return (NULL);

	//normal ret: ret(extract)
	return (extract_line(&stash));
}

int	main(int ac, char **av)
{
	/*test: extract_line = OK, no leaks*/
	// char *buff = malloc(30);
	// strcpy(buff, "hi! \nI'm Jin");
	// buff[29] = 0;
	// printf("before extract: [%s]\n", buff);
	// char * l = extract_line(&buff);
	// printf("after extract/line: [%s]\n", l);
	// printf("after extract/buff: [%s]\n", buff);
	// free(l);
	// free(buff);
	/*test: join_free(stash, buff) = OK, no leaks*/ 
	// char	*s1 = malloc(30);
	// char	*s2 = malloc(30);
	// strcpy(s1, "hi! \n");
	// strcpy(s2, "I'm Jin");
	// char *res = join_free(s1, s2);
	// printf("join_free(hi!\n, I'm jin): [%s]\n", res);
	// printf("after join_free/s1: [%s]\n", s1);
	// printf("after join_free/s2: [%s]\n", s2);
	// free(s2);
	// free(res);
	/*ref: malloc -> free : ok*/
	// char	*temp_bf = malloc(10);
	// free(temp_bf);

	/*test: gnl = ?*/
	if (ac != 2 || !av[1])
		return (1);
	int fd = open(av[1], O_RDONLY);
	if (fd < 0)
		return (1);
	char	*line;
	printf("* * * * gnl start * * ** * \n");
	while (1)
	{
		line = gnl(fd);
		if (!line)
			break ;
		printf("%s", line);
		free(line);
					write(1, "JF:1", 4);

	}
	return (0);
}