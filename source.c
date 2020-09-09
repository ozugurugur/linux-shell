#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h> 


int main() {
	
	char exe[] = "/bin/";
	char *args[10];
	args[9] = NULL;
	
	char *command;
    char *line;
    size_t bufsize = 32;
    size_t characters ;
    char exiting[] = "exit\n";
    line = (char *)malloc(bufsize * sizeof(char));
    if( line == NULL){
        perror("Unable to allocate line");
        exit(1);
    }



while(1){            //repeat forever
	printf ("cen354sh> ");
	characters = getline(&line,&bufsize,stdin);           //get the command line as input 

	
		if (strcmp(line,exiting) == 0)                        //exit when user types "exit"
			exit(0);
		
		else{
			//printf ("%s" ,line );

			if (fork() != 0)
				wait(NULL);
			else {
				
				command  = strsep(&line," ");
				strcat (exe,command);
				args[0] = exe;
				args[1] = strsep(&line," ");
				args[2] = strsep(&line," ");
				args[3] = strsep(&line," ");
				args[4] = strsep(&line," ");
				args[5] = strsep(&line," ");
				args[6] = strsep(&line," ");
				args[7] = strsep(&line," ");
				args[8] = strsep(&line," ");
			
			
		
			
				execv(args[0] ,args); 
				
				}
			
	}
}


free(line);





return 0;
}
