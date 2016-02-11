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

 * UI for displaying for list mounted filesystems & show disk spaces  which is designed to share
 * elements.
 * 
-------------------------------------------------------------------------------------------------------------- 
 */
 
 #include <stdio.h>
 #include <stdlib.h>
 #include <ncurses.h>
 #include "../include/SMIT.h"
 #include "../include/filesystemfuncs.h"


//WINDOW *FSPAD; // PAD to display filesystems on

int PADCREATED = 0; // Set to 1 once pad is created 


int y, x; // Used with getmaxyx

int DrawFSDefaultScreen(char *title)
{
	char SCROLLOPT[] = "Up: Scroll Up		Down: Scroll Down";
	char FSUIOPTS1[] = "F1=Help		F2=Refresh		F10=Quit";
	
	/* Clears Screen, Gets vales of X, Y, Enable Keypad
	 * disable echo, draws a box on stdscr, adds a title to screen */
	 
	clear();
	getmaxyx(stdscr, y,x);
	keypad(stdscr, TRUE);
	noecho();
	box(stdscr, ACS_VLINE, ACS_HLINE);
	mvaddstr(1, x/6, title);
	mvaddstr(y-4, 2, SCROLLOPT);
	mvaddstr(y-2, 2, FSUIOPTS1);
	
	
	/* Make Windows, SPARE Window is Windows that has a border
	 * to prevent overwriting on the borders*/
	 
	SPARE = newwin(15, 76, 4, 2);
	box(SPARE, ACS_VLINE, ACS_HLINE);
	
	/*  Creates a PAD (Window that is larger than screen sizes better 
	 *  for scrolling */
	 
	 if(PADCREATED <1) {
		 /* Pad 30 lines x 68 column */
		 FSPAD = newpad(30, 74);
			if(FSPAD == NULL) {
				MsgBoxError("Unable to create Filesystem PAD");
				return(1);
			 };
			 scrollok(FSPAD, TRUE);
			 PADCREATED = 1;
		 }
	 /* else
			{
				prefresh(FSPAD, 15, 1, 4, 3, 14, 39);
			} */
	
	
	refresh();
	wrefresh(SPARE);
	prefresh(FSPAD, 15, 1, 5, 3, 14, 74);
	
	return 0;
}
