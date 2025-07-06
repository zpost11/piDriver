#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main() 
{
	int file;
	char character;

	file = open("/dev/hello1", O_RDWR);

	if (file < 0) {
		perror("open");
		return file;
	}

	while (read(file, &character, 1)) 
    {
		putchar(character);
	}

	close(file);
	return 0;
}