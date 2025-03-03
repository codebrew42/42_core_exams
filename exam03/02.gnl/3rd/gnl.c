#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#define BUFF_SIZE 1

int	join_free(char **s1, char *s2)
{
	int		len = strlen(s2);
	int		start;

	start = strlen(*s1);
	if(*s1)
		*s1 = strdup(*s1);
	*s1 = malloc(start + len + 1);
	if (!*s1)
		return (1);
	memmove(s1 + start, s2, len);
	printf("inside join_free: s1[%s]", *s1);
	return (0);
}

int	main()
{
	char *s1;
	char *s2 = "I am";
	char *s3 = "Jin";

	printf("s1[%s]\n", s1);
	printf("s2[%s]\n", s2);
		printf("s3[%s]\n", s3);

	join_free(&s1, s2);
	printf("s1[%s]", s1);

	// join_free(&s2, s3);
	// printf("s2[%s]", s2);


	// join_free(&s3, s3);
	// printf("s3[%s]", s3);

}

// char	*gnl(int fd)
// {
// 	char *buff = malloc (BUFF_SIZE + 1);
// 	if (!buff)
// 		return (NULL);
// 	static char		*stash;
// 	int				bytes_read;

// 	while (1)
// 	{
// 		bytes_read = read(fd, buff, BUFF_SIZE);
// 		if (bytes_read < 0)
// 		{
// 			free(buff);
// 			return (NULL);
// 		}
// 		else if (bytes_read > 0)
// 		{
// 			if (join_free(stash, buff))
// 				return (NULL);
// 		}
// 	}

// }

/*
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
		printf("line[%d]:%s", i, line);
		if (!line)
			break ;
		free(line);
		i++;
	}
	return (0);
}
*/
