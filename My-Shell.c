#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
/*
Use these colors to print colored text on the console
*/
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_RESET   "\x1b[0m"


/*
removes the newline and space character from the end and start of a char*
*/
void removeWhiteSpace(char* buf){
	if(buf[strlen(buf)-1]==' ' || buf[strlen(buf)-1]=='\n')
	buf[strlen(buf)-1]='\0';
	if(buf[0]==' ' || buf[0]=='\n') memmove(buf, buf+1, strlen(buf));
}

/*
tokenizes char* buf using the delimiter c, and returns the array of strings in param
and the size of the array in pointer nr
*/

void tokenize_buffer(char** param,int *nr,char *buf,const char *c){
	char *token;
	token=strtok(buf,c);
	int pc=-1;
	while(token){
		param[++pc]= (char *)malloc(sizeof(token)+1);
		strcpy(param[pc],token);
		removeWhiteSpace(param[pc]);
		token=strtok(NULL,c);
	}
	param[++pc]=NULL;
	*nr=pc;
}

/*
loads and executes a single external command

*/
void executeBasic(char** argv){
	if(fork()>0){
		//parent
		wait(NULL);
	}
	else{

         if ( argv[1] != NULL){
                  printf(ANSI_COLOR_RED "Invalid Input %s , Arguments are not Allowed ! \n"  ANSI_COLOR_RESET, argv[1]);
             }
		 //child
	else {
          	execvp(argv[0],argv);
		
                }
   exit(1);
	}
}

/*
shows the internal help
*/
void showHelp(){
	printf(ANSI_COLOR_GREEN   "<<<<<<<<<---------Help------->>>>>>>>>>"   ANSI_COLOR_RESET "\n");
	printf(ANSI_COLOR_GREEN   "\t\t Exit & Command With No Arguments are allowed in this shell"   ANSI_COLOR_RESET "\n");
	
}

int main(int argc,char** argv)
{
	char buf[500],*buffer[100],buf2[500],buf3[500], *params1[100],*params2[100],*token,cwd[1024];
	int nr=0;
	printf(ANSI_COLOR_GREEN   "*****************************************************"   ANSI_COLOR_RESET "\n");
	printf(ANSI_COLOR_GREEN   "************************** MY SHELL ***************************"   ANSI_COLOR_RESET "\n");

	while(1){
		//print current Directory
		if (getcwd(cwd, sizeof(cwd)) != NULL){
                // trim /root part we only want the other part
                char  *cw= cwd;
                cw += 5;

                printf(ANSI_COLOR_GREEN " root@kali:OUR SHELL ~" ANSI_COLOR_RESET);
		printf(ANSI_COLOR_BLUE "%s# " ANSI_COLOR_RESET, cw);
	}
	else 	perror("getcwd failed\n");

		//read user input
		fgets(buf, 500, stdin);//buffer overflow cannot happen

		//check if only a command with no argument exist & execute

                     //single command including internal ones
				tokenize_buffer(params1,&nr,buf," ");		
		          if(strstr(params1[0],"help")){//help builtin command
				showHelp();
        			}
			else if(strstr(params1[0],"exit")){//exit builtin command
				exit(0);
 	     		}
			else { 
                         executeBasic(params1);
                         }


}
return 0;
}

