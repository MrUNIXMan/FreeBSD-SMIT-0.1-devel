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

Description: FreeBSD-SMIT Loader

This all provide arguments to be passed to SMIT so it loads the relevent parts
of the program.

----------------------------------------------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include <unistd.h>


/* My header files for Smit */

#include "include/SMIT.h"
#include "include/SMITprotos.h"

void usage(void)
{
    printf("Usage: smit/smitty [argument]\n\n");
	printf("Following argument will run part of the program\n");
	printf("\nusermenu - User Menu	\
			\nfsmenu  - Filesystem Menu	\
			\nsysconfig - System config menu	\
			\nusermgr - User Manager	\
			\nfsmgr - Filesystem Manager	\
			\nabout - program info	\
			\nhelp - this screen			\
			\nsoftwaremgr - Software manager menu \
			\nkernelmgr - Kernel Manager\n\n");

}

/* Shows Copyright */

void about(void)
{
	printf("%s Version %s\n%s\n", PROGNAME, VERSION, COPYRIGHT);
	
}

/* Init Curses */

void cursesinit()
{
	initscr();   	/* Init Screen */
	noecho(); 		/* Echo Off */
	keypad(stdscr,TRUE);  /* Enable use of Keypad */
	curs_set(0);		  /*Turn off Cursor */

}

/* Safe Exit */
int clean_exit()
{
	clear();
	refresh();
	endwin();
	
	
	exit(0);
}



int main(int argc, char *argv[])
{
	/* If no arguments are given then load SMIT main menu */
	
    if(argv[1] == NULL)
    {
			cursesinit(); /* Call curses init function */
			startsmit();  /* Not existed yet */
			clean_exit(); /* After leaving SMIT then Exit */
		
	}
	
	if(strcmp(argv[1], "about") == 0)
	{
		about();
		exit(0);
	}
	else if(strcmp(argv[1], "help") == 0)
	{
		usage();
		exit(0);
	}
	
	
	/* NOT REACHED */
	exit(0);
}
