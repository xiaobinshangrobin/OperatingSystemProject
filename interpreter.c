
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "shell.h"
#include "shellmemory.h"
#include "pcb.h"
#include "cpu.h"
#include "ram.h"
#include "kernel.h"
#include "memorymanager.h"


int exec(char* a, char* b, char* c)
{
FILE* x = fopen(a, "rt");
if(x == NULL)
{
printf("Script %s not found\n",a);
}
else {launcher(x,a);}

if(b != NULL)
{ 

FILE* y = fopen(b, "rt");
if(y == NULL)
{
printf("Script %s not found\n",b);
}
else 
{

 launcher(y,b);
 
}
}

if(c != NULL)
{

FILE* z = fopen(c, "rt");
if(z == NULL)
{
printf("Script %s not found\n",c);
}
else
 {launcher(z,c);}
}


return scheduler();
}


int run2 (FILE* file)
{
char line[1000];
int errCode = 0;

while(fgets(line,999,file)!=NULL) 
{
errCode = parse(line);
 if (errCode == 1) 
 {
  fclose(file);
  return 1;
 }

}
fclose(file);
return 0;

}


int interpreter(char *words [])
{
int errorCode = 0;
char a[100];

if(strcmp(words[0],"help")==0 && (words[1]==NULL))
{printf("help: Displays all the commands\nquit: Exits / terminates the shell with “Bye!”\nset VAR STRING: Assigns a value to shell memory\nprint VAR: Prints the STRING assigned to VAR\nrun SCRIPT.TXT: executes the file SCRIPT.TXT\n");
}

else if(strcmp(words[0],"quit")==0 && (words[1]==NULL))
{printf("Bye!\n"); 
return 1;
}

else if (strcmp(words[0],"set")==0 &&(words[1]!=NULL)&&(words[2]!=NULL)&&(words[3]==NULL))
{strcpy(a, words[1]); 
strcat(a,"="); 
strcat(a,words[2]); 
set(a, words[1]);
}

else if (strcmp(words[0],"print")==0 &&(words[1]!=NULL)&&(words[2]==NULL))
{printf("%s\n",get(words[1]));
}

else if (strcmp(words[0],"run")==0 &&(words[1]!=NULL)&&(words[2]==NULL))
{FILE *file = fopen(words[1],"rt");
if (file == NULL)
{
printf("Script not found\n");
return 0;
}
else return run2(file);
}
else if(strcmp(words[0],"exec")==0 &&(words[1]!=NULL) && (words[4]==NULL))
{
return exec(words[1],words[2],words[3]);
}

else printf("Unknown command\n");
return errorCode;

}







