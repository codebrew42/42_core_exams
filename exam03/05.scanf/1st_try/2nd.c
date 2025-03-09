#include <stdio.h>
#include <ctype.h>

void	skip_whitespaces(void);
//bhv: while c(from stdin) is not EOF and isspace(c), skip ;
//err check: if (c != EOF) {unget(c, stdin)}

int		handle_c(char *c_ptr)
//param: c_ptr = destination
//bhv: cp from stdin
//err: if (c != EOF) {unget(c,stdin)}
//bhv: save c to *cptr
//ret: 1

int		handle_str(char *s)
//param: s = destination
//bhv1: skip white(!)
//bhv2: cp one  char from stdin 
//		=> when? while(c = fgetc != EOF && !isspace(c) (!)isspace
//err: if (i of s[i] == 0) {ret 0}
//bhv2: s[i] = 0
//err: if (c != EOF) {unget(c,stdin)}
//ret: 1

int		handle_int(int *i_ptr)
//param: destination
//bhv1: skip white(!)
//bhv2: cp from one char -> check: - or +? then, sigh = -1
//bhv2: while(c=fgetc != EOF && isdigit(c)
//		=> long res <- res * 10 + c - '0'
//err: if (c != EOF){unget(c, stdin)}
//bhv2: save *i_ptr = (int)sign * res
//ret: 1

int		ft_scanf(const char *format, ...)
{
//param: format ""
//bhv1: va_list args; int count = 0
//bhv1: va_start(args)
//bhv2: while(*format)
//		handle %s, %d, %c
//		skip whitespaces
//		skip anything else, if *f != c (fgetc), {unget, break} (!)not ret
//bhv3: va_end(args)
//ret: 1


}

int main(void)
{

	printf("Enter c1 and c2:\n");
	int res1 = ft_scanf("c1  and  c2", &c1, &c2);
	if (res1 == 2)
		printf("SCAN SUC: c1[%c] c2[%c]\n", c1, c2);
	else
		printf("SCAN FAIL\n");



	return(0);
}
