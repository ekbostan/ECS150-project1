#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define CMDLINE_MAX 512
#define EXEC 1
#define REDIR 2
#define PIPE 3
//#define BIC 4 // Built in commands

// struct cmd
// {
//     int type;
// }

// struct execcmd
// {
//     int type;
//     char *args[CMDLINE_MAX];
//     char *eargs[CMDLINE_MAX];
// }

// struct redircmd
// {
//     int type;
//     char *file;
//     char *efile;
//     int mode;
//     int fd;

// }

// struct pipecmd
// {
//     int type;
//     char *left;
//     char *right;
// }

// struct cmd *
// execcmd(void)
// {
//     struct execcmd *cmd;

//     cmd = malloc(sizeof(*cmd));
//     memset(cmd, 0 sizeof(*cmd));
//     cmd->type = EXEC;
//     return (struct cmd *)cmd;
// }

// struct cmd *
// redircmd(char *file, char *efile, int mode, int fd)
// {
//     struct redircmd *cmd;
//     cmd = malloc(sizeof(*cmd));
//     memset(cmd, 0 sizeof(*cmd));

//     cmd->type = REDIR;
//     cmd->file = file;
//     cmd->efile = efile;
//     cmd->mode = mode;
//     cmd->fd = fd;
//     return (struct cmd *)cmd;
// }

// struct cmd *
// pipecmd(struct cmd *left, struct cmd *right)
// {
//     struct pipecmd *cmd;
//     cmd = malloc(sizeof(*cmd));
//     memset(cmd, 0 sizeof(*cmd));

//     cmd->type = PIPE;
//     cmd->left = left;
//     cmd->right = right;
//     return (struct cmd *)cmd;
// }

int *findpipe(char *userInput)
{
    char *ret;
    ret = memchr(userInput, "|", strlen(userInput));
    if (ret != NULL)
    {
        return 1; /* Returns 1 if its a pipe */
    }
    ret = memchr(userInput, ">", strlen(userInput));
    if (ret != NULL)
    {
        return 2;
    }
    else
        return 3;
}

main(void)
{
    char cmd[CMDLINE_MAX];

    while (1)
    {
        char *nl;
        int retval;

        /*print prompt */
        printf("sshell$ ");
        fflush(stdout);

        /* Get command line */
        fgets(cmd, CMDLINE_MAX, stdin);

        /* Print command line if stdin is not provided by terminal */

        if (!isatty(STDIN_FILENO))
        {
            printf("%s", cmd);
            fflush(stdout);
        }

        /* Remove trailing newline from command line */

        nl = strchr(cmd, '\n');
        if (nl)
        {
            *nl = '\0';
        }

        int *execpipe = findpipe(cmd);

        printf("%d", execpipe);
        /* Built in command */

        if (!strcmp(cmd, "exit"))
        {
            fprintf(stderr, "Bye...\n");
            break;
        }

        /* Regular command */
        retval = system(cmd);
        fprintf(stdout, "Return status value for '%s': %d\n", cmd, retval);
    }

    return EXIT_SUCCESS;
}