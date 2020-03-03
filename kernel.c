#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "shell.h"
#include "interpreter.h"
#include "pcb.h"
#include "ram.h"
#include "cpu.h"
#include "memorymanager.h"
#include "dirent.h"

FILE* ram [10];
char prompt[100]={'$','\0'};
char userInput[1000];
int errorCode = 0;
struct PCB* head; 
struct PCB* tail;

void addToReady(struct PCB*p)
{
if(head == NULL)
{
 head = p;
 tail = p; 
}
else
{
tail->next = p;
tail = tail->next; 
}
}

void terminates()
{
         struct PCB* temp = head;
         for(int i =0; i<head->pages_max; i++)
         {
          if(head->pageTable[i]!=100&&ram[head->pageTable[i]]!=NULL)
          fclose(ram[head->pageTable[i]]);
          ram[head->pageTable[i]]=NULL;
         }
         if(head->file!=NULL)
         fclose(head->file);
         char command[1000];
         sprintf(command,"BackingStore/%s",head->fileName);
         int s;int d;
         if(head->next!=NULL&&(strcmp(head->fileName,head->next->fileName)==0))
         s=0; else s=1;
         if(head->next!=NULL&&head->next->next!=NULL&&(strcmp(head->fileName,head->next->next->fileName)==0))
         d=0; else d=1;
         if(fopen(command,"r")!=NULL&&s!=0&&d!=0 )
         {
         
         sprintf(command, "rm -r BackingStore/%s",head->fileName);
         system(command);
         }
         head = head->next;
         temp->next = NULL;
         free(temp);
}

int scheduler()
{
while(head != NULL)
{
if(myCPU.quanta==2)
{
myCPU.IP = head->PC;
myCPU.offset = head->PC_offset;
int a = run();
if (a==9)//one program completed
        {
         terminates();
        }
else if (a==1)//quit 
      {
       while (head!=NULL)
       {
        struct PCB* temp = head;
        if(head->file!=NULL)
        fclose(head->file);
        head = head->next;
        free(temp);
        }
       int i = 0;
       while(i<10)
       {if (ram[i]!=NULL)
        fclose(ram[i]);
        ram[i] = NULL;
        i++;}
       return 1;
      }
else  if(a==2)//page fault
      {
       (head->PC_page)++;
        myCPU.offset = 0;
       if((head->PC_page)>=(head->pages_max))
         {terminates(); 
         }
       else if(head->pageTable[head->PC_page]!=100)
         {
          (head->PC)=ram[head->pageTable[head->PC_page]];
          (head->PC_offset)=0;
          tail->next = head;
          head = head->next;
          tail = tail->next;
          tail->next = NULL;
         }
       else {
            int fn = findFrame(findPage(head->PC_page,head->file));
            int vf;
            if(fn==-1) {vf = findVictim(head);}
            else vf = 0;
            updateFrame(fn, vf, findPage(head->PC_page,head->file));
            updatePageTable(head, head->PC_page, fn, vf);
            //(head->PC)=ram[head->pageTable[head->PC_page]];
            head->PC_offset=0;
            tail->next = head;
            head = head->next;
            tail = tail->next;
            tail->next = NULL;
            }
       

      }
else  //task switch
      {head->PC = myCPU.IP;
       head->PC_offset = myCPU.offset;
       tail->next = head;
       head = head->next;
       tail = tail->next;
       tail->next = NULL;
       }
}      
}

int i = 0;//these lines might be useless. They are just to make sure all the
while(i<10)//files are closed and ram is cleared after all programs completed.
{
if (ram[i]!=NULL)
fclose(ram[i]);
ram[i] = NULL;
i++;}

return 0;
}

void boot()
{
for(int i=0; i<10; i++)
ram[i]=NULL;

DIR* dir = opendir("BackingStore");
if(dir)
{
closedir(dir);
system("rm -r BackingStore");
}
system("mkdir BackingStore");
}

int main (int argc, char *argv[])
{
boot();
ui();

myCPU.quanta = 2;
myCPU.offset = 0;
head = NULL;
tail = NULL;

while(1)
{
printf("%s",prompt);
fgets(userInput, 999, stdin);

errorCode = parse(userInput);
if (errorCode == 1) exit(99);

}
}





