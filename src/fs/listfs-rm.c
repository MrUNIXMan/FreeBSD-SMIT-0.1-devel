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

 * Remade List fs c - Most FreeBSD's Code has b
 * 
-------------------------------------------------------------------------------------------------------------- 
 */
 
#include <sys/param.h>
#include <sys/mount.h>
#include <sys/stat.h>

#include <ctype.h>
#include <err.h>
#include <errno.h>
#include <fstab.h>
#include <paths.h>

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


#include <ncurses.h>
#include "../include/SMIT.h"


#include "../include/SMITextern.h"
#include "../include/fsmntopts.h"
#include "../include/fspathnames.h"
#include "../include/filesystemfuncs.h"

int ListFS = 0; /* 0 = not created while 1 means created.*/

struct statfs *getmountpoint(const char *);
void printmount(const char *);

/* Draws the UI using a pre-made UI */
void drawlistfs()
{
	
		DrawFSDefaultScreen("List Mounted Filesystems");
		attron(A_BOLD);
		mvaddstr(3, 4, "Device");
		
		mvaddstr(3, 26, "Mount Directory");
		
		mvaddstr(3, 60, "Filesystem Type");
		attroff(A_BOLD);
		refresh();
		
		if(ListFS < 1) {
				wclear(FSPAD);
				counter_FS=15;
				wmove(FSPAD, 15,2);
				listfs();
			}
		else 	{
				prefresh(FSPAD, 15, 1, 5, 3, 14, 74);
			}
	
}

/* Main function of show mounted disks */

int mntlistmain()
{
	
	int FS_KEY;

	while(1)
	{
		drawlistfs();
		
		FS_KEY = getch();
		switch(FS_KEY)
		{	
			case KEY_F(2):
			ListFS = 0;
			break;
			case KEY_F(10):
			return 0;
			case KEY_DOWN:
				wscrl(FSPAD, 3);
				prefresh(FSPAD, 15, 1, 5, 3, 14, 74);
			break;
			case KEY_UP:
				wscrl(FSPAD, -3);
				prefresh(FSPAD, 15, 1, 5, 3, 14, 74);
			break;
			
		}
	}
return 0;
}


