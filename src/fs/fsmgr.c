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

Description: Filesystem Manager

----------------------------------------------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <fstab.h>
#include <sys/mount.h>
#include <sys/param.h>


#include "../include/filesystemfuncs.h"
#include "../include/fsvals.h"
#include "../include/SMIT.h"

/* Prototype */
int process_filesystem_lists();
void print_mounted_filesystems(struct statfs *);
void print_fstab_filesystems(struct fstab *);

/* Values used by GetMaxyx */

int SpareY, SpareX;

int IsPadDrawn = 0;  /* 0 means No, 1  means Yes to prevent redrawing when refreshing */


/* Defaults to Viewing Mounted Filesystems although can be changed to view
 * listings from the /etc/fstab file. They will be changed as user
 * selects 2 views. */

int FsMgrViewFStab = 0;
int FsMgrViewMounts = 1;
int FsMgrRelist = 0;

int FS_counter = 15;


/* This user interface will  be different */
int DrawFSMgr(int fsmenuitem)
{
	
	int FSMGRMenuCtr;
	int x, y;
	
	char topmenu[FSMGR_MENU_MAX] [24] = {
											"Fstab","Disk", "View", "Help", "Quit"
										 };
	char FuncKeys1[] = "F1=Help		F2=Redraw	F3=Mount";
	char FuncKeys2[] = "F4=Unmount		F5=Fstab	F6=NULL";
	char FuncKeys3[] = "F9=Shell		F10=Quit	Enter=Do";
										 
	getmaxyx(stdscr, y,x);
	clear();
	box(stdscr, ACS_VLINE, ACS_HLINE);
	mvhline(2, 1, ACS_HLINE, x-2);
	mvvline(1, 42, ACS_VLINE, 1);
	attron(A_BOLD);
	mvprintw(1, 46, "%s Filesystem Manager ", PROGNAME);
	mvaddstr(y-4, 2, FuncKeys1);
	mvaddstr(y-3, 2, FuncKeys2);
	mvaddstr(y-2, 2, FuncKeys3);
	
	attroff(A_BOLD);
	
	SPARE = newwin(y-13, x-2, 5, 1);
	box(SPARE, ACS_VLINE, ACS_HLINE); 
	getmaxyx(SPARE, SpareY, SpareX);
	
	if(IsPadDrawn < 1)
		{
			FSPAD = newpad(250, SpareX-1);
			if(FSPAD == NULL)  {
				MsgBoxError("Unable to create filesystem PAD");
				return(1);
			};
			scrollok(FSPAD, TRUE);
			IsPadDrawn = 1;
			
		}
		
		
		process_filesystem_lists();
	
			
				
	
	
	for(FSMGRMenuCtr = 0; FSMGRMenuCtr < FSMGR_MENU_MAX ; FSMGRMenuCtr++)
	{
		if(FSMGRMenuCtr==fsmenuitem)	
			attron(A_REVERSE);
			mvaddstr(1, 2+(FSMGRMenuCtr*8), topmenu[FSMGRMenuCtr]);
			attroff(A_REVERSE);
	
		
	}
	
	/* Screen Must Be refreshed in reverse starting with the
	 * base screen (Stdscr, then others on top  Similar to Drawing
	 * in CAD */
	 
	refresh();
	wrefresh(SPARE);
	
	prefresh(FSPAD, 15, 1, 6, 3, 14, SpareX-2);
	
	
	return 0;
}

int process_filesystem_lists()
{
	struct statfs *MountBuffer;
	struct fstab *fs;
	
	const char **FileSystemList;
	int MountSize, FileSysCounter,  ReturnValue;
	ReturnValue = 0;
	FileSystemList=NULL;
	
	/* Check Defaults */
	
	/* View Mounted Disks */
	if(FsMgrViewMounts > 0)
		{
			
				
				attron(A_BOLD);
				mvaddstr(4, 2, "Filesystem Node");
				mvaddstr(4, 21, "Mount Directory");
				mvaddstr(4, 46, "Filesystem Type");
				mvaddstr(4, 65, "State");
				attroff(A_BOLD);
				
			if(FsMgrRelist < 1) {
			
				if((MountSize = getmntinfo(&MountBuffer, MNT_NOWAIT)) == 0) {
					MsgBoxError("Error with getmntinfo");
					return(1);
				}
			
				FsMgrRelist = 1;
			
				for(FileSysCounter = 0; FileSysCounter < MountSize; FileSysCounter++) {
					if(chkfilesysname(MountBuffer[FileSysCounter].f_fstypename, FileSystemList))
					continue;
			
					print_mounted_filesystems(&MountBuffer[FileSysCounter]);
				}
				
			} // End of Relist <1 Statment
	}
		
			
			
	/* View Disks listed in /etc/fstab */
	
	if(FsMgrViewFStab > 0) 
		{
			
				attron(A_BOLD);
				mvaddstr(4, 2, "Filesystem Node");
				mvaddstr(4, 21, "Mount Directory");
				mvaddstr(4, 46, "Filesystem Type");
				mvaddstr(4, 65, "List type");
				attroff(A_BOLD);
			if(FsMgrRelist < 1)
			{
			
				setfsent();
			
				while((fs = getfsent()))
				{
					print_fstab_filesystems(fs);
				};
	
				endfsent();
				FsMgrRelist = 1;
			}	
		}	
		
		/* Probley Not Reached */
		
	if(FsMgrViewFStab != 1 && FsMgrViewMounts != 1)
	{
		MsgBoxError("No default Filesystem List option selected");		
		
	}
	
	
	return 0;
}


void print_mounted_filesystems(struct statfs *sfs)
{
	
	mvwprintw(FSPAD, FS_counter, 2,  "%s", sfs->f_mntfromname);
	mvwprintw(FSPAD, FS_counter, 21, "%s", sfs->f_mntonname);
	mvwprintw(FSPAD, FS_counter, 46, "%s", sfs->f_fstypename);
	mvwprintw(FSPAD, FS_counter, 63, "Mounted");
	FS_counter++;
	wmove(FSPAD, FS_counter, 2);
	
	
}

void print_fstab_filesystems(struct fstab *fs)
{
		
	mvwprintw(FSPAD, FS_counter, 2,  "%s", fs->fs_spec);
	mvwprintw(FSPAD, FS_counter, 21, "%s", fs->fs_file);
	mvwprintw(FSPAD, FS_counter, 46, "%s", fs->fs_vfstype);
	mvwprintw(FSPAD, FS_counter, 63, "Fstab Entry");
	FS_counter++;
	wmove(FSPAD, FS_counter, 2);
	
}



int FilesystemManager()
{
	int key;
	int MenuItem=0;
	
	

	while(MenuItem != 4 )
	{	
		DrawFSMgr(MenuItem);
		do {
			key = getch();
			switch(key)
			{
				case KEY_LEFT:
					MenuItem--;
					if(MenuItem < 0) MenuItem = FSMGR_MENU_MAX-1;
				break;
				
				case KEY_RIGHT:
					MenuItem++;
					if(MenuItem > FSMGR_MENU_MAX) MenuItem = 0;
				break;
				
				case KEY_UP:
				wscrl(FSPAD, -3);
					prefresh(FSPAD, 15, 1, 6, 3, SpareY-2, SpareX-2);
				break;
				
				case KEY_DOWN:
				wscrl(FSPAD, 3);
					prefresh(FSPAD, 15, 1, 6, 3, SpareY-2, SpareX-2);
				break;
				
				case KEY_F(2):
					FS_counter = 15;
					FsMgrRelist = 0;

					break;
				case KEY_F(3):
					Mountafs();
					break;
				case KEY_F(4):
					Unmount_Fs();
					break;
				case KEY_F(5):
					AddtoFstab();
					break;
			
				case KEY_F(10):
				return 0;
				break;
			}
			DrawFSMgr(MenuItem);
		} while(key != '\n');
		/* Menu Options */
		 if(MenuItem == 0)			/* Fstab Menu */
		 {
			 showFstabMenu();
			 
		 }
		 
		 else if(MenuItem == 1)		/* Disk Menu */
		 {
			 ShowDiskMenu();
		 }
		 
		 else if(MenuItem == 2)		/* View Menu */
		 {
			 ShowViewMenu();
		 }
		 
		 else if(MenuItem == 4)		/* Help */
		 {
			 
		 }
		
		
	}
	
	
	return 0;
}
