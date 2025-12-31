#include <stdio.h>
#include <string.h>

int main() {
	while (1) {
		char *line = NULL;
		size_t linecap = 0;
		ssize_t linelen;

		while ((linelen = getline(&line, &linecap, stdin) > 0)) {
			if (strcmp(line, "exit\n") == 0)
				break;

		}

		break;
	}

	return 0;
}
