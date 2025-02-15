#ifndef GNL_H
# define GNL_H

# include <stddef.h>
# define GNL
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif
char *get_next_line(int fd);

#endif