## always init before using realloc

### realloc(NULL, size) is valid - it behaves like malloc(size)  
### realloc(ptr, size) is valid when ptr was previously allocated with malloc/calloc/realloc  
## realloc(uninitialized_ptr, size) is undefined behavior and can cause segfault  

So these are safe:

```c
//SAFE
// 1: Init with NULL
char *s = NULL;
s = realloc(s, new_size);  // acts like malloc(new_size)

// 2: Init with malloc
char *s = malloc(1);
s = realloc(s, new_size);  // resizes existing allocation

// BAD, UNSAFE: Uninitialized pointer
char *s;
s = realloc(s, new_size);  // undefined behavior -> seg fault
```