
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "shell.h"
#include "interpreter.h"
#include "pcb.h"
#include "ram.h"
#include "kernel.h"
#include "memorymanager.h"


struct CPU
{
FILE*IP;
char IR [1000];
int quanta;
int offset;

} myCPU;// quanta is assigned to 2 in main;

int run ( )
{

for (int i = 0; i<myCPU.quanta; i++)
{

int errCode = 0;
if(fgets(myCPU.IR,999,myCPU.IP)!=NULL) 
{

errCode = parse(myCPU.IR);

myCPU.offset++;
if(myCPU.offset == 4)
{
return 2;//pagefault
}
 if (errCode == 1) 
 {
  return 1;//quit
 }

}
else 
  return 9; //this file completed

}
return 0;
}
