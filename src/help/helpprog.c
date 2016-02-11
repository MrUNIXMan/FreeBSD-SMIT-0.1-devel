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

Description: FreeBSD-SMIT Help Viewer
This module displays Help.
----------------------------------------------------------------------------------------
*/
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include "../include/help.h"
#include "../include/SMIT.h"



/* Line Position on the Pad */
int linesPosCtr = 250; /* Position on Line 250 on Pad to everything */
int TotalNumOfLines = 0;

/* If Pad is Made then will be set to 1 to skip
 * Pad Creation when screen is refreshed */
int IsPadMade = 0; 

/* Each line for 500 Char Max */
char lines[MAX_CHAR];

char tmphelp[250];
char section[240];



/* This will be using PAD instead of Windows
 * as this will be a larger and take more stuff
 * compared to a Window */
 
WINDOW *HelpPAD;

int keys;
/* This is for GetMaxYX */
int y, x;

int DrawHelpScreen()
{
	getmaxyx(stdscr, y,x);
	
	clear();
	char Title[] = "SMIT Help";
	char Controls[] = "UP: Scroll Up		DOWN: Scroll Down		F2=ReDraw Screen		F10=Quit Help";
	char Controls2[]= "PGDOWN: Down 10	PGUP: Up 10";
	
	box(stdscr, ACS_VLINE, ACS_HLINE);
	attron(A_BOLD);
	mvprintw(1, x/3, "%s: %s", Title, section);
	mvaddstr(y-3, 1, Controls);
	mvaddstr(y-2, 1, Controls2);
	attroff(A_BOLD);
	mvhline(2, 1,ACS_HLINE, x-2);   /* Line for Top */
	mvhline(y-4, 1,ACS_HLINE, x-2); /* Line for Bottom */
	mvprintw(1, x-25, "Total Lines: %d", TotalNumOfLines);
	refresh();
	
	/* Make Pads */
	
	/* Creates a New Pad and Tests it 
	 * They are seen as Virtual Windows 
	 * that allows to be bigger than Window
	 * 										*/
	 
	 if(IsPadMade != 1) {
	
	HelpPAD = newpad(1000, x-3);
		if(HelpPAD == NULL) {
			addstr("Unable to Create Pad"); /* Change to MsgBoxError when part of SMIT */
			getch();
			return(1);
		}
	
	scrollok(HelpPAD, TRUE); /* Turn on Scrolling */
    }

	prefresh(HelpPAD, 250,1,3,2,y-5,x-4);
	
	IsPadMade = 1; /* To Prevent Re-Drawing the Pad */
	
	return 0;
}


int readhelpfile()
{
		
	/* Read the File */
	TotalNumOfLines = 0;   /* Reset Total Line count */
	linesPosCtr = 250;     /* Reset Line position on pad */
	
	FILE *fp = fopen(tmphelp, "r");
	if(fp == NULL)
	{
		MsgBoxError("Failed to open file");
		
		return(1);
	}
	
	while(fgets(lines, 500, fp)) {
		mvwprintw(HelpPAD, linesPosCtr, 2, "%s", lines);
		prefresh(HelpPAD, 250,1,3,2,y-5,x-4);
		++linesPosCtr;
		++TotalNumOfLines;
		
		wmove(HelpPAD, linesPosCtr, 2);
		
	}

	
	

	
	fclose(fp);
	return 0;
}


int help_func(char *help)
{
	/* This Tests the arguments passed after user asks for help*/
	
	if(strcmp(help, "smitmain") == 0 ) {
		sprintf(tmphelp, HELP_PATH MAIN_HELP_FILE);
		strcpy(section, "General");
		
	}
	if(strcmp(help, "kernmgr") == 0 ) {
		sprintf(tmphelp, HELP_PATH KERNEL_MGR_HELP);
		strcpy(section, "Kernel Config Manager");
		
	}
	
	if(strcmp(help, "addtofstab") == 0) {
		sprintf(tmphelp, HELP_PATH ADDTOFSTAB_HELP);
		strcpy(section, "Add to Fstab");
	}
	

	keypad(stdscr,TRUE);
	curs_set(0);
	noecho();
	
	
	/* Draws the Help Screen */
	
	DrawHelpScreen();
	readhelpfile();
	
	while(1) {
	
		
		DrawHelpScreen();
		
		prefresh(HelpPAD, 250,1,3,2,y-5,x-4);
	
	keys = getch();
		switch(keys) {
			case KEY_F(2):
		
				linesPosCtr = 250;
				DrawHelpScreen();
				readhelpfile();
			break;;
			case KEY_F(10):
				IsPadMade = 0;	
				sprintf(tmphelp, " "); /* Reset tmphelp */
				delwin(HelpPAD);	
				return 0;
				break;;
			case KEY_DOWN:
				wscrl(HelpPAD, 3);
				prefresh(HelpPAD, 250,1,3,2,y-5,x-4);
				
			break;
			case KEY_UP:
				wscrl(HelpPAD, -3);
				prefresh(HelpPAD, 250,1,3,2,y-5,x-4);
			break;
			case KEY_PPAGE:
				wscrl(HelpPAD, -10);
				prefresh(HelpPAD, 250,1,3,2,y-5,x-4);
			break;
			case KEY_NPAGE:
				wscrl(HelpPAD, 10);
				prefresh(HelpPAD, 250,1,3,2,y-5,x-4);
			break;
			
				
			
		};
	
	};
	

 IsPadMade = 0;	
 sprintf(tmphelp, " "); /* Reset tmphelp */	
 return 0;
}
	
