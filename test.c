#include<stdio.h>
#include<string.h>
 
int main(void)
{
    	char a[1000];
    	char aa[1000];
    	char c[] = " ";
 
    	printf("请输入一串字符：");
    	gets(a);
 
    	char *p = strtok(a,c);
    	printf("%s\n",p);
 
    	p = strtok(NULL,c);
 
    	while(p)
    	{
        	printf("%s\n",p);
        	p = strtok(NULL,c); 
    	}
}