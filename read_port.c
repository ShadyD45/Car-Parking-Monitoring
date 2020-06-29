#include<stdio.h>
#include<stdlib.h>

/* This function is used to read the sensor data from the Serial port (USB Port) */
void ReadSerialPort(int st[])
{
	int i=0;
	FILE *fp;
	/*
	  Uncomment only for testing purposes for this funcion
		fopen("serial.txt","r");
	*/
	fp=fopen("/dev/ttyACM0","r");	//The file ttyACM0,ttyACM1...ttyACMx stores the data received from the sensors
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
