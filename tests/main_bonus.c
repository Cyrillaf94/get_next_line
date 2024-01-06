#include "../bonus/get_next_line_bonus.h"
#include <stdio.h>
#include <fcntl.h>

int	main()
{
	int fd = open("tests/test.txt", O_RDONLY);
	int fd2 = open("tests/test2.txt", O_RDONLY);
	for (int i = 0; i < 15; i++)
	{
		printf("test : *%s*\n", get_next_line(fd));
		printf("test 1 : *%s*\n", get_next_line(fd2));
	}
}
