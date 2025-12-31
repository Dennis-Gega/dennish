#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
	while (1) {
		printf("dennish> ");

		char *line = NULL;
		size_t linecap = 0;
		ssize_t linelen;

		linelen = getline(&line, &linecap, stdin);
		line[strcspn(line, "\n")] = '\0';

		if (strcmp(line, "exit") == 0)
			exit(0);

		int rc = fork();
		if (rc < 0) {
			fprintf(stderr, "fork failed\n");
			exit(1);
		} else if (rc == 0) {
			char *args[] = { line, NULL };
			execv(args[0], args);
		} else {
			int rc_wait = wait(NULL);
		}
	}

	return 0;
}
