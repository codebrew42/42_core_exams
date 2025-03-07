#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define BF_SIZE 1

char	*read_input(void)
{
	int		bytes_read;
	char	*buff;      // Read buffer
	char	*new_dest;  // Temporary storage
	char	*dest = NULL; // Final string
	int		total = 0;  // Total bytes read

	buff = malloc(BF_SIZE + 1);
	if (!buff)
		return (NULL);
	while (1)
	{
		bytes_read = read(0, buff, BF_SIZE);
		if (bytes_read < 0)
		{
			free(buff);
			free(dest);
			return (NULL);
		}
		else if (!bytes_read)
			break;
		buff[bytes_read] = '\0';
		
		// 1. Allocate new memory block
		new_dest = malloc(total + bytes_read + 1);
		if (!new_dest)
		{
			free(dest);
			free(buff);
			return (NULL);
		}
		// 2. Copy existing data (if any)
		if (dest)
			memmove(new_dest, dest, total);
		
		// 3. Append new data using total instead of strlen(dest)
		memmove(new_dest + total, buff, bytes_read);
		total += bytes_read;
		new_dest[total] = '\0';   // Maintain null-termination
		
		// 4. Cleanup old data
		free(dest);
		dest = new_dest;
	}
	free(buff);  // Free buffer AFTER loop completes
	return (dest);
}

int	main(int ac, char **av)
{
	char	*input;

	if (ac != 2)
		return (1);
	input = read_input();
	if (!input)
		return (0);
	printf("input: %s", input);
	free(input);
	return (0);
}