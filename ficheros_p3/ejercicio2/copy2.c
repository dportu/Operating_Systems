#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 512

void copy(int fd_in, int fd_out)
{
	int read_bytes = 0;
	char buffer[BUFFER_SIZE];
	
	while ((read_bytes = read(fd_in, buffer, sizeof(buffer))) > 0) {
		/* Transfer data from the buffer onto the output file */
		if (write(fd_out, buffer, read_bytes) < read_bytes) {
			perror("Write");
			exit(1);
		}
	}

	if (read_bytes < 0) {
		perror("Read");
		exit(1);
	}
}

void copy_regular(char *orig, char *dest)
{

}

void copy_link(char *orig, char *dest)
{

}

int main(int argc, char *argv[])
{
	int fd_input;
	int fd_output;
	struct stat stats;
	

	if(argc != 3)  {
		perror("Enter 2 arguments");
	}
	else {
		fd_input = open(argv[1], O_RDONLY);
		fd_output = creat(argv[2], 0644);

		if(fd_input < 0) {
			perror("Open");
		}
		else if(fd_output < 0) {
			perror("Create");
		}
		else {
			lstat(fd_input, stats);
			switch(stats.st_mode) {
				
			}

			copy(fd_input, fd_output);
			close(fd_input);
			close(fd_output);
		}
	}

	return 0;
}
