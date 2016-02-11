		
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

 Rewritten mount.c by Vincent
 * All rights reserved.
 * 
 * 
 * Code used from mount.c from FreeBSD mount and was written by BSD.
 * 
 * ReWritten version of list mounted filesystem using Mount as 
 * a way to write this. Mount with no arguments shows mounted filesystem
 * this is an ncurses version to display mounted filesystems.
 * 
 * 
 * 
-------------------------------------------------------------------------------------------------------------- 
 */
 
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

#include <sys/param.h>
#include <sys/mount.h>
#include <sys/stat.h>
#include <sys/wait.h>

#include <ctype.h>
//#include <err.h>
//#include <errno.h>
#include <fstab.h>
#include <paths.h>
#include <pwd.h>
#include <signal.h>
#include <stdint.h>
#include <unistd.h>
#include <libutil.h>

#include "../include/SMIT.h"
#include "../include/SMITextern.h"  // FreeBSD's rewritten extern.h

#include "../include/fsmntopts.h" // FreeBSD's mntopts.h as it is
#include "../include/fspathnames.h" // Re-written pathnames.h
#include "../include/filesystemfuncs.h"


/* Draw Interface is in another file  shared by this and another */

/* Eqiv to main */
int showmountedfs()
{
	
	// To be inplmented. 
	int /* ro , */ mountsize;
	
		      //*mntfromname **vfslist *vfstype
	const char /* *mntpnt, */     **fslist, *fstyp;
	struct fstab *fs;
	
	struct statfs *mountbuffer;
	
	/* Default Filesystem in FreeBSD 
	 * ufs = UNIX filesystem*/
	
	fslist = NULL; 
	fstyp = "ufs";
	
	
	/* Check for Bad Types */
	
	#define BADTYPE(type) \
		(strcmp(type, FSTAB_RO) && \
			strcmp(type, FSTAB_RW) && strcmp(type, FSTAB_RQ));
	
	/* Process Filesystems */
	
	if((mountsize = getmntinfo(&mountbuffer, MNT_NOWAIT)) == 0)
		{
		MsgBoxError("getmntinfo error occurred");
		return(1);
		};
	
	while((fs = getfsent()) != NULL)
	{
		
	//	if (BADTYPE(fs->fs_type)) {
	//		continue; }
	
		if (chkfilesysname(fs->fs_vfstype, fslist))
			 continue; 
			 
			 
		
	
	
	};
	
	
	DrawFSDefaultScreen("Showing Mounted Filesystems");
	
	getch();
	

	
	
	
	return 0;
}




