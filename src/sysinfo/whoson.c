/*
Copyright (c) 2015, MrUNIXMan
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this
  list of conditions and the following disclaimer.

* Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.

* Neither the name of FreeBSD-SMIT nor the names of its
  contributors may be used to endorse or promote products derived from
  this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
---------------------------------------------------------------------------------------

Description: Rewritten version of the Who Command

Original  Code from FreeBSD's Who command is written by Copyright (c) 2002 Tim J. Robbins.
 * All rights reserved.
 * 
 * The Module has been re-written by MrUNIXMan Nov 24th 2015
 * 
 * Who Commands that Shows inside Curses
-------------------------------------------------------------------------------------------------------------- 
 */



#include <sys/param.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/stat.h>

#include <err.h>
#include <errno.h>
#include <langinfo.h>
#include <limits.h>
#include <locale.h>
#include <paths.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <timeconv.h>
#include <unistd.h>
#include <utmpx.h>

#include <ncurses.h>

#include "../include/SMIT.h"

/* Prototypes */
static void output(const struct utmpx *UT);
static int TTY_Stats(char *line);
static void Process_Users_in_UTMP(void);


/* Pad for the Who Window  just incase it has longer lists to permit
 * scrolling */
WINDOW *WhoPad;

static int ctr;
int WhoPadisCreated = 0;

int y, x;


int DrawWhoScreen()
{
	char SHOWKEYS1[] = "F1=Help		F2=Redraw		F10=Quit";
	char SHOWKEYS2[] = "UP: Scroll up		Down: Scroll Down";
	
	
	clear();
	getmaxyx(stdscr, y,x);
	box(stdscr, ACS_VLINE, ACS_HLINE);
	attron(A_BOLD);
	mvprintw(1, x/5, "View logged in Users on this system");
	mvprintw(3, 4, "Name");
	mvprintw(3, 23, "Line");
	mvprintw(3, 33, "Location");
	mvaddstr(y-3,2, SHOWKEYS1);
	mvaddstr(y-2,2, SHOWKEYS2);
	attroff(A_BOLD);
	
	refresh();
	
	SPARE = newwin(15,58,4,2);
	box(SPARE, ACS_VLINE, ACS_HLINE);
	wrefresh(SPARE);
	
	
	if(WhoPadisCreated < 1) {
		WhoPad = newpad(50, 54);
		
			if(WhoPad == NULL) {
				MsgBoxError("Unable to Create Pad for Who");
				return(1);
			}
			/* Prevents Recreating the Pad on refresh */
		  
		  scrollok(WhoPad, TRUE);
		  WhoPadisCreated = 1;
		  
		}
	else
		{
			prefresh(WhoPad, 21, 1,5,3,15,50);
		}
	
	prefresh(WhoPad, 21, 1,5,3,15,50);
	return 0;
}

int ShowLoggedUsers()
{
	int key;
	ctr = 20;
	curs_set(0);
	setlocale(LC_TIME, "");
	
	while(1) {
			DrawWhoScreen();
			Process_Users_in_UTMP();
			key = getch();
			switch(key)
			{
				case KEY_UP:
				wscrl(WhoPad, -2);
				break;
				case KEY_DOWN:
				wscrl(WhoPad, 2);
				break;
				case KEY_F(1):
				break;
				case KEY_F(2):
				DrawWhoScreen();
				Process_Users_in_UTMP();
				break;
				
				case KEY_F(10):
				endutxent();
				return(0);
				break;	
				
				
			};
			
		};
	
	
	endutxent();
	return 0;
}

/* These codes are modified after looking at the WHO command */

static void output(const struct utmpx *UT)
{
	
	mvwprintw(WhoPad,ctr, 2, UT->ut_user);	
	mvwprintw(WhoPad,ctr, 21, UT->ut_line);
	mvwprintw(WhoPad,ctr, 31, UT->ut_host);

	wmove(WhoPad, ctr++, 2);
	prefresh(WhoPad, 21, 1,5,3,15,50);
	
}



static int TTY_Stats(char *line)
{
	struct stat SB;
	/* tty buffer for use with snprintf */
	char ttybuffer[MAXPATHLEN];
	
	(void)snprintf(ttybuffer, sizeof(ttybuffer), "%s%s", _PATH_DEV, line);
	/* Check if OK */
		if(stat(ttybuffer, &SB) == 0) {
			return(0); 
			}
		else
			return(-1);
}

static void Process_Users_in_UTMP(void)
{

	struct utmpx *UTX;
	
	while((UTX = getutxent()) != NULL) {
		if(TTY_Stats(UTX->ut_line) == 0)
		output(UTX);
		};
		
}
