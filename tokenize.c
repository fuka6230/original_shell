#include "header.h"

char **argv;
char *output_file; 
char *input_file;

Node *new_node(char **argv, bool has_pipe, char *output_file, char *input_file) {
	Node *node = (Node *)calloc(1, sizeof(Node));
	node->argv = argv;
	if (output_file == NULL) {
		node->output_to = NULL;
	}
	else {
		node->output_to = output_file;
	}
	if (input_file == NULL)
		node->input_from = NULL;
	else
		node->input_from = input_file;
	node->has_pipe = has_pipe;
	node->next = NULL;
	return node;
}

Node *tokenize(void) {
	char buf[BUFFERSIZE];
	char string[128];
	char first_string[BUFFERSIZE];
	int argv_index = 1;

	argv = (char **)calloc(TOKENNUMBER,sizeof(char *));
	for(int i = 0; i < TOKENNUMBER; i++){
			argv[i] = (char *)calloc(BUFFERSIZE,sizeof(char));
	}
	bool has_pipe;
	has_pipe = false;
	fgets(string, 128, stdin);
	if (strcmp(string, "exit\n") == 0) {
		return 0;
	}

	char *tp;
	tp = strtok(string, " \n");
	
	snprintf(argv[0], BUFFERSIZE, "%s", tp);
	while ( tp != NULL ) {
		tp = strtok(NULL," \n");
		if (tp != NULL && strcmp(tp, "|") == 0) {
			has_pipe = true;
			break;
		}
		if (tp != NULL && strcmp(tp, ">") == 0) {
			tp = strtok(NULL," \n");
			if (tp == NULL) {
				exit(1);
			}
			else {
				output_file = tp;
			}
		}
		else if (tp != NULL && strcmp(tp, "<") == 0) {
			tp = strtok(NULL," \n");
			if (tp == NULL) {
				exit(1);
			}
			else {
				input_file = tp;
			}
		}
		else if (tp != NULL) {
			snprintf(argv[argv_index], BUFFERSIZE, "%s", tp);
			argv_index++;
		}
	}
	argv[argv_index] = NULL;
	Node *node = new_node(argv, has_pipe, output_file, input_file);
	free(tp);
	return node;
}