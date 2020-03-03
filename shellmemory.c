#include<stdlib.h>
#include<string.h>

char* data[1000]={NULL};

int match(char *model, char *var) 
{
int i, len=strlen(var), matchCount=0;
if (model == NULL)
return 0;
else
for(i=0;i<len;i++)
{if (*(model+i) == *(var+i)) 
matchCount++;}

if (matchCount == len)
return 1;
else
return 0;
}

char *extract(char *model) 
{
char token='=';    
char value[1000];  
int i,j, len=strlen(model);
for(i=0;i<len && *(model+i)!=token;i++); 

for(i=i+1,j=0;i<len;i++,j++) 
value[j]=*(model+i);

value[j]='\0';
return strdup(value);
}

int set(char *string, char*var) 
{
int i=0;
for(i=0;i<1000;i++)
{
 if (match(data[i],var)==1) 
 {data[i] = strdup(string);
 return 0;
 }
else
 if (data[i]==NULL) 
 {
 data[i] = strdup(string);
 return 0;
 }
}
return 0;
}

char *get(char *var) {
int i=0;
for(i=0;i<1000;i++)
 if (match(data[i],var)) 
 return extract(data[i]);
return "Varible does not exist";
}
