#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h> 
#include <ctype.h>




char *rtrim(char *s)
{
	if (s!=NULL){
		char* back = s + strlen(s);
		while(isspace(*--back));
		*(back+1) = '\0';
		return s;
	}
}



void errorA(){
	
	char error_message[30] = "An error has occurred\n";
    write(STDERR_FILENO, error_message, strlen(error_message));
		
}



int main() {
	
	char path1[] = "/bin/";
	char path2[]="/usr";
	char *args[10];
	args[9] = NULL;
	char *direction[1];
	char *command;
	char *command2;
    char *line;
    size_t bufsize = 100;
    size_t characters ;
    char exiting[] = "exit";
    char ccd[] ="cd";
    char pth[] ="path";
    line = (char *)malloc(bufsize * sizeof(char));
    
    if( line == NULL){
        errorA();
        exit(1);
    }




	while(1){            //repeat forever
		printf ("cen354sh> ");
		characters = getline(&line,&bufsize,stdin);           //get the command line as input 
		command  = rtrim(strsep(&line," "));
	
	
	
			if (strcmp(command,exiting) == 0)                        //exit when user types "exit"
				exit(0);
			
			else if (strcmp(command,ccd) ==0){
				if (line != NULL){
					direction[0] = rtrim(strsep(&line," "));
					if (strcmp(direction[0],"")!=0 || line!=NULL ){
						if (strsep(&line,"")==NULL    ){
							if(chdir(direction[0])!=0)
							errorA();
						}
						else{errorA();}
					}
					else{errorA();}
				}
				else{errorA();}
			}
			
			else if (strcmp(command,pth) ==0){
				if (line == NULL){
					strcpy(path1,NULL);
					strcpy(path2,NULL);
				}
				else {
					strcpy(path1,rtrim(strsep(&line," ")));
					if (line!=NULL)
					strcpy(path2,rtrim(strsep(&line," ")));
					
				}
					
			}
			
			else{
				//printf ("%s" ,line );
			
			
				if (fork() !=0){
					wait(NULL);
				}
				
			
			
				else {
				
				
					strcat (path1,command);
				
				
					args[1] = rtrim(strsep(&line," "));
					args[2] = rtrim(strsep(&line," "));
					args[3] = rtrim(strsep(&line," "));
					args[4] = rtrim(strsep(&line," "));
					args[5] = rtrim(strsep(&line," "));
					args[6] = rtrim(strsep(&line," "));
					args[7] = rtrim(strsep(&line," "));
					args[8] = rtrim(strsep(&line," "));
			
					if (access(path1,X_OK)==0){
						args[0] = path1;
						execv(args[0] ,args);
					}
				
					else {
					
						strcat (path2,path1);
					
						if(access(path2,X_OK)==0){
							args[0] = path2;
							execv(args[0] ,args);
						}
						else{
						
							errorA();
							exit(0);
						}	
							exit(0);
					}
				}
			
		}
	}


	free(line);






	return 0;
}
