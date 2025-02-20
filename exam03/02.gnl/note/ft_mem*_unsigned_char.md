
## why using **unsigned char** here?

> not clear
- to mv ptr byte by byte

```c

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*temp_dst;
	const char	*temp_src;

	temp_dst = (char *)dst;
	temp_src = (const char *)src;
	if (!temp_dst && !temp_src)
		return (NULL);
	while (n--)
	{
		*temp_dst++ = *temp_src++;
	}
	return (dst);
}


```

## how to use unsigned int or size_t in a loop?
```c
void	*ft_memcopy(void *dest, const void *src, size_t n)
{
	char		*d;
	const char	*s;

	d = dest;
	s = src;
	if (!src || !n)
		return (NULL);
	if (s == d)
		return (d);
	if (d < s && d + n > s)
		ft_memmove(dest, src, n);
	else
	{
		while (--n >= 0)
		{
			printf("BEFORE: d[%zu]=[%s], s[%zu]=[%s]\n", n, &d[n], n, &s[n]);
			d[n] = s[n];
			printf("AFTER: d[%zu]=[%s], s[%zu]=[%s]\n", n, &d[n], n, &s[n]);

		}
	}
	return (d);
}

```
> this example[1] cases seg fault

#### why segfault?
-  3 -> 2 -> 1 -> 0 -> 123890128901248904098 very large velue  
- so change like below  

```c
void	*ft_memcopy(void *dest, const void *src, size_t n)
{
	else
	{
		while (n > 0)
		{
			n--;
			printf("BEFORE: d[%zu]=[%s], s[%zu]=[%s]\n", n, &d[n], n, &s[n]);
			d[n] = s[n];
			printf("AFTER: d[%zu]=[%s], s[%zu]=[%s]\n", n, &d[n], n, &s[n]);
		}
	}
}

```