#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "shell.h"
#include "interpreter.h"
#include "cpu.h"
#include "ram.h"
#include "kernel.h"
#include "memorymanager.h"


struct PCB 
{
FILE*PC;
FILE*file;
char*fileName;
struct PCB* next;
int pageTable[10];
int PC_page;
int PC_offset;
int pages_max;

}PCB;

struct PCB* makePCB (FILE*p)
{
struct PCB* newPcb = ( struct PCB*) malloc (sizeof (struct PCB));
newPcb->PC = p;
newPcb->file = fopen(getFileName(p),"rt");

for(int i=0; i<10; i++)
{newPcb->pageTable[i]=100;
}
newPcb->next = NULL;
newPcb->PC_page = 0;
newPcb->PC_offset = 0;
newPcb->pages_max = countTotalPages(p);

return newPcb;
}
