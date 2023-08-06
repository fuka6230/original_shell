#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <signal.h>


#define	BUFFERSIZE 1024
#define	ARGVNUMBER 10
#define MAXCOMMANDLENGTH 128

extern bool only_one_command;

typedef struct Node Node;
struct Node {
	char **argv;
	char *output_to;
	char *input_from;
	Node *next;
};

typedef struct Token Token;
struct Token {
	char *command;
	Token *next;
};

Token *tokenize(void);
Node  *parse(void);


