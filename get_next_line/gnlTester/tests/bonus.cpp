extern "C"
{
#define new tripouille
#include "get_next_line_bonus.h"
#undef new
}

#include <sys/wait.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "sigsegv.hpp"
#include "check.hpp"
#include "gnl.hpp"

int iTest = 1;
int main(void)
{
	signal(SIGSEGV, sigsegv); int fd[4];
	title("[BUFFER_SIZE = " << BUFFER_SIZE << "]: " << ENDL)
	
	title("multiple fd: ")
	fd[0] = open("files/41_with_nl", O_RDWR);
	 gnl(1000, NULL);
	 gnl(fd[0], "0123456789012345678901234567890123456789\n");

	fd[1] = open("files/42_with_nl", O_RDWR);
	 gnl(1001, NULL);
	 gnl(fd[1], "01234567890123456789012345678901234567890\n");

	fd[2] = open("files/43_with_nl", O_RDWR);
	 gnl(1002, NULL);
	 gnl(fd[2], "012345678901234567890123456789012345678901\n");

	 gnl(1003, NULL);
	 gnl(fd[0], "0");

	 gnl(1004, NULL);
	 gnl(fd[1], "1");

	 gnl(1005, NULL);
	 gnl(fd[2], "2");

	 gnl(fd[0], NULL);
	 gnl(fd[1], NULL);
	 gnl(fd[2], NULL);
	showLeaks();

	fd[3] = open("files/nl", O_RDWR);
	 gnl(1006, NULL);
	 gnl(fd[3], "\n");
	 gnl(1007, NULL);
	 gnl(fd[3], NULL);
	showLeaks();
	write(1, "\n", 1);
	return (0);
}