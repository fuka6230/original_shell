#include "header.h"

void signal_handler(int signum) {
	printf(" type exit to end\n");
}

Token *new_token(char *command, Token *next) {
	char *target_command = (char*)calloc(MAXCOMMANDLENGTH, sizeof(char));
	Token *token = (Token *)calloc(1, sizeof(Token));
	snprintf(target_command, MAXCOMMANDLENGTH, "%s", command);
	token->command = target_command;
	if (next != NULL) {
		token->next = next;
	}
	return token;
}

Token *tokenize(void) {
// Token *main(void) {
	char command[MAXCOMMANDLENGTH];
	char string[BUFFERSIZE];
	char *tp;


	printf("> ");
	signal(SIGINT, signal_handler);
	fgets(string, BUFFERSIZE, stdin);
	if (strcmp(string, "exit\n") == 0) {
		exit(1);
	}

	// printf("%s", string);
	tp = strtok(string, "|");
	snprintf(command, MAXCOMMANDLENGTH, "%s", tp);
	// printf("%s\n", command);
	Token *token = new_token(command, NULL);
	// printf("first: %s\n", token->command);


	while(tp != NULL) {
		// strtok関数により変更されたNULLのポインタが先頭
		tp = strtok(NULL, "|");
		
		// ptrがNULLの場合エラーが発生するので対処
		if(tp != NULL) {
			Token *next_token = token;
			snprintf(command, MAXCOMMANDLENGTH, "%s", tp);
			// printf("next: %s\n", next_token->command);
			token = new_token(command, next_token);
			// printf("now: %s\n", token->command);
			// printf("old: %s\n", token->next->command);
		}
	}
	return token;
}