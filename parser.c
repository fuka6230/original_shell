#include "header.h"

char **argv;
char *output_file; 
char *input_file;

void show_node(Node *node) {
	if (node->next != NULL) {
		show_node(node->next);
	}
}


Node *new_node(char **argv, char *output_file, char *input_file, int argv_num) {
	char **tmp;
	Node *node = (Node *)calloc(1, sizeof(Node));

	tmp = (char **)calloc(ARGVNUMBER,sizeof(char *));
	for(int i = 0; i < ARGVNUMBER; i++){
			tmp[i] = (char *)calloc(BUFFERSIZE,sizeof(char));
	}

	for(int i = 0; i < argv_num; i++){
		snprintf(tmp[i], MAXCOMMANDLENGTH, "%s", argv[i]);
	}
	tmp[argv_num] = NULL;
	node->argv = tmp;
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
	node->next = NULL;
	return node;
}

Node *process_command(char *command) {
	char buf[BUFFERSIZE];
	char string[128];
	char first_string[BUFFERSIZE];
	int argv_index = 1;

	argv = (char **)calloc(ARGVNUMBER,sizeof(char *));
	for(int i = 0; i < ARGVNUMBER; i++){
			argv[i] = (char *)calloc(BUFFERSIZE,sizeof(char));
	}

	// fgets(string, BUFFERSIZE, stdin);
	// if (strcmp(string, "exit\n") == 0) {
	// 	exit(1);
	// }

	char *tp;
	tp = strtok(command, " \n");
	
	snprintf(argv[0], BUFFERSIZE, "%s", tp);
	while ( tp != NULL ) {
		tp = strtok(NULL," \n");
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
	// argv[argv_index] = NULL;
	Node *node = new_node(argv, output_file, input_file, argv_index);
	free(tp);
	return node;
}

Node *parse(void) {
	Node *node;
	Node *old_node = NULL;
	Node  *first_node = NULL;
	Token *token = tokenize();
	while (1) {
		node = process_command(token->command);
		if (old_node != NULL) {
			old_node->next = node;
		}
		if (first_node == NULL) {
			first_node = node;
		}
		// printf("%s\n", node->argv[0]);
		if (token->next == NULL) {
			break;
		}
		old_node = node;
		token = token->next;
	}
	show_node(first_node);
	return first_node;
}