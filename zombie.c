#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

void main(){
	pid_t pid;
	char *message;
	int n;
	
	pid=fork();
	printf("\n\n%d\n\n",pid);

	switch(pid){
		case -1:
			printf("Failed");
			exit(0);
		case 0: 
			message="Child process";
			n=30;
			printf("Child Process created %d\n", getpid());
			break;
		default:
			message="Parent process";
                        n=3;
                        printf("Parent Process created %d\n", getpid());
                        break;

	}

	for(;n>0;n--){
		printf("\n%s\n",message);
		sleep(1);
	}
}






