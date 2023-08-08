#include "header.h"

void output_to_file(Node *node) {
	int fd;
	if (node->is_append == true) {
		fd = open(node->output_to,  O_WRONLY | O_APPEND, 0666);
	}
	else {
		fd = open(node->output_to,  O_WRONLY | O_CREAT | O_TRUNC, 0666);
	}
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

void execute(Node *node) {
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

	execv(command, node->argv);
	
	for(int i = 0; i < ARGVNUMBER; i++){
		free(node->argv[i]);
	}
	free(node->argv);
}

void pipe_process(Node *node) {
	int child;
	int fd[2] = {};

	if (node->next == NULL){
		if (only_one_command == true && node->output_to != NULL) {
			output_to_file(node);
		}
		execute(node);
	}
	else {
		pipe(fd);
		if ((child = fork()) < 0) {
			perror("fork");
			exit(1);
		}
		else if (child == 0) {
			close(fd[0]);
      dup2(fd[1], 1);
			if (node->is_pipe_error == true) {
				dup2(fd[1], 2);
			}
      close(fd[1]);
      
      pipe_process(node->next);
		}
		else {
      // 親プロセスならパイプをstdinにdup2して、
      // 右からi番目のコマンドを実行
      close(fd[1]);
      dup2(fd[0], 0);
      close(fd[0]);
      
			if (node->output_to != NULL) {
				output_to_file(node);
			}
      execute(node);
    }
	}
}

int main(void) {
	int child;
	
	while (1) {
		Node *node = (Node *)calloc(1, sizeof(Node));
		node = parse();

		if ((child = fork()) < 0) {
			perror("fork");
			exit(1);
		}
		if (child == 0) {
			pipe_process(node);
		}
		else
			wait(NULL);
		free(node);
	}

  return 0;
}