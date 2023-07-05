#include "header.h"

int main(void) {
	tokenize();

	int child;
	if ((child = fork()) < 0) {
		perror("fork");
		exit(1);
	}

	if (child == 0) {
		char *str_init = "/bin/";
		char command[BUFFERSIZE];
		snprintf(command, BUFFERSIZE, "%s%s", str_init, argv[0]);
		execv(command, argv);
		for(int i = 0; i < 5; i++){
			free(argv[i]);
		}
		free(argv);
	}
	return 0;
}