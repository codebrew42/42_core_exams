#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
//#define BUFF_SIZE 1

void	ft_memmove(char *dst, char *src, size_t len)
{
	if (!src || !dst)
		return ;
	size_t i = 0;
	if (src + len > dst)
	{
		while (src[--len])
		{
			dst[len] = src[len];
		}
	}
	else
	{
		while (src[i])
		{
			dst[i] = src[i];
			i++;
		}
	}
	dst[len] = 0; //!
	return;
}

char *extract_line(char **s)
{
	//early ret
	if (!s || !*s)
		return (NULL);

	//extract first
	int dest_len = strlen(*s);
	char *newline_pos = strchr(*s, '\n');
	if (newline_pos)
		dest_len -= strlen(newline_pos + 1);
	char *dest = malloc(dest_len + 1);
	if (!dest)
		return (NULL);
	ft_memmove(dest, *s, dest_len);
	dest[dest_len] = 0; //
	//update stash
	if (!newline_pos)
	{
		*s = NULL;
//		free(*s); //!; wrong ! (freed mem was not allocated)
	}
	else
	{
		while (*s != newline_pos)
			*s += 1;
		*s += 1;
	}
	
	return (dest);
}

int	ft_strlen(char *s)
{
	if (!s)
		return (0);
	int	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	join_free(char **s1, char *s2)
{
	int		start;

	if (!*s1 && !s2)
	{
		printf("case A\n");
		*s1 = NULL;
		return (1);
	}
	int		len_s2 = ft_strlen(s2);
	int		len_s1 = ft_strlen(*s1);
	char	*ret = malloc(len_s1 + len_s2 + 1);
	if (!ret)
	{
		*s1 = NULL;
//		free(s2);
		return (1);
	}
	if (*s1)
		ft_memmove(ret, *s1, len_s1);
	if (s2)
		ft_memmove(ret+ len_s1, s2, len_s2);
	ret[len_s1+len_s2] = 0;
	*s1 = ret;
	free(s2);  //!: free bf
	return (0);
}

/* testing join_free 
int	main()
{
	char *s1 = NULL;
	char *s2 = "I am ";
	char *s3 = "Jin";

	printf("s1[%s]\n", s1);
	printf("s2[%s]\n", s2);
	printf("s3[%s]\n", s3);

	join_free(&s1, s2);
	printf("joined s1+s2[%s]", s1);

	join_free(&s2, s3);
	printf("joined s2+s3[%s]", s2);


	// join_free(&s3, s3);
	// printf("s3[%s]", s3);

}*/

char	*gnl(int fd)
{
	if (fd < 0 || BUFF_SIZE <= 0)
		return (NULL);
	if (stash && strchr(stash, '\n')) //difficult
		return (extract_line(&stash));

	char *buff = malloc (BUFF_SIZE + 1);
	if (!buff)
		return (NULL);

	static char		*stash;
	int				bytes_read;
	while (1)
	{
		bytes_read = read(fd, buff, BUFF_SIZE);
		if (bytes_read < 0)
		{
			if (stash)
				free(stash);
			free(buff);
			return (NULL);
		}
		else if (!bytes_read)
			break ;
		buff[bytes_read] = 0; //!
		if (join_free(&stash, buff))
		{
			free(stash);
			return (NULL);
		}
		if (strchr(stash, '\n'))
			break ;
	}
	return (NULL);
}


int		main(int ac, char **av)
{
	if (ac != 2 || !*av)
		return (1);
	int fd = open(av[1], O_RDONLY);
	if (fd < 0)
		return (1);
	int i = 0;
	char *line;
	while (1)
	{
		line = gnl(fd);
		if (!line)
			break ;
		printf("%s",line);
		free(line);
		i++;
	}
	return (0);
}
