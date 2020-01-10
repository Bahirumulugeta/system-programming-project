
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
int copy(char arg1[],char arg2[]);
int cut(char arg1[],char arg2[]);
int encrypt (char arg[]);
int decrypt (char arg[]);
int display(char arg[]);
int main(int argc, char *argv[]) 
{
  
  if((strcmp(argv[1],"-c")==0) && (argc==4)){
    if(copy(argv[2],argv[3])==1){
       printf("\ncopied successfully\n");
    }
  }
  
  else if((strcmp(argv[1],"-x")==0) && (argc==4))
  {
    if(copy(argv[2],argv[3])==1){
       remove(argv[2]);
       printf("\ncutted succesfully\n");
    }
  }
  else if((strcmp(argv[1],"-d")==0)&&(argc==3)){
       if( access( argv[2], F_OK ) != -1 ) {
           remove(argv[2]);
           printf("\ndeleted successfully\n");
    
        } else {
         printf("\nfile not founcd\n");
         }
  }
  else if((strcmp(argv[1],"-fe")==0)&&(argc==3)){
    if(encrypt(argv[2])==1){
       printf("\nencripted successfully\n");
    }
    
  }
   else if((strcmp(argv[1],"-fd")==0)&&(argc==3)){
   if(decrypt(argv[2])==1){
      printf("\ndecryped successfully\n");
    }
  }
  else if((strcmp(argv[1],"-s")==0)&&(argc==3)){

    char *args[]={"./shell_bash.sh",argv[1],argv[2],NULL};
    execvp(args[0],args);
  }
  else if((strcmp(argv[1],"-h")==0)&&(argc==4)){

    char *args[]={"./shell_bash.sh",argv[1],argv[2],argv[3],NULL};
    execvp(args[0],args);
  }
  else if((strcmp(argv[1],"-uh")==0)&&(argc==4)){

    char *args[]={"./shell_bash.sh",argv[1],argv[2],argv[3],NULL};
    execvp(args[0],args);
  }
  else if((strcmp(argv[1],"-disp")==0)&&(argc==3)){
    if(display(argv[2])!=1){
      printf("\nPlease enter correct file name,try again.\n");
    }
  }
  else if((strcmp(argv[1],"?")==0))
  {
     printf("\n.....................................................................................");
     printf("\n...............                 Help                               ..................");
     printf("\n____________________________________________________________________________________\n");
     printf("\n...                        file Controlling                                      ...\n");
     printf("\n.....................................................................................");
     printf("\n  With four(4) arguments");
     printf("\n  run [excutable file] [variables] [source file] [destination file]");
     printf("\n       Where [variable] is... \n");
     printf("\n                     -c      to copy file");
     printf("\n                     -x      to cut file");
     printf("\n  run [excutable file] [variables] [parent path] [file name]");
     printf("\n       Where [variable] is... \n");
     printf("\n                     -h      to hide file");
     printf("\n                     -uh     to un hide file");
     printf("\n.....................................................................................");
     printf("\n  With three(3) arguments");
     printf("\n  run [excutable file] [variables] [file name]");
     printf("\n       Where [variable] is... \n");
     printf("\n                     -d      to delete file");
     printf("\n                     -fe     to encrypt file");
     printf("\n                     -fd     to decrypt file");
     printf("\n                     -s      to search file");
     printf("\n                     -disp   to display the content of  file");
     
     printf("\n  please run [excutable file] ?        to get help about the system  ");
     printf("\n.....................................................................................\n");
  }
  
  else{
    printf("no arguments in this form please run [excutable file] ?\n");
  }
  return 0;
}
int copy(char arg1[],char arg2[]){
 // creat a pointer
  FILE *fileptr1,*fileptr2;
  int i;
  char ch;
  if( (fileptr1 = fopen(arg1, "r") ) == NULL ) {//open source file in only read mode
    printf("Error...\nCannot open the source file, please check the file name carryfully");//display if argv[0] does not exit
    return -1;
   }
   if( (fileptr2 = fopen(arg2, "r") ) != NULL) {// check the destination file if exists or not to prevnt existing file

    printf("\nWarning... file  already exists.\n");
    printf("Press Y to continue. Or any other key to exit: ");

    ch = getchar();
    if(ch != 'Y' && ch != 'y') {
        
      printf("\ncopying process was terminated.\n");
      fclose(fileptr1);
      fclose(fileptr2);
      return -1;
     }
    else{
      fclose(fileptr2);// close read mode connection
      fileptr2 = fopen(arg2, "w");// now open destination file in write mode
    }
  }
  else {
    fileptr2 = fopen(arg2, "w");//if the destination file doesn't exit open the pointer in open mode
  }
  
  while( !feof(fileptr1) ) {// copy the content of source to destination character by character
    ch = getc(fileptr1);
    if(ch != EOF) {
      putc(ch, fileptr2);
    }
  }
  // close both pointer connection
  fclose(fileptr1);
  fclose(fileptr2);
 
 return 1;
}
int encrypt(char arg[]){
  char ch, choice;
	FILE *fps, *fpt;
	fps=fopen(arg, "r");

	fpt=fopen("temp.txt", "w");
	while(1)
	{
		ch=fgetc(fps);
		if(ch==EOF)
		{
			break;
		}
		else
		{
			ch=ch+100;
			fputc(ch, fpt);
		}
	}
	fclose(fps);
	fclose(fpt);
	fps=fopen(arg, "w");
	fpt=fopen("temp.txt", "r");
	while(1)
	{
		ch=fgetc(fpt);
		if(ch==EOF)
		{
			break;
		}
		else
		{
			fputc(ch, fps);
		}
	}
	fclose(fps);
	fclose(fpt);
  return 1;
}
int decrypt(char arg[]){
char ch, choice;
	FILE *fps, *fpt;

	fps=fopen(arg, "w");
	fpt=fopen("temp.txt", "r");
	while(1)
	{
		ch=fgetc(fpt);
		if(ch==EOF)
		{
			break;
		}
		else
		{
			ch=ch-100;
			fputc(ch, fps);
		}
	}
	fclose(fps);
	fclose(fpt);
  return 1;
}
int display(char arg[]){
   int pipefd[2];
   char buff[10024];
   int childpid;
   int size;
   FILE *file;
   if (pipe(pipefd) < 0) {
       perror("can't open pipe\n");
   }
   if ((childpid = fork()) == 0) {
      sleep(1);
      size = read(pipefd[0], buff, sizeof(buff));
      close(pipefd[0]);
      file = fopen(buff, "r");
      if (file == NULL) {
         write(pipefd[1], "Can't open file", 15);
         exit(1);
      }
      unsigned count=0;
        while (!feof(file) && count < sizeof(buff))
        {
         buff[count++]=fgetc(file);
        if (feof(file)) 
           {
                buff[--count]=0;
           }
        else
        {
         buff[sizeof(buff)-1]=0;    
        }
        }
       write(pipefd[1], buff, strlen(buff));
             close(pipefd[1]);
            _exit(EXIT_SUCCESS); 
   } else if (childpid > 0) {
      size = strlen(arg);
      if (write(pipefd[1], arg, size) != size) {
         perror("Error writing to pipe\n");
      }
      close(pipefd[1]);
      wait(NULL);
      while ((size = read(pipefd[0], buff, sizeof(buff))) > 0) {
         write(1, buff, size);
      }
     close(pipefd[0]);
     exit(EXIT_SUCCESS);
   }
}
