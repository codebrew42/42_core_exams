#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define BF_SIZE 1


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
	if (!s || !*s)
		return (NULL);
	char	*newline_pos = ft_strchr(*s, '\n');

	//copy line
	if (!newline_pos)
		int		line_len = strlen(s);
	else
		int		line_len = newline_pos - *s + 1;
	char *dest = malloc(line_len + 1);
	if (!dest)
		return (NULL);
	memmove(dest, s, line_len);
	dest[line_len] = 0; 

	//update stash
	while (*s != newline_pos)
		*s++;
	return (dest);
}

char	*gnl(int fd)
{
	//er_ret: fd<0, buff_size=0
	if (fd < 0 || BF_SIZE == 0)
		return (NULL);

	//if (stash contains \n) {ret (extract_line($stash)}
	static char	*stash;

	if (ft_strchr(stash, '\n')
		return (extract_line(&stash);

	//loop: if (stash doesn't contain \n) {read(fd, buff, BF_SIZE)}
	char *buff = malloc(BF_SIZE + 1);
	if (!buff)
		return (NULL);

	while (!ft_strchr(stash, '\n'))
	{
		int bytes_read = read(fd, buff, BF_SIZE);
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
