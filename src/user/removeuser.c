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

Description: Remove User

----------------------------------------------------------------------------------------
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pwd.h>
#include <time.h>
#include <sys/types.h>
#include <ncurses.h>
#include <sys/wait.h>

/* My Includes */

#include "../include/SMIT.h"

int delUser();


char loginname[256];
int x, y;
int key;


int removeuser(void)
{
	
	
	/* Declarations */
	
	WINDOW *rmudlg; /* Prompt Username Window */
	

	rmudlg = newwin(6,61,6,10); /* User name input dialog */
	box(rmudlg, ACS_VLINE, ACS_HLINE);
	wattron(rmudlg, A_UNDERLINE);
	mvwprintw(rmudlg, 1, 20, "Remove user from system");
	wattroff(rmudlg, A_UNDERLINE);
	
	
	
	echo();    /* Turns on Echo to see the text typed */
	/* Username Prompt */
	mvwprintw(rmudlg, 3, 1,  "Please type in username to remove:");
	mvwprintw(rmudlg, 3, 37, "[______________]");
	wrefresh(rmudlg);

	
	
	/* Show a highlighted Field */
	wattron(rmudlg, A_REVERSE);
	mvwprintw(rmudlg, 3, 37, "[______________]");
	wrefresh(rmudlg);
	mvwgetnstr(rmudlg, 3,38, loginname, 15);
	wattroff(rmudlg, A_REVERSE);
	noecho(); /* Removes Echo */
	

	werase(rmudlg);	
	
	while(1)
	{
		rmudlg = newwin(10,61,6,10);
		box(rmudlg, ACS_VLINE, ACS_HLINE);
		wattron(rmudlg, A_UNDERLINE);
		mvwprintw(rmudlg, 1, 20, "Are you sure");
		wattroff(rmudlg, A_UNDERLINE);
		mvwprintw(rmudlg, 3, 7,  "Are you sure you want to delete");
		mvwprintw(rmudlg, 4, 7, "user %s from the system", loginname);
		wattron(rmudlg,A_BOLD);
		mvwprintw(rmudlg, 6, 7, "Y=Yes	 N=No 	F10=Cancel");
		wattroff(rmudlg,A_BOLD);
		wrefresh(rmudlg);
		
		key = getch();
		switch(key)
		{
			case KEY_F(10):
			return 0;
			break;
			
			case 'n':
			return 0;
			break;
			
			case 'N':
			return 0;
			break;
			
			case 'y':
			delUser();
			return 0;
			break;
			
			case 'Y':
			delUser();
			return 0;
			break;
					
			
		}
	};
		
	
	return 0;
}


int delUser()
{
	
	struct passwd *pw;
	
	if((pw = getpwnam(loginname) == NULL))
	{
		MsgBoxUser(loginname, "Username cannot be removed, does not exist");
		return(1);
	}
	else
	{
		MsgBoxUser(loginname, "Removing User From system");
		
		pid_t pid = fork();
		
		char *argv[] = {"pw", "userdel", loginname, NULL};
		
		if(pid == 0)
		{
			execv("/usr/sbin/pw", argv);
		}
		else
		{
			MsgBoxWaitPid();
			waitpid(pid, NULL, 0);
			
		}
		
		MsgBoxUser(loginname, "Removal of User Complete");
			
	}
		
	
	
	
	
	return 0;
}
