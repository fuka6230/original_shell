#include "header.h"

char **argv;

int tokenize(void) {
	char buf[BUFFERSIZE];
	char string[128];
	char first_string[BUFFERSIZE];
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
	return 1;
}