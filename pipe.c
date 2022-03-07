#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include<sys/wait.h>
#define QTD_MESSAGES 2

int main() {
	int pipeFileDescriptors[2];
	int returnStatus;
	char writeMessages[QTD_MESSAGES][20] = {"Maria", "Joao andou a noite"};
	char readMessages[20];
	memset(readMessages, '\0', sizeof(char) * 20);

	returnStatus = pipe(pipeFileDescriptors);
	
	if (returnStatus == -1) {
		printf("Error when create pipe\n");
		return 1;
	}
	pid_t idnum;
	idnum = fork();

	if (idnum == 0) {
		printf("This is the child\n");
		for (int i = 0; i < QTD_MESSAGES; i++){
			printf("Child process is reading Message %d\n", i);
			read(pipeFileDescriptors[0], readMessages, sizeof(char) * 20);
			printf("Message %d is %s\n", i, readMessages);
		}
		 exit(0);
	} else {
		printf("This is the parent\n");
		for (int i = 0; i < QTD_MESSAGES; i++) {
			printf("Parent process is writing Message %d\n", i);
			printf("Message %d is %s\n", i, writeMessages[i]);
			write(pipeFileDescriptors[1], writeMessages[i], sizeof(char) * 20);
		}
		wait(NULL);
	}
	return 0;
}
