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

Description: List Mounted Filesystem, A Modified version of Mount from FreeBSD.
* Contains code by FreeBSD people.
* 



----------------------------------------------------------------------------------------
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

int listfs();

/* `meta' options */
#define MOUNT_META_OPTION_FSTAB		"fstab"

int ListFS = 0;  /* if Set to 1 then refresh pad */


struct statfs *getmntpt(const char *);

void	prmount(struct statfs *);


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

int
mntlistmain()
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

int listfs()
{

	
	const char  **vfslist, *vfstype;
	struct statfs *mntbuf;
	
	int i, mntsize, rval;

	

	vfslist = NULL;
	vfstype = "ufs";

// Leave there



	rval = 0;
		/* Might be what I want */

		if ((mntsize = getmntinfo(&mntbuf, MNT_NOWAIT)) == 0)
			err(1, "getmntinfo");
			for (i = 0; i < mntsize; i++) {
				if (chkfilesysname(mntbuf[i].f_fstypename,
				    vfslist))
					continue;
				prmount(&mntbuf[i]);
				counter_FS++;
				wmove(FSPAD, counter_FS, 2);
			}

		
		
		counter_FS = 15; // Reset the Counter
		ListFS = 1;		// Prevent from being re-listed
		return (rval);


}


void
prmount(struct statfs *sfp)
{
	
	/* Prints /dev/ada0a on / (ufs - Removed the other part as it is not Necessary */
	
	(void)mvwprintw(FSPAD, counter_FS, 3, "%s", sfp->f_mntfromname);
	(void)mvwprintw(FSPAD, counter_FS, 26, "%s", sfp->f_mntonname);
	(void)mvwprintw(FSPAD, counter_FS, 61, "%s", sfp->f_fstypename);
	prefresh(FSPAD, 15, 1, 5, 3, 14, 74);

	

	
}  
