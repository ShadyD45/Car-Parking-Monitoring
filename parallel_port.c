#include<fcntl.h>
#include<sys/io.h>
#include<stdio.h>

int addr = 0x0378;

read_port(])
{
	int status = open("/dev/ttyS1",O_RDWR);
	ioperm(addr,255,1);
	iopl(status);
	
	outb(addr+2,0x20);
	int data = inb(addr)
	
	printf("\ndata =%d",data);
	close(status);
}
