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

Description: Add User Module

----------------------------------------------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pwd.h>
#include <string.h>
#include <ncurses.h>
#include <sys/wait.h>
#include "../include/SMIT.h"
#include "../include/users.h"

void add_user_screen();
int execute_pw();

/* Screen Size Storers when getmaxyx is used */
int x, y;
char userinfobuf[256]; /* Buffer */
int AddUserKey;

int unamefield = 0;
int uidfield = 0;
int gidfield = 0;

WINDOW *adduserconfirm;

struct users_info ui;

void DrawAddUserScreen()
{
	getmaxyx(stdscr, y, x);
	
	
	clear();
	box(stdscr, ACS_VLINE, ACS_HLINE);
	curs_set(0);
	attron(A_BOLD);
	mvaddstr(1, 27, AddUserTitle);
	mvaddstr(3, 2, SubMesg);
	
	mvaddstr(y-5, 2, AddUserFKEY1);
	mvaddstr(y-4, 2, AddUserFKEY2);
	mvaddstr(y-3, 2, AddUserFKEY3);
	mvaddstr(y-2, 2, AddUserFKEY4);
	attroff(A_BOLD);
	
	/* Draw the Fields */
	
	mvprintw(6,35, "[Entry Fields]");
	attron(A_BOLD);
	mvprintw(8,10,	"Username:");
	mvprintw(9,10,	"Comment:");
	mvprintw(10,10,	"User ID (UID):");
	mvprintw(11,10, "Group ID (GID):");
    mvprintw(12,10,	"Login Shell:");
    mvprintw(13,10, "Home Directory:");
    attroff(A_BOLD);
    
    /* Entry Fields */
	
	mvprintw(8,35,	"[_______________________]");
	mvprintw(9,35,	"[_______________________]");
	mvprintw(10,35,	"[_______________________]");
	mvprintw(11,35, "[_______________________]");
    mvprintw(12,35,	"[_______________________]");
    mvprintw(13,35, "[_______________________]");

	/* Data Storage for each fields. UI = User Info
	 * struct users_info found in users.h */

	mvprintw(8,36,	"%s", ui.username);
	mvprintw(9,36,	"%s", ui.gecos);
	mvprintw(10,36,	"%s", ui.user_id);	
	mvprintw(11,36,	"%s", ui.group_id);
	mvprintw(12,36, "%s", ui.shell);
	mvprintw(13,36, "%s", ui.homedir);
			
	refresh();
}

int useradd()
{
	noecho();
	keypad(stdscr, TRUE);
	
	
	while(1) {
		DrawAddUserScreen();
	
			AddUserKey = getch();
			switch(AddUserKey)
			{
				/* Help */
				case KEY_F(1):
				break;
				
				/* Reset Fields */
				case KEY_F(2):
				sprintf(ui.username, "_");
				sprintf(ui.gecos, "_");
				sprintf(ui.user_id, "_");
				sprintf(ui.group_id, "_");
				sprintf(ui.shell, "_");
				sprintf(ui.homedir, "_");
				break;
				
				/* Username */
				case KEY_F(3):
				echo();
				attron(A_REVERSE);
				mvprintw(8,35,	"[_______________________]");
				mvwgetnstr(stdscr, 8,36, userinfobuf, 15);
				
				strcpy(ui.username, userinfobuf);
				attroff(A_REVERSE);
				noecho();
				unamefield = 1;
				break;
				
				/* User Comment/Gecos */
				case KEY_F(4):
				echo();
				attron(A_REVERSE);
				mvprintw(9,35,	"[_______________________]");
				mvwgetnstr(stdscr, 9,36, userinfobuf, 20);
				
				strcpy(ui.gecos, userinfobuf);
				attroff(A_REVERSE);
				noecho();
				break;
				
				/* User ID*/
				case KEY_F(5):
				echo();
				attron(A_REVERSE);
				mvprintw(10,35,	"[_______________________]");
				mvwgetnstr(stdscr, 10,36, userinfobuf, 20);
				
				strcpy(ui.user_id, userinfobuf);
				attroff(A_REVERSE);
				noecho();
				uidfield = 1;
				break;
				
				/* Group ID*/
				case KEY_F(6):
				echo();
				attron(A_REVERSE);
				mvprintw(11,35,	"[_______________________]");
				mvwgetnstr(stdscr, 11,36, userinfobuf, 20);
				
				strcpy(ui.group_id, userinfobuf);
				attroff(A_REVERSE);
				noecho();
				gidfield = 1;
				break;
				
				
				/* Login Shell */
				case KEY_F(7):
				echo();
				attron(A_REVERSE);
				mvprintw(12,35,	"[_______________________]");
				mvwgetnstr(stdscr, 12,36, userinfobuf, 23);
				
				strcpy(ui.shell, userinfobuf);
				attroff(A_REVERSE);
				noecho();
				break;
				
				/* Home Dir */
				case KEY_F(8):
				echo();
				attron(A_REVERSE);
				mvprintw(13,35,	"[_______________________]");
				mvwgetnstr(stdscr, 13,36, userinfobuf, 23);
				
				strcpy(ui.homedir, userinfobuf);
				attroff(A_REVERSE);
				noecho();
				break;
				
				case KEY_F(9):
					execute_default_shell();
				break;
				
				/* Quit */
				case KEY_F(10):
				return 0;
				break;
				
				/* Commence Add */
				
				case KEY_F(11):
					add_user();
				break;
				
			};
		};
		
		
		
	
	
	return 0;
}


int add_user()
{
		int AUKEY;
		
		while(1) {	
				add_user_screen();
					do {
						AUKEY = wgetch(adduserconfirm);
						switch(AUKEY)
						{
							case 'Y':
							  execute_pw();
							  return 0;
							break;
							case 'y':
								execute_pw();
								return 0;
							break;
							case 'N':
							return 0;
							break;
							case 'n':
							return 0;
							break;
						}
						add_user_screen();
					} while(AUKEY != 'n');
							
			};
	
	return 0;
}


void add_user_screen()
{

	
	adduserconfirm = newwin(14, 55, 3,13);
	box(adduserconfirm, ACS_VLINE, ACS_HLINE);
	
	wattron(adduserconfirm, A_BOLD);
	mvwaddstr(adduserconfirm,1, 15,  "Add User?");
	
	mvwaddstr(adduserconfirm, 3, 2, "Username:");
	mvwaddstr(adduserconfirm, 4, 2, "User ID:");
	mvwaddstr(adduserconfirm, 5, 2, "Group ID:");
	mvwaddstr(adduserconfirm, 6, 2, "Default Shell:");
	mvwaddstr(adduserconfirm, 7, 2, "Home directory:");
	mvwaddstr(adduserconfirm, 8, 2, "Comment/Gecos:");
	
	mvwaddstr(adduserconfirm, 10,2, "Press (Y)es or (N)o");
	mvwaddstr(adduserconfirm, 11,2, "UID and GID is not implented so it will not work yet");
	
	wattroff(adduserconfirm, A_BOLD);
	
	mvwprintw(adduserconfirm, 3, 25, "%s", ui.username);
	mvwprintw(adduserconfirm, 4, 25, "%s", ui.user_id);
	mvwprintw(adduserconfirm, 5, 25, "%s", ui.group_id);
	mvwprintw(adduserconfirm, 6, 25, "%s", ui.shell);
	mvwprintw(adduserconfirm, 7, 25, "%s", ui.homedir);
	mvwprintw(adduserconfirm, 8, 25, "%s", ui.gecos);
	

	
	wrefresh(adduserconfirm);

}

int execute_pw()
{
	
	/* This will only work with this setting as char argv does not get seen by execv when declared inside an if statment 
	 * I learned that UID and GID are not a requirment*/
	
			
/********************************************************************************************************************/
	
	char *argv[] = {"pw", "useradd", ui.username, "-m",  "-c", ui.gecos, "-s", ui.shell, "-d", ui.homedir, NULL};	
						
				
/********************************************************************************************************************/				
	/* Fork the Process */
	
		MsgBoxUser(ui.username, "Adding User");
	
	pid_t pid = fork();
	
		if(pid == 0)
		{
			execv("/usr/sbin/pw", argv);
		}
		else
		{
			MsgBoxWaitPid();
			waitpid(pid, NULL, 0);
		}
	
		MsgBoxUser(ui.username, "Adding User Complete");
	

	/* Reset the Fields */
	unamefield = 0;
	uidfield = 0;
	gidfield = 0;
	
	return 0;
}

