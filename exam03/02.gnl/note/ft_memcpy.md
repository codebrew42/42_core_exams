# Memory Allocation: main vs. ft_memcpy

Comparing two approaches for custom ft_memcpy usage.

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


