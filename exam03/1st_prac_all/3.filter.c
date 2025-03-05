#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#define	BUFF_SIZE 1

void	*ft_memmove(char *dst, char *src, int i)
{
	if(!dst || !i)
		return (NULL);
	if (src + i < dst)
	{
		while (src[--i])
			dst[i] = src[i];
	}
	else
	{
		int j = -1;
		while (src[++j])
			dst[j] = src[j];
	}
	return (NULL);
}

int	ft_strlen(char *s)
{
	int len = 0;
	while (s[len])
		len++;
	return (len);
}

char	*join_free_buff(char *dst, char *bff)
{
	if (!bff)
		return (NULL);
	char *ret = malloc(strlen(dst) + strlen(bff) + 1);
	ft_memmove(ret, dst, strlen(dst));
	ft_memmove(ret + strlen(dst), bff, strlen(bff));
	ret[strlen(dst) + strlen(bff)] = 0;
	free(bff);
	return (ret);
}


char	*read_input()
{
	char	*buff = malloc(BUFF_SIZE + 1);
	int		bytes_read;
	char	*dest;
	int		fd = 0;
	while (1)
	{
		bytes_read = read(fd, buff, BUFF_SIZE);
		if (bytes_read < 0)
		{
			free(buff);
			return (NULL);
		}
		if (bytes_read == 0)
			break ;
		buff[bytes_read] = 0;
		dest = join_free_buff(dest, buff);
	}
	return (dest);
}

int		main(int ac, char **av)
{
	if (ac != 2 || !av || !*av)
		return (1);
	char *input = read_input();
	printf("input[%s]", input);
	return (0);
}