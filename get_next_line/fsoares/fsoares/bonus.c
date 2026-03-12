#include "file_utils.h"
#include "../get_next_line_bonus.h"
#include <wchar.h>
#include <locale.h>

void populate_expected(char *buffer, int n)
{
	int i = 0;
	while (i < n)
	{
		i += sprintf(buffer + i, "0123456789");
	}
	buffer[n] = 0;
}

char *__get_line(int line)
{
	switch (line)
	{
	case 0:
		return "0123456789\n";
	case 1:
		return "012345678\n";
	case 2:
		return "90123456789\n";
	case 3:
		return "0123456789\n";
	case 4:
		return "xxxx\n";
	default:
		return NULL;
	}
}

int main(int argn, char **argv)
{
	setup_framework(argn, argv);
	printf(BMAG "BUFFER_SIZE" NC ": %i\n", BUFFER_SIZE);

	TEST("open, error, open", {
		char *name = "read_error.txt";
		char *other = "lines_around_10.txt";
		int fd = open(name, O_RDONLY);
		int fd2 = open(other, O_RDONLY);
		 test_gnl(fd, "aaaaaaaaaa\n");
		 test_gnl(fd2, "0123456789\n");
		 test_gnl(fd, "bbbbbbbbbb\n");
		 test_gnl(fd2, "012345678\n");
		
		next_read_error = 1;
		if (BUFFER_SIZE > 100) {
			char *temp;
			do
			{
				temp = get_next_line(fd);
				free(temp);
			} while (temp != NULL);
		}
		 test_gnl(fd, NULL);
		next_read_error = 0;
		close(fd);
		 test_gnl(fd2, "90123456789\n");
		fd = open(name, O_RDONLY);
		 test_gnl(fd, "aaaaaaaaaa\n");
		 test_gnl(fd2, "0123456789\n");
		 test_gnl(fd, "bbbbbbbbbb\n");
		 test_gnl(fd, "cccccccccc\n");
		 test_gnl(fd2, "xxxx\n");
		 test_gnl(fd2, NULL);
		 test_gnl(fd, "dddddddddd\n");
		 test_gnl(fd, NULL);
	});

	TEST("2 file descriptors", {
		char *name = "lines_around_10.txt";
		int fd_1 = open(name, O_RDONLY);
		int fd_2 = open(name, O_RDONLY);
		 test_gnl(fd_1, "0123456789\n");
		 test_gnl(fd_2, "0123456789\n");
		 test_gnl(fd_1, "012345678\n");
		 test_gnl(fd_2, "012345678\n");
		 test_gnl(fd_2, "90123456789\n");
		 test_gnl(fd_2, "0123456789\n");
		 test_gnl(fd_2, "xxxx\n");
		 test_gnl(fd_2, NULL);
		 test_gnl(fd_1, "90123456789\n");
		 test_gnl(fd_1, "0123456789\n");
		 test_gnl(fd_1, "xxxx\n");
		 test_gnl(fd_1, NULL);
	});

	TEST("multiple fds", {
		char *name = "lines_around_10.txt";

		char expected[20000 + 2];
		populate_expected(expected, 20000);
		expected[20000] = '\n';
		expected[20001] = 0;

		int fd_1 = open(name, O_RDONLY);
		int fd_2 = open(name, O_RDONLY);
		int fd_3 = open(name, O_RDONLY);
		 test_gnl(fd_1, "0123456789\n");
		 test_gnl(fd_2, "0123456789\n");
		 test_gnl(fd_3, "0123456789\n");
		 test_gnl(fd_1, "012345678\n");
		 test_gnl(fd_2, "012345678\n");
		 test_gnl(fd_2, "90123456789\n");

		int fd_4 = open("giant_line_nl.txt", O_RDONLY);
		 test_gnl(fd_2, "0123456789\n");
		 test_gnl(fd_3, "012345678\n");
		 test_gnl(fd_4, expected);
		 test_gnl(fd_2, "xxxx\n");
		 test_gnl(fd_2, NULL);
		 test_gnl(fd_1, "90123456789\n");
		 test_gnl(fd_4, "another line!!!");
		 test_gnl(fd_1, "0123456789\n");
		 test_gnl(fd_4, NULL);
		 test_gnl(fd_1, "xxxx\n");
		 test_gnl(fd_4, NULL);
		 test_gnl(fd_3, "90123456789\n");
		 test_gnl(fd_3, "0123456789\n");
		 test_gnl(fd_1, NULL);
		 test_gnl(fd_3, "xxxx\n");
		 test_gnl(fd_3, NULL);
	});

#ifdef STRICT_MEM

	if (BUFFER_SIZE != 10) {
		printf("\n");
		return 0;
	}

	wchar_t symbols[10] = {0x280B, 0x2819, 0x281A, 0x281E, 0x2816,
						   0x2826, 0x2834, 0x2832, 0x2833, 0x2813};

	g_test = 1;
	alarm(TIMEOUT * 10);
	char *_title = "test limit fds";
	printf(BLU "%-20s" NC ": ", _title);
	fflush(stdout);
	int res = 1;
	errors_file = fopen("errors.log", "w");

	int fds[10000] = {0};
	int start = -1;
	int end = -1;
	int fd;
	int cid = fork();
	if (cid == 0)
	{
		int i = 0;
		setlocale(LC_CTYPE, "");
		printf(BWHT " ");
		while (1)
		{
			wprintf(L"\b%lc", symbols[i]);
			fflush(stdout);
			usleep(100000);
			i = (i + 1) % 10;
		}
	}
	else
	{
		child_pid = cid;
		do
		{
			fd = open("lines_around_10.txt", O_RDONLY);
			if (start == -1 && fd != -1)
				start = fd;
			if (fd != -1)
				end = fd;
			if (end != -1 && fd == -1) {
				close(end);
				end = end - 1;
			}
		} while (fd != -1 && fd < 1000);

		fd = start;
		while (fd <= end && res)
		{
			res = silent_gnl_test(fd, __get_line(fds[fd])) && res;
			fds[fd]++;
			fd++;
		}
		if (res) {
			printf("\b" NC "Read all fds: " GRN "OK!" BWHT "  ");
			fflush(stdout);
		}
		fd = start;
		while (fd <= end)
		{
			close(fd);
			fd++;
		}
		kill(cid, SIGKILL);
		child_pid = -1;
		usleep(200000);
		printf("\b" NC "\n");
		fflush(stdout);
	}
	fclose(errors_file);
#endif

	printf("\n");
}
