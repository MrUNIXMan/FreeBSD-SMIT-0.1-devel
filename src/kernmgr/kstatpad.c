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

Description: KStat - Shows Kernel Modules Loaded
* Ideas taken from kldstat which was done by Doub Rabson in 1997
* Copyright (c) 1997 Doug Rabson
* 
* It was rewritten using some code to work with SMIT
* 
----------------------------------------------------------------------------------------
*/
#include <sys/cdefs.h>
#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <sys/types.h>
#include <sys/param.h>
#include <sys/module.h>
#include <sys/linker.h>
#include "../include/SMIT.h"
#include "../include/kernel.h"
int count = 15;
int verbose = 0;
int redraw = 0;
int statpad_created = 0;
int y,x;

WINDOW *STATPAD;

void DrawStatScreen()
{
	
	clear();
	getmaxyx(stdscr, y, x);
	attron(A_BOLD);
	mvprintw(1, 23, "View Loaded Kernel Modules");
	
	mvprintw(3, 3,  "ID");
	mvprintw(3, 7,  "Refs");
	mvprintw(3, 14, "Address");
	mvprintw(3, 30, "Size");
	mvprintw(3, 40, "Name");
	attroff(A_BOLD);
	
	DLG = newwin(14, 60, 4, 1);
	box(DLG, '|', '-');
	
	if(statpad_created < 1)
	{
		STATPAD = newpad(50,58);
		scrollok(STATPAD, TRUE);
		prefresh(STATPAD, 15, 1, 6, 3, 14, 58);
		statpad_created = 1;
	}
	else
	{
		prefresh(STATPAD, 15, 1, 6, 3, 14, 58);
		
	}
	
	
	mvprintw(18, 2, "UP/Down Key: Scroll up/down");
	mvprintw(20, 2, "F2=Redraw		F10=Quit");
	
	refresh();
}

/* Code by orignal Author  apart from mvprintw and FileID and other ncurses stuff*/
static void printstats(FileID, verbose)
{
	
		
	struct kld_file_stat stat;
    
    stat.version = sizeof(struct kld_file_stat);
    if (kldstat(FileID, &stat) < 0)
	err(1, "can't stat file id %d", FileID);
    else
	mvwprintw(STATPAD, count, 2, "%2d %4d %p %-8zx %s",stat.id, stat.refs, stat.address, stat.size, 
	       stat.name);
	
	wmove(STATPAD, count, 2);
	count++;
	refresh();
	wrefresh(DLG);
	prefresh(STATPAD, 15, 2, 6, 3, 14, 58);
	
 
	
}

int ShowLoadedKernelModules()
{
		
		int FileID = 0;
		int key;
		
		while(1)
		{
			DrawStatScreen();		
			
			if(redraw < 1)
			{
			wclear(STATPAD);
			for(FileID = kldnext(0); FileID > 0; FileID = kldnext(FileID))
			printstats(FileID, verbose);
			redraw = 1;
			}
			else {
			wrefresh(DLG);
			prefresh(STATPAD, 15, 2, 6, 3, 14, 58);
			}
			
			
		key = getch();
		switch(key)
		{
			case KEY_F(2):
			redraw = 0;
			count = 15;
			break;
			case KEY_F(10):
				return 0;
			break;
			
			case KEY_DOWN:
				wscrl(STATPAD, 3);
				prefresh(STATPAD, 15, 1, 6, 3, 14, 58);
			break;
			case KEY_UP:
				wscrl(STATPAD, -3);
				prefresh(STATPAD, 15, 1, 6, 3, 14, 58);
			break;
			
		}
		
	}	
	
	return 0;
}
