/* Name: David Nallapu
ID:1610110115
*/
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#define MAX_LINE 80 /* The maximum length command */
int main(void) {

    char com[] = "";
   //opens file for append and read

    int i = 0;
    int flag = 0;
    int length = 0;
    char * p;
    char * args[MAX_LINE / 2 + 1]; /* command line arguments */
    int should_run = 1; /* flag to determine when to exit program */
    while (should_run) {
         FILE * fp;
    fp = fopen("/home/david/1.txt", "a");
        printf("osh>");
        flag = 0;
        fflush(stdout);
        fgets(com,MAX_LINE,stdin);
        com[strlen(com)-1]='\0';

        for (int j = 0; com[j] != '\0'; ++j) {//loop to find length of command
            length++;
        }

        for (int j = 0; j < length; j++) {//loop to remove & if it exists
            if (com[j] == '&') {
                flag = 1;
                com[j] = '\0';
            }

        }
if(strcmp(com,"history"))
            fprintf(fp, "%s\n", com);//writes to file for history
        
            fclose(fp);
        if (!strcmp(com, "exit")) // Exit condition
        {
            fclose(fp);
            should_run = 0;
        }

        if (!strcmp(com, "history")) {//History 
            FILE * fd;
            fd = fopen("/home/david/1.txt", "r");
            char c;
            int count = 0;
            for (c = getc(fd); c != EOF; c = getc(fd))
                if (c == '\n') // Increments count if this character is newline
                    count = count + 1;
             

            char history[count][MAX_LINE / 2 + 1];

            char * line = NULL;
            size_t len = 0;
            int i = 0;
            ssize_t read;
            fseek(fd, 0, SEEK_SET);

            while ((read = getline( & line, & len, fd)) != -1) {//copies each line of file into a 2d Array
              
                strcpy(history[i], line);
                i++;
            }
            int z = 0;
            fclose(fd);

            for (int j = count - 1; j >= 0 && z < 10; --j) {//prints the history line by line
                printf("%d. %s\n", z++, history[j]);
            }

            if (count == 0) {
                printf("No commands in history\n");
                continue;
            }
            printf("Enter the command you want to run(!N, !!-most recent command)");
            char input[2];
            scanf("%s", input);
            char * d;
            int j = 0;

            if (!strcmp(input, "!!"))

            {
                d = strtok(strtok(history[count - 1], "\n"), " ");
                while (d != NULL) {
                    args[j++] = d;
                    d = strtok(NULL, " ");
                }
                args[2] = NULL;
                execvp(args[0], args);

            }
            int cho = (int) input[1];
            cho -= 47;//converts ASCII to integer
            if (cho > count) {
                printf("No such command in history.\n");
                break;
            }

            if (0 <= cho <= 9) {

                d = strtok(strtok(history[count - cho], "\n"), " ");
                while (d != NULL) {
                    args[j++] = d;
                    d = strtok(NULL, " ");
                }
                args[2] = NULL;
                execvp(args[0], args);
            }

        }

        
        
            fprintf(fp, "%s\n", com);//writes to file for history
        

        pid_t pid;//Forking process starts here
        pid = fork();
        if (pid < 0) {
            printf("\nFailed forking child..");

        } else if (pid == 0) {

            p = strtok(com, " ");
            while (p != NULL) {
                args[i++] = p;
                p = strtok(NULL, " ");
            }
            execvp(args[0], args);

        } else {

            if (flag == 0)// wait(NULL) invoked if ampersand exists in command
                wait(NULL);

        }
    }

    return 0;
}