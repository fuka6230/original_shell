#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(void) {
	char string[128];
	char *first_string;
	char *argv[] = {NULL, NULL, NULL, NULL, NULL};
	int argv_index = 1;
	fgets(string, 128, stdin);
	if (strcmp(string, "exit\n") == 0) {
		return 0;
	}

	char *tp;
	first_string = strtok(string, " \n");
	argv[0] = first_string;
	while ( tp != NULL ) {
		tp = strtok(NULL," \n" );
		if (tp != NULL) {
			argv[argv_index] = tp;
		}
		argv_index++;
	}
	argv[argv_index] = NULL;
			
	int child;
	if ((child = fork()) < 0) {
		perror("fork");
		exit(1);
	}

	if (child == 0) {
		char str_init[50] = "/bin/";
		char string_copy[20];
		strcpy(string_copy, first_string);
		strcat(str_init, string_copy);
		execv(str_init, argv);
	}
	return 0;
}