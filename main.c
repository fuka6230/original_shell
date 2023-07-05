#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define	BUFFERSIZE	1024

int main(void) {
	char buf[BUFFERSIZE];
	char string[128];
	char first_string[BUFFERSIZE];
	char **argv;
	int argv_index = 1;

	argv = (char **)calloc(5,sizeof(char *));
	for(int i = 0; i < 5; i++){
			argv[i] = (char *)calloc(BUFFERSIZE,sizeof(char));
	}
	fgets(string, 128, stdin);
	if (strcmp(string, "exit\n") == 0) {
		return 0;
	}

	char *tp;
	tp = strtok(string, " \n");
	
	snprintf(argv[0], BUFFERSIZE, "%s", tp);
	while ( tp != NULL ) {
		tp = strtok(NULL," \n");
		if (tp != NULL) {
			snprintf(argv[argv_index], BUFFERSIZE, "%s", tp);
			argv_index++;
		}
	}
	argv[argv_index] = NULL;
			
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