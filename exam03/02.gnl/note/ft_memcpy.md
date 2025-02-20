# Memory Allocation: main vs. ft_memcpy

## memcpy
#### what is memcpy?
Copies `n` bytes bytes by bytes from the source mem area to the destination mem area.
when the source and destination memory areas don't overlap. 

- **important:** If they overlap, use 'memmove'

 * @pre		The function does not check whether dest has enough allocated memory for  the n bytes. 
 * @pre		It only checks if dest or src is NULL. 
 * @pre		Therefore, it is the responsibility of the caller to ensure that dest has enough space. 
 * @param	n = **bytes** to copy.
 * @return	a pointer to the destination memory area (`dst`).
 * @note	why using (const)unsigned char *? : just to move pointer byte by byte

### when **dest** is NULL
- it's clear what to do when src is NULL
- but, when **src** is 

```c
int main()
{
	char *s = NULL;

	if (!s)
		printf("!s\n"); //!s will be printed
	else
		printf("s, s exist\n);
}

```

## Approach 1: Allocation in main
- Caller allocates & frees the buffer.
- More control; follows the standard memcpy pattern.
- Example:
```c
char *dst = malloc(3);
ft_memcpy(dst, "hi", 2);
dst[2] = '\0';
printf("%s\n", dst);
free(dst);
```
## Approach 2: Allocation in ft_memcpy
- The function allocates memory and returns a new pointer.
- Simpler caller code but with less control and potential ownership issues.
- Example:
```c
char *dst = ft_memcpy(NULL, "hi", 2);
printf("%s\n", dst);
free(dst);
```

## real memcpy 

```c
void *ft_memcpy(void *dest, const void *src, size_t n) {
    unsigned char *d = dest;
    const unsigned char *s = src;
    
    while (n--) {
        *d++ = *s++;
    }
    return dest;
}
```

## problem : seg fault
### when?
- when dest contains strn, seg fault
- when dest is just malloced, then it's ok
- should i fix this?

### OK cases

```c
int	main(int ac, char **av)
{
	char	*s1 = "Hi";
	s1 = malloc(10);
	char *s2 = s1 - 10;
	s2 = "jin";
	printf("before:[%s]\n", s1);
	ft_memcpy(s1, s2, 1);
	printf("after:[%s]\n", s2);
	return (0);
}
```
- surprisingly, it didn't cause seg fault
- assigining specific adr to src -> put str to that src -> memcpy
- i assigned (dest + 10), (dest - 10), both worked

```c
#include <stdio.h>
#include <stdlib.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*d;
	const char	*s;
	int			i;

	d = (char *)dest;
	s = (const char *)src;
	if (!s || !n)
		return (NULL);
	i = -1;
	if (d < s)
	{
		while (++i < n && s[i])
			d[i] = s[i];
	}
	else
	{
		while (n-- >= 0 && s[n])
			d[n] = s[n];
	}
	return (d);
}

int	main(int ac, char **av)
{
	char	*s = NULL;
	char	*str = "jieun    !     ";
	printf("before:[%s]\n", str);
	ft_memcpy(str, "t", 1); //seg fault1
	printf("after:[%s]\n", str); 
	return (0);
}

int	main(int ac, char **av)
{
	char	*str1;
	char	*str2 = "jieun    !     ";

	str1=malloc(10);
	printf("before:[%s]\n", str);
	ft_memcpy(str1, str2, 1);
	printf("after:[%s]\n", str);
	return (0);
}

int	main(int ac, char **av)
{
	char	*s1 = "Hi";
	char	*s2 = "jieun    !     ";
	s1 = malloc(10);
	s1 = "HI"; //without this; no seg fault
	printf("before:[%s]\n", s1);
	ft_memcpy(s1, s2, 1);
	printf("after:[%s]\n", s2);
	return (0);
}

/

```