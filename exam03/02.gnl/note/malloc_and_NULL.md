
```c
#include <stdio.h>
#include <stdlib.h>

int main()
{
	char *s;

	s = malloc(10);
	s = NULL;
	if (!s)
		printf("!s\n"); //!s: printed
	else
		printf("s, s exist\n");
}

int main()
{
	char *s;

	s = malloc(10);
	if (!s)
		printf("!s\n");
	else
		printf("s, s exist\n"); //s, s exist: printed
}


int main()
{
	char *s = NULL;

	if (!s)
		printf("!s\n"); //!s printed
	else
		printf("s, s exist\n");
}


```