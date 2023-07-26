#include "header.h"

int main(void) {
	Node *node = (Node *)calloc(1, sizeof(Node));
	node = tokenize();

	int child;
	if ((child = fork()) < 0) {
		perror("fork");
		exit(1);
	}

	if (child == 0) {
		char *str_init = "/bin/";
		char command[BUFFERSIZE];
		snprintf(command, BUFFERSIZE, "%s%s", str_init, node->argv[0]);

		if (node->input_from != NULL) {
			int fd_from;
			fd_from = open(node->input_from, O_RDONLY, 0666);
			if (fd_from < 0) {
				perror("open");
				exit(1);
			}
			if (dup2(fd_from, 0) < 0) {
				perror("dup2");
				close(fd_from);
				exit(1);
			}
			close(fd_from);
		}

		if (node->output_to != NULL) {
			int fd;
			fd = open(node->output_to, O_WRONLY | O_CREAT | O_TRUNC, 0666);
			if (fd < 0) {
				perror("open");
				exit(1);
			}
			if (dup2(fd, 1) < 0) {
				perror("dup2");
				close(fd);
				exit(1);
			}
			close(fd);
		}

		execv(command, node->argv);
		for(int i = 0; i < TOKENNUMBER; i++){
			free(node->argv[i]);
		}
		free(node->argv);
	}
	return 0;
}