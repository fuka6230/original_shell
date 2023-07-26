#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <fcntl.h>

#define	BUFFERSIZE 1024
#define	TOKENNUMBER 10
#define STDIN "<"

// extern char **argv;

typedef struct Node Node;
struct Node {
	char **argv;
	char *output_to;
	char *input_from;
	bool has_pipe;
	Node *next;
};

Node *tokenize();



