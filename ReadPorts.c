#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/io.h>


int addr = 0x0378;	// Address for parallel port on many machines

/* 
    This function is used to read the sensor data from the Serial port (USB Port) 
*/
void ReadSerialPort(int st[])
{
	int i=0;
	FILE *fp;
	/*
	  Uncomment only for testing purposes for this funcion
		fopen("serial.txt","r");
	*/
	fp=fopen("/dev/ttyACM0","r");	// The file ttyACM0,ttyACM1...ttyACMx stores the serial port data received from the sensors
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

/*
 Function is used To read sensor data from the parallel port
*/
void ReadParallelPort()
{
	int status = open("/dev/ttyS1",O_RDWR);
	ioperm(addr,255,1);
	iopl(status);
	
	outb(addr+2,0x20);
	int data = inb(addr)
	
	printf("\ndata =%d",data);
	close(status);
}
