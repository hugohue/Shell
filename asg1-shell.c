/*
* CSCI3150 Assignment 1 - Writing a Simple Shell
* Feel free to modify the given code.
* Press Ctrl-D to end the program
*
*  You may put down your reference here:
*
*/

/* Header Declaration */
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

/* Function Declaration */
int getUserInput(char* input);
void tokenizeInput(char* input);
char path[80];
char stack[80][255];
int top=-1;
int global_or=0;

void sig_handler(int sig){

}
/* Functions */
int main(int argc,char* argv[])
{
	signal(SIGINT,sig_handler);
		signal(SIGTSTP,sig_handler);
			signal(SIGQUIT,sig_handler);
	signal(SIGTERM,	sig_handler);
  int isExit = 0;
  do {
    char rawInput[255];
    isExit = getUserInput(rawInput);

    if(isExit) break;

    tokenizeInput(rawInput);



  } while(isExit = 1);
  return 0;
}

/*
  GetUserInput()
  - To parse User Input and remove new line character at the end.
  - Copy the cleansed input to parameter.
  - Return 1 if encountered EOF (Ctrl-D), 0 otherwise.
*/
int getUserInput(char* input)
{
  char buf[255];
  char tmp[4];
  int k;
 // printf("LDER: %s",path);
  getcwd(path, sizeof(path));


  char *s = buf;
  printf("[3150 Shell:%s]=> ",path);
  if(fgets(buf,255,stdin) == NULL)
  {
    putchar('\n');
    return 1;
  }
  // Remove \n
  for(;*s != '\n';s++);
  *s = '\0';
  


  strcpy(input,buf);

  for(k=0;k<3;k++){
  	tmp[k]=input[k];
  }
  tmp[k]='\0';
 // printf("%s\n",tmp);
  if(strcmp(tmp,"bye")==0){
  	if(strcmp(input,"bye")==0){
		return 1; 	
	}
  	printf("bye: wrong number of arguments\n");
}
  return 0;
}
/*
  tokenizeInput()
  - Tokenize the string stored in parameter, delimiter is space
  - In given code, it only prints out the token.
  Please implement the remaining part.
*/
int add_value(int x)
{
	global_or=0;
	return global_or=0;
}

void tokenizeInput(char* input)
{
  char buf[255], cmd[255], cmd2[255];

  char* arr[255], *parameters[255];
  char *envp[] = {(char*) "PATH=/bin", 0};
  int i=0;
  int count;
  int count_or=0;
  int count_and_situation;
  int or_flag=0;
  int or_flag2=0;
  int or_done=1;
  int count_and=0;
  int and_flag=0;
  int and_flag2=0;
  arr[1]=NULL;
  arr[2]=NULL;
  strcpy(buf,input);
  char* token = strtok(buf," ");
  //arr[0]=token;
  while(token != NULL)
  {
  	arr[i++]=token;
 //   printf("TOKEN: %s\n",token);
    token = strtok(NULL," ");
  }
  if(*arr==NULL){
  	return;
  }
  strcpy(cmd2, arr[0]);
  for (int j=0; j<i; j++)
  		parameters[j]=arr[j];
  	parameters[i]=NULL;

 //   printf("cmd2: %s\n",cmd2);
  	count_or=0;
  	count_and=0;
  	global_or=0;
  for (int j=0; j<i; j++)
  {
  	if (strcmp(arr[j],"||")==0){
  		count_or++;
  		if(or_flag>0){
  			or_flag2 =j;
  		}	
  		else or_flag=j;
	}
	if (strcmp(arr[j],"&&")==0){
  		count_and++;	
  		if(and_flag>0){
  			and_flag2 =j;
  		}	
  		else and_flag=j;
	}
	count_and_situation=count_and;
	/*
  	if (arr[j]=="||"){
  		count_or++;	
	}
	if (arr[j]=="&&"){
  		count_and++;	
	}
	*/
//	printf("arr:::: %s\n",arr[j]);
//	printf("count_or: %d\n", count_or);
//	printf("count_and: %d\n", count_and);
  }
 // printf("arr[0]: %s \n", arr[0]);
 // printf("arr[1]: %s \n", arr[1]);
 // printf("arr[2]: %s \n", arr[2]);
while((global_or==0 && count_or>=0) || (global_or==256 && count_and>=0)){
  if (fork()!=0){
 // 	printf("DEBUG2\n");
  	/*
  	else if(strcmp(arr[0],".")==0)
  	{
  		getcwd(path, sizeof(path));
  		printf("%s\n",path);
  		printf("mesdddddsge\n");
  		strcat(path, "/hello");
  		char *argv[] = {"/hello"};
  		execvp(path, argv);
  		//strcat(path, parameters)
  		chdir("parameters");
  	}
  	*/
  	  	if(strcmp(cmd2,"gofolder")==0&&(arr[1]=='\0'||arr[2]!='\0')){
  			printf("gofolder: wrong number of arguments \n");
  			return ;
  		}

  		if(strcmp(cmd2,"gofolder")==0){
		getcwd(path, sizeof(path));
		strcat(path, "/");
		strcat(path, arr[1]);
 // 		printf("GOFOLDER: %s",path);

  		if(chdir(path)==-1){
  			printf("Not a correct directory");
  		}
 // 		printf("CHANGED: %s",path);		
  		return ;
  		}
  		if(strcmp(cmd2,"push")==0&&arr[1]=='\0'){
  			printf("push: wrong number of arguments \n");
  			return ;
  		}

  		if((strcmp(cmd2,"push")==0&&strcmp(arr[1],"..")!=0)){
		getcwd(path, sizeof(path));
 // 		printf("push: %s",path);
// wrong number of arguments
  		if(chdir(arr[1])==-1){
  			printf("Not a correct directory");
  		} else{
  		top++;
  		strcpy(stack[top],path);
  		count=0;
  		for(i=top;i>=0;i--){
  		printf("%d %s \n",count, stack[i]);
  		count++;
  		}	
  	}
  		
  		return ;
  		}

		if(strcmp(cmd2,"pop")==0&&arr[1]!='\0'){
		  			printf("pop: wrong number of arguments \n");
		  			return ;
		  		}

  		if(strcmp(cmd2,"pop")==0 && top!=-2){
  			
  			chdir(stack[top]);
  		//	stack[top]='\0';
  		count=0;
  		top--;
  		for(i=top;i>=0;i--){
  		printf("%d %s \n",count, stack[i]);
  		count++;
  		}
  		if (strcmp(cmd2,"pop")==0 && top==-2){
  			printf("pop: directory stack empty \n");

  			}
		}

		if(strcmp(cmd2,"dirs")==0){
			count=0;
	  		for(i=top;i>=0;i--){
		  		printf("%d %s \n",count, stack[i]);
		  		count++;
			}
  		}
  	wait(&global_or);  	

  	}
  	else {
  //			printf("COUNT_OR: %d\n", count_or);
  //			printf("DEBUG\n");

  		if(count_or==1 || count_or==2){
  			strcpy(cmd2,arr[0]);

  			  for (int j=0; j<or_flag; j++)
  				parameters[j]=arr[j];
  				parameters[or_flag]=NULL;
  		}
  		if(count_or==0 && or_flag>0){
  			strcpy(cmd2,arr[or_flag+1]);
  			for (int j=0; j<i; j++)
  				parameters[j]=NULL;

  			int head=0;
  			for (int j=or_flag+1; j<i; j++)
  			{
  				parameters[head]=arr[j];  
  				head++;		
  				}	
  		}
  		if(count_and_situation==2){
  		if(count_and==2){
  			strcpy(cmd2,arr[0]);

  			  for (int j=0; j<and_flag; j++)
  				parameters[j]=arr[j];
  				parameters[and_flag]=NULL;
  		}
  		if(count_and==1 && and_flag>0){
  			strcpy(cmd2,arr[and_flag+1]);
  			for (int j=0; j<i; j++)
  				parameters[j]=NULL;

  			int head=0;
  			for (int j=and_flag+1; j<and_flag2; j++)
  			{
  				parameters[head]=arr[j];  
  				head++;		
  				}	
  		}  		
  		if(count_and==0 && and_flag>0){
  			strcpy(cmd2,arr[and_flag2+1]);
  			for (int j=0; j<i; j++)
  				parameters[j]=NULL;

  			int head=0;
  			for (int j=and_flag2+1; j<i; j++)
  			{
  				parameters[head]=arr[j];  
  				head++;		
  				}	
  		}
  	}
  		if(count_and_situation==1){
		if(count_and==1){
  			strcpy(cmd2,arr[0]);

  			  for (int j=0; j<and_flag; j++)
  				parameters[j]=arr[j];
  				parameters[and_flag]=NULL;
  		}
  		if(count_and==0 && and_flag>0){
  			strcpy(cmd2,arr[and_flag+1]);
  			for (int j=0; j<i; j++)
  				parameters[j]=NULL;

  			int head=0;
  			for (int j=and_flag+1; j<and_flag2; j++)
  			{
  				parameters[head]=arr[j];  
  				head++;		
  				}	
  		}  	



  		}  	

  		strcpy(cmd, "/bin/");
  		strcat(cmd, cmd2);
 // 		  		printf("cmd %s", cmd);
//		  		printf("cmd2 %s", cmd2);
//		  		printf("para %s", parameters[1]);

  		/*
  		ls -h -l
  		/bin/ls ls
  		/usr/bin/cmd cmd
  		path/cmd cmd
  		*/
  	//	printf("CMD2: %s", cmd2);
  		
  		if(strcmp(cmd2,"gofolder")==0 || strcmp(cmd2,"push")==0|| strcmp(cmd2,"pop")==0||strcmp(cmd2,"dirs")==0||strcmp(cmd2,"bye")==0){
  			_exit(1);
  		}

  		else if(execvp(cmd, parameters)<0)
  		{
	  		cmd[0]='\0';

	  		strcpy(cmd, "/usr/bin/");
	  		strcat(cmd, cmd2);
	  		if(execvp(cmd, parameters)<0){
	  			cmd[0]='\0';
		  		strcpy(cmd, "./");
		  		strcat(cmd, cmd2);
		  		if(execvp(cmd, parameters)<0 && *cmd2!='\0'){
		  			printf("{%s}: command not found\n", cmd2);
		  			exit(EXIT_FAILURE);
		  		}
	  		}	
  		}
// ls || aa >> 1st run >> non run
// aa || ls >> 2nd  non run>> run
// hello || ls >>1st run >> non run

 // hehe && ls >> 1st non run end
 // ls && hehe >> 2nd non run end
 // ls && hello	>> 1st run and 2nd hello

  		/*

*/
  	}
  //	printf("hello\n");
  //	printf("or_done: %d \n",or_done);
  //	printf("global_or: %d \n", global_or);
  //	printf("or_done_flag: %d \n",or_done_flag);
  	if(global_or==256)
  		global_or=0;
  	else
  		global_or=256;

 // 	printf("global_or: %d \n", global_or);
  	count_or--;
  	count_and--;
  }
  return;
}

