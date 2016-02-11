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

Description: User Manager

----------------------------------------------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <pwd.h>


#include "../include/SMIT.h"

#define EST_MAX_USERS 250

WINDOW *UserPad;
int MaxUsers; /* Shows Max amount of Users on the system */
int UserNo = 1; /* Starts at 1 */
/*				Max User Limit  Char length */
//char *usernames[EST_MAX_USERS] [12] = { {NULL} };

char *usernames[EST_MAX_USERS];


int PADCreated = 0;
int newlist = 0;
int UMkey;


int listctr = 100; /* This is used for pads position */
int y, x;

struct passwd *pw;

char computer[256];
struct utsname uts; /* Structure of uts from utsname */

int listusers();

int DrawUserMgrScreen(int useritem)
{
	/* Bottom Bar that shows Options */
	char UM_FKEYS1[] = "F1=Help		F2=Refresh		F3=Add User";
	char UM_FKEYS2[] = "F4=Modify User	F5=Remove User		F9=Shell";
	char UM_FKEYS3[] = "F10=Exit		Enter=Do/Select";
	
	/* Attempt to Select usernames */
	//int UserCounter = 0;
	
	int begy = 5, begx = 3 ;
	

	
	clear();
	getmaxyx(stdscr, y, x);
	box(stdscr, ACS_VLINE, ACS_HLINE);
	
	
	attron(A_BOLD);
	
	mvprintw(4,	5, "User");
	mvprintw(4, 18, "UID");
	mvprintw(4, 25, "GID");
	mvprintw(4, 38, "Comment");
	mvaddstr(y-4, 2, UM_FKEYS1);
	mvaddstr(y-3, 2, UM_FKEYS2);
	mvaddstr(y-2, 2, UM_FKEYS3);
	attroff(A_BOLD);
	
	SPARE = newwin(y-10, x-2, begy, 1);
	box(SPARE, '|', '-'); 
	
	
	
	
	refresh();
	wrefresh(SPARE);
	
	
	if(PADCreated < 1)
	{
		UserPad = newpad(1000, x-5);
		if (UserPad == NULL)
			{
			MsgBoxError("Unable to create pad");
			return (1);
			};
		scrollok(UserPad, TRUE);
		PADCreated = 1;
	}
	else
	{
	  prefresh(UserPad, 100, 	 0,    begy+1,  begx,	  y-7, 	   x-5);
		
	}
	
		
	
	
	
	refresh();

	 /* List users in to box */
	listusers();
	attron(A_BOLD);
	mvprintw(2, 2, "Total Users on %s: %d", computer, MaxUsers);
	attroff(A_BOLD);
	
	refresh();
	
	/*				  Origin  			Destination & Size 
	 * 	Padname,  PMinRow, PMinCol, sminrow,  smincol, 	 smaxrow,  smaxcol  */ 
	
	//prefresh(UserPad, 100,  1, 		   3,  2,	        110, 80);
	prefresh(UserPad, 100, 	 0,    begy+1,  begx,	  y-7, 	   x-5);
	
	return 0;
}

int listusers()
{
	
	if(newlist < 1)
	{
	 UserNo = 1; /* Reset it */
	 wclear(UserPad);
	
	setpwent();  // Want to use passwd
	
	while(( pw = getpwent() )) {
		(void)mvwprintw(UserPad, listctr, 2, "%s", pw->pw_name);
		(void)mvwprintw(UserPad, listctr, 16, "%d", pw->pw_uid);
		(void)mvwprintw(UserPad, listctr, 23, "%d", pw->pw_gid);
		(void)mvwprintw(UserPad, listctr, 35, "%s", pw->pw_gecos);
			
			
			wmove(UserPad, listctr++, 2);
			UserNo++;
			
			prefresh(UserPad, 100, 	 0,    5+1,  3,	  y-7, 	   x-5);
		}
	newlist = 1; /* to Prevent from re-doing the list on a pad */
	endpwent();
	
	MaxUsers = UserNo;
	
	}
	
	else {
		/* Just Refresh the Pad no need to rewrite the list */
		prefresh(UserPad, 100, 	 0,    5+1,  3,	  y-7, 	   x-5);
	}
	
	return 0;
}


int UserMgr()
{
	/* User mgr Key */
	
	if(gethostname(computer, 255) !=0 || uname(&uts) < 0)
	{
		MsgBoxError("Unable to get hostname information");
	}
	
	
	int UserMgrItem = 0;
	keypad(stdscr, TRUE);
	noecho();
	
	while(1)
	{
		DrawUserMgrScreen(UserMgrItem);
		
		do
		{
			UMkey = getch();
			switch(UMkey)
			{
				case KEY_F(2):
					listctr = 100;
					newlist = 0;
					break;
				case KEY_F(3):
					useradd();
					listctr = 100;
					 newlist = 0;
					break;
				case KEY_F(5):
					 removeuser();
					 listctr = 100;
					 newlist = 0;
					break;
				case KEY_F(9):
				   execute_default_shell();
				   break;
				case KEY_F(10):
					return 0;
				break;;
				
				case KEY_DOWN:
					wscrl(UserPad, 3);
					mvprintw(1, x/2, "Username: %s", usernames[UserNo++]);
					
				break;;
				
				case KEY_UP:
					wscrl(UserPad, -3);
				break;;
				
				
			};
			DrawUserMgrScreen(UserMgrItem);
		} while(UMkey != '\n');
		
		/* Responses */
	
	}; /*End of While */
	
	return 0;
}
