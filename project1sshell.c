#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define CMDLINE_MAX 512
int findpipe(char* userInput)
{
    char* ret;
    ret = memchr(userInput, '|', strlen(userInput));
    if (ret != NULL)
    {
        return 1 ;/* Returns 1 if its a pipe*/
    }
     ret = memchr(userInput, '>', strlen(userInput));
    if (ret != NULL)
    {
        return 2 ;/* Returns 2 if its a redirect*/
    }
    else 
    return 3 ; /* Returns 3 if its built-in cmd*/

}
int main(void)
{
        char cmd[CMDLINE_MAX];
	pid_t pid;
        while (1) {
                char *nl;
                /*int retval;*/

                /* Print prompt */
                printf("sshell$ ");
                fflush(stdout);

                /* Get command line */
                fgets(cmd, CMDLINE_MAX, stdin);

                /* Print command line if stdin is not provided by terminal */
                if (!isatty(STDIN_FILENO)) {
                        printf("%s", cmd);
                        fflush(stdout);
                }

                /* Remove trailing newline from command line */
                nl = strchr(cmd, '\n');
                if (nl)
                        *nl = '\0';

                /* Builtin command */
                if (!strcmp(cmd, "exit")) {
                        fprintf(stderr, "Bye...\n");
                        break;
                }
		int cmdType = findpipe(cmd);
		 if(cmdType == 1)
        	{
           		 printf("1");
       		 }
       		 if (cmdType == 2)
       		 {
           		 printf("2");

       		}
       		 if(cmdType == 3 )
       		 {
           		 printf("3");

       		 }

		char *args[] = {cmd,NULL};

                pid = fork();
		if(pid == 0) {
			/* Child*/
			execvp(cmd,args);
			perror("execvp");
			exit(1);
		} else if (pid > 0){
			/* Parent */
			int status;
			waitpid(pid, &status,0);
			printf("+ completed '%s' [%d]\n",cmd,
               			WEXITSTATUS(status));
		} else {
			perror("fork");
			exit(1);
		}
        }

        return EXIT_SUCCESS;
}
