
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