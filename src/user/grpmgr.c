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

Description: Group Manager

----------------------------------------------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <grp.h>


#include "../include/SMIT.h"

#define EST_MAX_USERS 250

WINDOW *GroupPad;
int MaxGroups; /* Shows Max amount of Users on the system */
int GroupNo = 1; /* Starts at 1 */
/*				Max User Limit  Char length */


int GPADCreated = 0;
int newgrlist = 0;
int GRkey;


int listgrctr = 100; /* This is used for pads position */
int y, x;

struct group *grp;

char computer[256];
struct utsname uts; /* Structure of uts from utsname */

int listgroups();

int DrawGroupMgrScreen(int grpitem)
{
	/* Bottom Bar that shows Options */
	char GR_FKEYS1[] = "F1=Help		F2=Refresh		F3=Add Group";
	char GR_FKEYS2[] = "F4=Modify Group	F5=Remove Group		F9=Shell";
	char GR_FKEYS3[] = "F10=Exit		Enter=Do/Select";
	
	/* Attempt to Select usernames */
	//int UserCounter = 0;
	
	int begy = 5, begx = 3 ;
	

	
	clear();
	getmaxyx(stdscr, y, x);
	box(stdscr, ACS_VLINE, ACS_HLINE);
	
	
	attron(A_BOLD);
	
	mvprintw(4,	5, "Group Name");
	mvprintw(4, 25, "Group ID");
	/*mvprintw(4, 25, "GID");
	mvprintw(4, 38, "Comment"); */
	mvaddstr(y-4, 2, GR_FKEYS1);
	mvaddstr(y-3, 2, GR_FKEYS2);
	mvaddstr(y-2, 2, GR_FKEYS3);
	attroff(A_BOLD);
	
	SPARE = newwin(y-10, x-2, begy, 1);
	box(SPARE, '|', '-'); 
	
	
	
	
	refresh();
	wrefresh(SPARE);
	
	
	if(GPADCreated < 1)
	{
		GroupPad = newpad(500, x-5);
		if (GroupPad == NULL)
			{
			MsgBoxError("Unable to create pad");
			return (1);
			};
		scrollok(GroupPad, TRUE);
		GPADCreated = 1;
	}
	else
	{
	  prefresh(GroupPad, 100, 	 0,    begy+1,  begx,	  y-7, 	   x-5);
		
	}
	
		
	
	
	
	refresh();

	 /* List users in to box */
	listgroups();
	attron(A_BOLD);
	mvprintw(2, 2, "Total Groups on %s: %d", computer, MaxGroups);
	attroff(A_BOLD);
	
	refresh();
	
	/*				  Origin  			Destination & Size 
	 * 	Padname,  PMinRow, PMinCol, sminrow,  smincol, 	 smaxrow,  smaxcol  */ 
	
	//prefresh(UserPad, 100,  1, 		   3,  2,	        110, 80);
	prefresh(GroupPad, 100, 	 0,    begy+1,  begx,	  y-7, 	   x-5);
	
	return 0;
}

int listgroups()
{
	
	if(newgrlist < 1)
	{
	 GroupNo = 1; /* Reset it */
	 wclear(GroupPad);
	
	setgrent();  // Want to use group file
	
	while(( grp = getgrent() )) {
		(void)mvwprintw(GroupPad, listgrctr, 2, "%s", grp->gr_name);
		(void)mvwprintw(GroupPad, listgrctr, 23, "%d", grp->gr_gid);
		//(void)mvwprintw(GroupPad, listgrctr, 23, "%u", grp->gr_mem);
		
			
			
			wmove(GroupPad, listgrctr++, 2);
			GroupNo++;
			
			prefresh(GroupPad, 100, 	 0,    5+1,  3,	  y-7, 	   x-5);
		}
	newgrlist = 1; /* to Prevent from re-doing the list on a pad */
	endgrent();
	
	MaxGroups = GroupNo;
	
	}
	
	else {
		/* Just Refresh the Pad no need to rewrite the list */
		prefresh(GroupPad, 100, 	 0,    5+1,  3,	  y-7, 	   x-5);
	}
	
	return 0;
}


int GroupMgr()
{
	/* User mgr Key */
	
	if(gethostname(computer, 255) !=0 || uname(&uts) < 0)
	{
		MsgBoxError("Unable to get hostname information");
	}
	
	
	int GroupMgrItem = 0;
	keypad(stdscr, TRUE);
	noecho();
	
	while(1)
	{
		DrawGroupMgrScreen(GroupMgrItem);
		
		do
		{
			GRkey = getch();
			switch(GRkey)
			{
				case KEY_F(2):
					listgrctr = 100;
					newgrlist = 0;
					break;
				case KEY_F(3):
					useradd();
					break;
				case KEY_F(10):
					return 0;
				break;;
				
				case KEY_DOWN:
					wscrl(GroupPad, 3);
					//mvprintw(1, x/2, "Username: %s", usernames[UserNo++]);
					
				break;;
				
				case KEY_UP:
					wscrl(GroupPad, -3);
				break;;
				
				
			};
			DrawGroupMgrScreen(GroupMgrItem);
		} while(GRkey != '\n');
		
		/* Responses */
	
	}; /*End of While */
	
	return 0;
}
