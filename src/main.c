#include <curses.h>
#include "create_thread.h"
#include "event.h"

unsigned int left_limit;
unsigned int right_limit;
unsigned int up_limit;
unsigned int down_limit;

plane_t planeMaster;
unsigned int bulletShootedNum;

int keyInput;

/*initialise the boundary of terminal*/
void InitBoundary(void)
{
    left_limit=0;
    right_limit=COLS-1;
    up_limit=0;
    down_limit=LINES-1;
}

/*initialise the curses*/
void InitCurses(void)
{
    
    initscr();
    box(stdscr, ACS_VLINE, ACS_HLINE);
    curs_set(0);
    cbreak();
    nonl();
    noecho();
    intrflush( stdscr, FALSE);
    keypad( stdscr, TRUE );
    refresh();
    
}

int main()
{
    
    InitCurses();
    InitBoundary();
    InitThread(); //create a thread for generating bullets and enemys
   
    InitPlane(&planeMaster,right_limit/2,down_limit-1);
    
    while(1)
    {
        planeMaster.Refresh(&planeMaster);

        keyInput=getch(); //waiting for keyboard input
		
		planeMaster.Erasure(&planeMaster);
         
        switch(keyInput)
        {
            case KEY_LEFT:
                planeMaster.x--;
                if(planeMaster.x<left_limit+2)
                {
                    planeMaster.x=left_limit+2;
                }
                break;
            case KEY_RIGHT:
                planeMaster.x++;
                if(planeMaster.x>right_limit-2)
                {
                    planeMaster.x=right_limit-2;
                }
                break;
            case KEY_UP:
                bulletShootedNum++; 
                break;
        }
          
    }
    
    endwin();
    return 0;
}
