#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "shell.h"
#include "interpreter.h"
#include "pcb.h"
#include "cpu.h"
#include "kernel.h"
#include "memorymanager.h"

int addToRAM (FILE*p)
{
int i = 0;
while(ram[i] != NULL && i < 10)
{
i++;
}

if (i<10)
ram [i] = p;
return i;
}
