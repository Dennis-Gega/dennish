#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
	while (1) {
		printf("dennish> ");


		// get raw line from stdin
		char *line = NULL;
		size_t linecap = 0;
		ssize_t linelen;
		linelen = getline(&line, &linecap, stdin);


		// parse input into array
		char *argv[10], **ap = argv;
		argv[0] = "/bin/";
		for (int i = 1; i < 10; ++i) argv[i] = NULL;
		int argc = 0;
		while (1) {
			char* token = strsep(&line, " \n");
			if (token == NULL || *token == '\n' || *token == '\0')
				break;

			*ap = token;
			++argc;

			if (ap != &argv[10])
				++ap;
		}

		if (strcmp(argv[0], "exit") == 0)
			exit(0);


		int rc = fork();
		if (rc < 0) {
			fprintf(stderr, "fork failed\n");
			exit(1);
		} else if (rc == 0) {
			execv(argv[0], argv);
		} else {
			int rc_wait = wait(NULL);
		}
	}

	return 0;
}
