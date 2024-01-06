#include "../get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

int	main()
{
	int fd = open("tests/test2.txt", O_RDONLY);
	for (int i = 0; i < 15; i++)
	{
		printf("%s", get_next_line(fd));
	}
}
