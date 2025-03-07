#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define BUFF_SIZE 1

void	*ft_memmove(char *dst, char *src, int n);
int		ft_strlen(char *s);
char	*join_free_buff(char *dst, char *bff);
char	*read_input(void);

void	*ft_memmove(char *dst, char *src, int n)
{
	int	i;

	if (!dst || !src || n <= 0)
		return (dst);
	i = -1;
	if (dst > src && dst < src + n)
		while (n--)
			dst[n] = src[n];
	else
		while (++i < n)
			dst[i] = src[i];
	return (dst);
}

int	ft_strlen(char *s)
{
	int	len;

	len = 0;
	if (!s)
		return (0);
	while (s[len])
		len++;
	return (len);
}

char	*join_free_buff(char *dst, char *bff)
{
	char	*ret;
	int		dst_len;
	int		bff_len;

	if (!bff)
		return (dst);
	dst_len = ft_strlen(dst);
	bff_len = ft_strlen(bff);
	ret = malloc(dst_len + bff_len + 1);
	if (!ret)
		return (NULL);
	if (dst)
		ft_memmove(ret, dst, dst_len);
	ft_memmove(ret + dst_len, bff, bff_len);
	ret[dst_len + bff_len] = '\0';
	free(dst);
	free(bff);
	return (ret);
}

char	*read_input(void)
{
	char	buff[BUFF_SIZE + 1];
	char	*dest;
	char	*tmp;
	ssize_t	bytes_read;

	dest = NULL;
	while (1)
	{
		bytes_read = read(0, buff, BUFF_SIZE);
		if (bytes_read < 0)
		{
			free(dest);
			return (NULL);
		}
		if (bytes_read == 0)
			break ;
		tmp = malloc(BUFF_SIZE + 1);
		if (!tmp)
		{
			free(dest);
			return (NULL);
		}
		ft_memmove(tmp, buff, bytes_read);
		tmp[bytes_read] = '\0';
		dest = join_free_buff(dest, tmp);
	}
	return (dest);
}

int	main(int ac, char **av)
{
	char	*input;

	if (ac != 2)
		return (1);
	input = read_input();
	if (input)
	{
		printf("input[%s]", input);
		free(input);
	}
	return (0);
}