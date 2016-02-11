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

 Rewritten df.c by Vincent
 * All rights reserved.
 * 
 * 
 * Code used from df.c from FreeBSD df and was written by BSD.
 * 
 * ReWritten to adapt to my naming as part of learning curve.
 * 
 * This varient of df is found in GNU-Darwin as it still used printf()
 * 
 * 
-------------------------------------------------------------------------------------------------------------- 
 */
 

#include <ncurses.h>
#include <sys/param.h>
#include <sys/stat.h>
#include <sys/mount.h>
#include <sys/sysctl.h>
#include <ufs/ufs/ufsmount.h>
#include <err.h>
#include <libutil.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sysexits.h>
#include <unistd.h>

#include "../include/SMIT.h"
#include "../include/SMITextern.h"  // FreeBSD's rewritten extern.h

#include "../include/fsmntopts.h" // FreeBSD's mntopts.h as it is
#include "../include/fspathnames.h" // Re-written pathnames.h
#include "../include/filesystemfuncs.h" // Filesystem UI functions

//#define UNITS_SI 1
//#define UNIT_2 2

int dfctr; // Counter

/* Max Widths different member names */

struct maxWidths {
	int MountFrom;
	int Total;
	int Used;
	int Available;
	int I_Used;
	int I_Free;
};

/* Prototypes */
void DrawDFUI();
int process_df_disks();
static intmax_t fsbtoblk(int64_t num, uint64_t fsbs, u_long bs);
static int int64width(int64_t value);
static size_t regetmntinfo(struct statfs **mntpbuf, long mountsize, const char **VFSlist);
static void printstat(struct statfs *, struct maxWidths *);
static void update_maxwidths(struct maxWidths *, const struct statfs *);


static __inline int imax(int a, int b)
{
	return (a > b ? a : b); 
}

//static struct ufs_args mountdev;


/* Draw Interface is in another file  shared by this and another */

int List_DF = 0;


void DrawDFUI()
{
	DrawFSDefaultScreen("Showing Disk Spaces");
		attron(A_BOLD);
		mvaddstr(3, 4, "Device");
		
		mvaddstr(3, 18, "Mount Directory");
		
		mvaddstr(3, 43, "1K Blocks	Used  Available");
		attroff(A_BOLD);
		refresh();
		
		if(List_DF < 1) {
				wclear(FSPAD);
				counter_FS=15;
				wmove(FSPAD, 15,2);
				process_df_disks();
				prefresh(FSPAD, 15, 1, 5, 3, 14, 74);
				List_DF = 1;
			}
		else 	{
				prefresh(FSPAD, 15, 1, 5, 3, 14, 74);
			}
				
	
}

int showdiskspace()
{
	int dfkey;
	
	while(1)	{
		DrawDFUI();
		dfkey = getch();
		switch(dfkey)
			{
				case KEY_F(2):
				List_DF = 0;
				break;
				case KEY_F(10):
				return 0;
				break;
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

/* Eqivilent to Main Function on Df.c */

int process_df_disks()
{
	
	//struct stat statbuf;
	struct statfs Totalbuf;
	struct maxWidths maxWidths;
	struct statfs *mountbuf;
	const char *fstyp;
	//char *mountpath,  *mountpoint;
	const char **VFSlist;
	size_t i, mountsize;
	
	int RetVal;
	
	
	
	/* fstyp is name from System V UNIX */
	fstyp = "ufs";
	
	memset(&Totalbuf, 0, sizeof(Totalbuf));
	Totalbuf.f_bsize = DEV_BSIZE;
	strncpy(Totalbuf.f_mntfromname, "total", MNAMELEN);
	VFSlist = NULL;
	
	
	mountsize = getmntinfo(&mountbuf, MNT_NOWAIT);
	bzero(&maxWidths, sizeof(maxWidths));
	for(i = 0; i <mountsize ; i++)
	/* Calls a function */
		update_maxwidths(&maxWidths, &mountbuf[i]);
	
	RetVal=0;
	
	mountsize = regetmntinfo(&mountbuf, mountsize, VFSlist);
	bzero(&maxWidths, sizeof(maxWidths));
	for (i = 0; i <mountsize; i++) {
		update_maxwidths(&maxWidths, &mountbuf[i]);
	}
	
	for(i = 0; i < mountsize; i++)
	 if((mountbuf[i].f_flags & MNT_IGNORE) == 0)
	 printstat(&mountbuf[i], &maxWidths);
	 
	 /* This had getch on the End */
	
	/*******************************************************************************/
	
	return(RetVal);
}

static size_t regetmntinfo(struct statfs **mntpbuf, long mountsize, const char **VFSlist)
{
	int error, i, j;
	
	struct 	statfs *mountbuf;
	
//	if(VFSlist == NULL)
//		return(mountsize : getmountinfo(mntpbuf, MNT_WAIT));
		
	mountbuf = *mntpbuf;
	for (j = 0, i = 0; i < mountsize; i++) {
		if(chkfilesysname(mountbuf[i].f_fstypename, VFSlist))
			continue;
			
			/*
		 * XXX statfs(2) can fail for various reasons. It may be
		 * possible that the user does not have access to the
		 * pathname, if this happens, we will fall back on
		 * "stale" filesystem statistics.
		 */
		 
		 error = statfs(mountbuf[i].f_mntonname, &mountbuf[j]);
			if(i != j) {
				if(error < 0 )
				 MsgBoxWarn("statfs possibly stale");
				 mountbuf[j] = mountbuf[i];
			 }
			 j++;
		 }

	return(j);
}


/*
 * Convert statfs returned file system size into BLOCKSIZE units.
 * Attempts to avoid overflow for large file systems.
 */

static intmax_t fsbtoblk(int64_t num, uint64_t fsbs, u_long bs)
{
	
	if(fsbs != 0 && fsbs < bs)
		return(num / (intmax_t)(bs /fsbs));
	else
		return(num * (intmax_t)(fsbs / bs));
		
}

static int int64width(int64_t value)
{
	int len;
	len = 0;
	
	if(value <= 0) {
		value = -value;
		len++;
	}
	
	while(value > 0) {
		len++;
		value /= 10;
	}
	
	return(len);
}

	
static void printstat(struct statfs *sfsp, struct maxWidths *mwp)
{
	static u_long blocksize;
	static int headerlen, timesthrough = 0;
	static const char *header;
	
	int64_t used, availblocks; // inodes;
	
	if(++timesthrough == 1) {
		header = getbsize(&headerlen, &blocksize);
	}
	
	used = sfsp->f_blocks - sfsp->f_bfree;
	availblocks = sfsp->f_bavail + used;
	
	/* print Devices */	
	(void)mvwprintw(FSPAD, counter_FS, 2, "%-*s", mwp->MountFrom, sfsp->f_mntfromname);
	
	/* Mount Dir */
	
	(void)mvwprintw(FSPAD,counter_FS,16, "%s", sfsp->f_mntonname);
	
	/* Spaces */
	
	(void)mvwprintw(FSPAD, counter_FS, 40, " %*jd %*jd %*jd",
		    mwp->Total, fsbtoblk(sfsp->f_blocks,
		    sfsp->f_bsize, blocksize),
		    mwp->Used, fsbtoblk(used, sfsp->f_bsize, blocksize),
		    mwp->Available, fsbtoblk(sfsp->f_bavail,
		    sfsp->f_bsize, blocksize));  
	
	/* Move Cursor Down */
	wmove(FSPAD, counter_FS++, 2);
	
}


/*
 * Update the maximum field-width information in `mwp' based on
 * the file system specified by `sfsp'.
 */

static void update_maxwidths(struct maxWidths *mwp, const struct statfs *sfsp)
{
	static u_long blocksize = 0;
	int dummy;
	
	if(blocksize == 0)
		getbsize(&dummy, &blocksize);
		
	mwp->MountFrom = imax(mwp->MountFrom, (int)strlen(sfsp->f_mntfromname));
	mwp->Total = imax(mwp->Total, int64width( \
		fsbtoblk((int64_t)sfsp->f_blocks, sfsp->f_bsize, blocksize)));
	
	mwp->Used = imax(mwp->Used,	\
	 int64width(fsbtoblk((int64_t)sfsp->f_blocks - 
	 (int64_t)sfsp->f_bfree, sfsp->f_bsize, blocksize)));
	 
	mwp->Available = imax(mwp->Available, int64width(fsbtoblk(sfsp->f_bavail,sfsp->f_bsize, blocksize)));
	
	mwp->I_Used = imax(mwp->I_Used, int64width((int64_t)sfsp->f_files -
	    sfsp->f_ffree));
	
	mwp->I_Free = imax(mwp->I_Free, int64width(sfsp->f_ffree));
}
