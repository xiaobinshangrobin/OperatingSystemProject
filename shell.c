#include "shellmemory.h"
#include "interpreter.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


void ui()
{
printf("Kernal 1.0 loaded!\n");
printf("Welcome to the Xiaobin Shang shell!\n");
printf("Shell version 2.0 Updated February 2019\n");
}

int parse(char input[])
{
char tmp[200];
char *words[100]={NULL};
int a,b;
int w = 0;

for(a=0; input[a]==' ' && a<1000; a++);

while(input[a] != '\n' && input[a] != '\0' &&  input[a]!='\r' && a<1000)
{
while(input[a]==' ') a++;

for(b=0; input[a] !='\n' && input[a] != '\0'&& input[a]!='\r' && input[a]!=' '&&a<1000; a++,b++)
tmp[b] = input[a];

tmp[b] = '\0';

words[w] = strdup(tmp);
a++;
w++;
}
if (words[0]==NULL)
return 0;


return interpreter(words);

}





