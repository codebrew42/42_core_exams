
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define SIZE 1


int		ft_strlen(char *s)
{
	if (!s)
		return (0);
	int len = 0;
	while(s[len])
		len++;
	return (len);
}

char	*ft_memmove(char *dest, char *src, int src_len)
{
	if (!dest)
		return (NULL);
	if (!src || !src_len)
		return (dest);
	int	i = src_len;
	if (src < dest && src + src_len > dest)
	{
		while (--i >= 0)
			dest[i] = src[i];
	}
	else
	{
		i = -1;
		while(++i < src_len)
			dest[i] = src[i];
	}
	dest[src_len] = '\0';
	return (dest);
}

char	*ft_strdup(char *src)
{
	if (!src)
		return (NULL);
	int		src_len = ft_strlen(src);
	char	*dest = malloc(src_len + 1);
	ft_memmove(dest, src, src_len);
	dest[src_len] = '\0';
	return (dest);
}

char	*join_free_old_dest(char *dest, char *buff)
{
	static int i = 0;
	if (!dest && !buff)
		return (NULL);
	if (!dest && buff)
	{
		dest = ft_strdup(buff);
		return (dest);
	}
	int	dest_len = ft_strlen(dest);
	int	buff_len = ft_strlen(buff);
	char	*ret = malloc(dest_len + buff_len + 1);
	if (!ret)
	{
		free(dest);
		return (NULL);
	}
	if (dest)
	{
		ft_memmove(ret, dest, dest_len);
		free(dest);
		//printf("ret[%d]: [%s]\n", i++, ret);
	}
	ft_memmove(ret + dest_len, buff, buff_len);
		//printf("ret[%d]: [%s]\n", i++, ret);
	ret[dest_len + buff_len] = '\0';
	return (ret);
}

char	*read_input(int fd)
{
	char	*buff;
	int		bytes_read;
	char	*dest = NULL; //check
	int		total = 0;
	while (1)
	{
		buff = malloc(SIZE + 1);
		if (!buff)
			return (NULL);
		bytes_read = read(fd, buff, SIZE);
		if (bytes_read <= 0)
		{
			free(buff);
			if (bytes_read < 0) //check: && dest?
				free(dest);
			break ;
		}
		buff[bytes_read] = '\0';
		dest = join_free_old_dest(dest, buff);
		free(buff);
	}
	if (!dest)
		return (NULL);
	return (dest);
}

char	*my_memmem(char *big, char *little)
{
	if (!big || !little)
		return (NULL);
	int	big_len = ft_strlen(big);
	int	little_len = ft_strlen(little);
	int	i = 0;
	int j;
	while (big[i])
	{
		j = 0;
		while (big[i+j] == little[j])
			j++;
		if (j == little_len)
			return (&big[i]);
		i++;
	}
	return (NULL);
}

void	filter_str(char *input, char *filter)
{
	if (!input || !filter)
		return ; 
	char	*filter_pos = my_memmem(input, filter);
	if (!filter_pos)
		return ;
	int		i = -1;
	int		filter_len = ft_strlen(filter);
	while (++i < filter_len)
		filter_pos[i] = '*';
	printf("last i = [%d]", i);
	if (filter_pos[i])
		filter_str(&filter_pos[i], filter);
//		filter_str(filter_pos + filter_len, filter);
	return ;
}

int	main(int ac, char **av)
{
	if (ac !=2 || !av[1])
		return (1);
	int		fd = 0;
	char	*input = read_input(fd);
//	if (input)
//		printf("BEFORE FILTER: [%s]", input);
	filter_str(input, av[1]);
//		printf("AFTER FILTER: [%s]", input);
		printf("%s", input);

//	printf("my_memmem=[%s]\n", my_memmem("hi i am jinmu", "ji"));
	return (0);
}