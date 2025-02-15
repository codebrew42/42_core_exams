#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

/** fixed */
void	*ft_memcpy(char *dest, char *src, size_t n)
{
	size_t i = 0;

	while (i < n)
	{
		dest[i] = src[i];
		i++;
	}
	dest[n] = '\0';
	return dest;
}

int main(void)
{
	//test ft_memcpy
	char	*dst;
	char	*src;

	dst = malloc(3);
	if (!dst)
	{
		fprintf(stderr, "ERROR: malloc failed");
		exit (1);
	}
	dst = ft_memcpy(dst, "hi", 2);
	printf("%s", dst);

/*

    dst = ft_memcpy(NULL, "hi", 2);
    if (!dst)
    {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    printf("%s", dst);
    free(dst);
    return 0;

*/
	return 0;
}