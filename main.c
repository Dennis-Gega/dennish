#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
	while (1) {
		printf("dennish> ");

		char *line = NULL;
		size_t linecap = 0;
		ssize_t linelen;

		linelen = getline(&line, &linecap, stdin);

		if (strcmp(line, "exit\n") == 0)
			exit(0);
		
		execv(line, NULL);	
	}

	return 0;
}
