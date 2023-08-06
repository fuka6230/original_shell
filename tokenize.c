#include "header.h"

Token *new_token(char *command, Token *next) {
	// char *target_command;
	char *target_command = (char*)calloc(128, sizeof(char));
	Token *token = (Token *)calloc(1, sizeof(Token));
	snprintf(target_command, 128, "%s", command);
	token->command = target_command;
	if (next != NULL) {
		token->next = next;
	}
	return token;
}

void main(void) {
	char command[128];
	char string[128];
	char *tp;

	fgets(string, 128, stdin);
	if (strcmp(string, "exit\n") == 0) {
		exit(1);
	}

	// printf("%s", string);
	tp = strtok(string, "|");
	snprintf(command, 128, "%s", tp);
	// printf("%s\n", command);
	Token *token = new_token(command, NULL);
	// printf("first: %s\n", token->command);


	while(tp != NULL) {
		// strtok関数により変更されたNULLのポインタが先頭
		tp = strtok(NULL, "|");
		
		// ptrがNULLの場合エラーが発生するので対処
		if(tp != NULL) {
			Token *next_token = token;
			snprintf(command, 128, "%s", tp);
			// printf("next: %s\n", next_token->command);
			token = new_token(command, next_token);
			// printf("now: %s\n", token->command);
			// printf("old: %s\n", token->next->command);
		}
	}
}