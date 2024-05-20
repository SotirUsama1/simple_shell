#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

char** commandToAv(char* BUFFER){
        size_t BUFF_SIZE = 32;
        size_t WORD_SIZE = 10;

        char* word = (char*) malloc(WORD_SIZE * sizeof(char));
        char** av = (char**) malloc(sizeof(BUFFER));
        int count = 0;

        do{
                word = strtok(BUFFER, " ");

                while (word != NULL){
                        av[count] = word;
                        word = strtok(NULL, " ");
                        count++;
                }
        }while(0);

	av[count] = '\0';
	
	if (av[count-1][strcspn(av[count-1],"\n")] == '\n') {
		av[count-1][strcspn(av[count-1],"\n")] = '\0';
        }

	return av;
}

int main(){
        size_t x;
        char* BUFFER;
        size_t BUFF_SIZE = 32;
	char** av;
	pid_t cur;
	int status;

        BUFFER = (char*) malloc(BUFF_SIZE * sizeof(char));

        while (1){
                printf("$ ");
                x = getline(&BUFFER, &BUFF_SIZE, stdin);
		if (x == -1)
			printf("\n");
                        return 0;

		av = commandToAv(BUFFER);

		cur = fork();
		if (cur == -1)
			perror("Error:fork:");
		else if (cur == 0)
		{
			if (execve(av[0], av, NULL) == -1)
        		{
                		perror("Error:execve:");
        		}
		}
		wait(&status);
        }
}
