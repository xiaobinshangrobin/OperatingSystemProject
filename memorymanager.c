#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "shell.h"
#include "interpreter.h"
#include "pcb.h"
#include "ram.h"
#include "cpu.h"
#include "kernel.h"
#include "time.h"

struct PCB* pcbTable [10] = {NULL};
char name[1000];

int countTotalPages(FILE*f)
{
char line[1000];
int c = 0;
while(fgets(line,999,f)!=NULL) 
{
c++;
}
fseek(f,0,SEEK_SET);
if(c%4==0)
return (c/4);
else return ((c/4)+1);
}

char* getFileName(FILE* f)
{
if(f!= NULL)
{
int fno = fileno(f);
char temp[1000];
sprintf(temp,"/proc/self/fd/%d",fno);
int i=readlink(temp,name,999);
name[i]='\0';
return name;
}
else return NULL;
}

FILE* findPage(int pageNumber, FILE*f)
{
FILE*fp2 = fopen (getFileName(f),"rt");
char line[1000];
for(int i=0; i<4*pageNumber; i++)
{
fgets(line,999,fp2);
}
return fp2;
}


int findFrame(FILE*page)
{
int i=0;
while(ram[i]!=NULL&&i<10)
{i++;}
if(i>=9 && ram[9]!= NULL)
{return -1;}
else 
return i;
}


int findVictim(struct PCB*p)
{
srand(time(NULL));
int a = rand()%10;
for(int i=0; i<(p->pages_max);i++)
{
if(p->pageTable[i]==a)
{a++;i=0;}
if(a==10)
{a=0;i=0;}  
}
return a;
}


int updateFrame(int frameNumber, int victimFrame, FILE*page)
{
if(frameNumber==-1)
{
  ram[victimFrame]=page;
}
else ram[frameNumber]=page;
return 1;
}


int updatePageTable(struct PCB*p, int pageNumber, int frameNumber, int victimFrame)
{
if(frameNumber==-1)
{
p->pageTable[pageNumber]=victimFrame;
pcbTable[victimFrame]->pageTable[pageNumber]=100;
pcbTable[victimFrame]=p;
}
else 
{
p->pageTable[pageNumber]=frameNumber;
pcbTable[frameNumber]=p;
}
return 1;
}


int launcher(FILE*p, char*name)
{
char command[1000];
sprintf(command,"cp %s BackingStore", name);
system(command);
fclose(p);

system("cd BackingStore");
FILE*q = fopen(name,"rt");
struct PCB* pcb = makePCB(q);
pcb->fileName = name;
if(pcb->pages_max <= 1)
{
int fn = findFrame(findPage(0,q));
int vf;
if(fn==-1) vf = findVictim(pcb);
else vf = 0;
updateFrame(fn, vf, findPage(0,q));
updatePageTable(pcb, 0, fn, vf);
}
else
{
int fn1 = findFrame(findPage(0,q));
int vf1;
if(fn1==-1) 
vf1 = findVictim(pcb);
else vf1 = 0;
updateFrame(fn1, vf1, findPage(0,q));
updatePageTable(pcb, 0, fn1, vf1);

int fn2 = findFrame(findPage(1,q));
int vf2;
if(fn2==-1) 
vf2 = findVictim(pcb);
else vf2 = 0;
updateFrame(fn2, vf2, findPage(1,q));
updatePageTable(pcb, 1, fn2, vf2);
}

addToReady(pcb);
return 1;
}


