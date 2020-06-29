#include<stdio.h>
#include<stdlib.h>

void read_port(int st[])
{
	int i=0;
	FILE *fp;
	fp=fopen("serial.txt","r");	//fp=fopen("/dev/ttyACM0","r");
	while((st[i]=fgetc(fp)) != '\n')
	{
		if(st[i]==48 || st[i]==49)
		{
			st[i]-=48;
			i++;
		}
	}

	fclose(fp);
}
