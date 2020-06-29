#include<iostream>
#include<stdio.h>
#include"read_port.c"
#include<ncurses.h>
#include<unistd.h>
using namespace std;


class MyWindow
{			
	public:
			WINDOW *create_newwin(int height, int width, int starty,int startx)
			{	
				WINDOW *local_win;
				local_win = newwin(height, width, starty, startx);
				box(local_win, 0 , 0);		/* 0, 0 gives default characters 
							   	 * for the vertical and horizontal lines
								*/	

				wrefresh(local_win);		/* Show that box 		*/
				
				return local_win;
			}
				
			void slot_color(WINDOW *my_win,int status)	//Colour the specified window representing the parking space
			{
				start_color();
				init_pair(1, COLOR_BLACK, COLOR_GREEN);
				init_pair(2, COLOR_BLACK, COLOR_RED);
				if(status==0){
					wbkgd(my_win,COLOR_PAIR(2));
				}
				else{
					wbkgd(my_win,COLOR_PAIR(1));
				}
				wrefresh(my_win);
			}
			
				 
};



int main()
{

	
	WINDOW *my_win[8];

	initscr();			/* Start curses mode 			*/
	cbreak();			/* Line buffering disabled, Pass on
					 		* every thing to me 	*/
	raw(); 				/* Line buffering disabled      	*/
	keypad(stdscr, TRUE);		/* I need that nifty F1 		*/
	noecho();   			/* Don't echo() while we do getch 	*/

	int height = 5;
	int width = 15;
	int starty = (LINES/8);	/* Calculating for a center placement */
	int startx = (COLS/10);	/* of the window		*/

	refresh();
		
	char ch='/';			
	int n,i;
	int j=0,k=3;
	int x[8],y[8];	
	int b=1,c=1;
	int status[8]={1,1,1,1,1,1,1,1};
	char s[15][15]={"Parking 1","Parking 2","Parking 3","Parking 4","Parking 5","Parking 6","Parking 7","Parking 8"};
	
	cout <<"\nEnter the no. of slots:--> ";
	cin >> n;

	while(1)
	{
		
			
		for(i=0;i<n;i++)
		{
			
			ReadSerialPort(status); // Read the sensor data from the serial port
			if(i<4)
			{
				x[i]=startx*b;	
				y[i]=starty;
				MyWindow w[i];
				if(j<=i)		/* To print the slots only n number of times*/
				{
					my_win[i]= w[i].create_newwin(height, width, y[i], x[i]);
					j=j+1;
					mvwprintw(my_win[i],2,5,"%s",s[i]);				
				}
				w[i].slot_color(my_win[i],status[i]);
				wrefresh(my_win[i]);
				b=b+2;
				
			}
			else
			{
				x[i]=startx*c;	
				y[i]=starty*4;
				MyWindow w[i];
				if(k<i)		/* To print the slots only n number of times */
				{
					my_win[i]= w[i].create_newwin(height, width, y[i], x[i]);
					mvwprintw(my_win[i],2,5,"%s",s[i]);
					k=k+1;
				}				
				w[i].slot_color(my_win[i],status[i]);
				wrefresh(my_win[i]);
				c=c+2;
			}
		}
		
		refresh();		/* To stop the blinking cursor */
		curs_set(0);		/* Make the cursor invisible */
		fflush(stdout);
	}

	getchar();
	endwin(); 			/* End curses mode */

	return 0;
}
