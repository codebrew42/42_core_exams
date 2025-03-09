/*ft_scanf
- handle s, d and c.
- dont handle options *, m and '
- dont handle max field width
- dont handle types mdifior vars
- dont handle conversions beginning with %n$

Allowed:isspace, isdigit, va_start, va_arg, va_copy, va_end, 
fgetc, ungetc, ferror, feof, stdi
*/

#include <stdio.h>

//err[1]: BUS ERROR
//why? char *name: uninit, that's why
/*
int main(void)
{
	char *name;
	int age;
	printf("Enter Name and Age:");
	int res = scanf("%s, %d", name, &age);

	printf("Result of scanf; Name[%s], Age[%d]", name, age);
	return (0);
}
*/

/**
err2: READING STR
Enter Name and Age:jin, 30
Result of scanf; Name[jin,], Age[1]%  

why? %s reads untill whitespace -> %d fails, because the format doesn't match
 
int main(void)
{
	char name[100];
	int age;
	printf("Enter Name and Age:");
	int res = scanf("%s, %d", name, &age);

	printf("Result of scanf; Name[%s], Age[%d]", name, age);
	return (0);
}
*/

/*
[option1] scanf("%s %d", name, &age) 
[option2] scanf("%s ,%d", name, &age)
*/
int main(void)
{
	char name[100];
	int age;
	printf("Enter Name and Age:");
	int res = scanf("%s hihihi %d", name, &age);

	printf("Result of scanf; Name[%s], Age[%d]", name, age);
	return (0);
}