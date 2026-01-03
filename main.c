#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/types.h>

char error_message[30] = "An error has occurred\n";
char path[50] = "/bin/";

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
		char buf[50];
		argv[0] = buf;
		strcpy(argv[0], path);

		for (int i = 1; i < 10; ++i) argv[i] = NULL;
		int argc = 0;
		while (1) {
			char* token = strsep(&line, " \n");
			if (token == NULL)
				break;
			else if (*token == '\n' || *token == '\0')
				continue;

			// append command name to $PATH if command is in there
			if (argc == 0) {
				char buf[50]; strcpy(buf, path);
				strcat(buf, token);

				if (access(buf, F_OK) == 0)
					strcat(argv[0], token);
				else *ap = token;
			}

			else *ap = token;
			++argc;

			if (ap != &argv[9])
				++ap;
		}

		// builtin commands
		bool is_builtin = false;
		if (strcmp(argv[0], "exit") == 0) {
			if (argc != 1) {
				write(STDERR_FILENO, error_message, strlen(error_message));
				exit(1);
			}

			is_builtin = true;
			exit(0);
		}

		if (strcmp(argv[0], "cd") == 0) {
			if (argc == 1) {
				chdir(getenv("HOME"));
			} else if (argc >= 2 || chdir(argv[1]) == -1) { 
				write(STDERR_FILENO, error_message, strlen(error_message));
				exit(1);
			}
			is_builtin = true;
		}

		if (strcmp(argv[0], "path") == 0) {
			if (argc != 2) {
				write(STDERR_FILENO, error_message, strlen(error_message));
				exit(1);
			}

			is_builtin = true;
			strcpy(path, argv[1]);
		}


		if (!is_builtin) {
			int rc = fork();
			if (rc == -1) {
				write(STDERR_FILENO, error_message, strlen(error_message));
				exit(1);
			}

			if (rc < 0) {
				fprintf(stderr, "fork failed\n");
				exit(1);
			} else if (rc == 0) {
				execv(argv[0], argv);
			} else {
				int rc_wait = wait(NULL);
			}
		}
	}

	return 0;
}
