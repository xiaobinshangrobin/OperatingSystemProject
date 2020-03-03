extern struct PCB
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

struct PCB* makePCB (FILE*p);

