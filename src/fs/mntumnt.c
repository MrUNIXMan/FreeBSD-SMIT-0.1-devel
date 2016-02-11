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

Description: Mount and Unmount stuff

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
#include <sys/wait.h>


#include "../include/filesystemfuncs.h"
#include "../include/SMIT.h"

WINDOW *MNTEdit;


int CommenceMount();
int Mountdisk();
int Unmount_Fs();

char Umountbuf[256];
char UmountedName[256];

	
struct FstabFields mountfields;

void DrawUMountUI()
{
		MNTEdit = newwin(8, 52, 4, 20);
		keypad(MNTEdit, TRUE);
		box(MNTEdit, ACS_VLINE, ACS_HLINE);
		wattron(MNTEdit, A_BOLD);
		mvwprintw(MNTEdit,1, 15, "Unmount a filesystem");
		mvwaddstr(MNTEdit,3, 2, "Type a mount point or device to umount ");
		wattroff(MNTEdit, A_BOLD);
		mvwaddstr(MNTEdit,5, 2, "[_____________________________________]");
		/* Window Refresh */
		wrefresh(MNTEdit);
		echo();
		wattron(MNTEdit, A_REVERSE);
		mvwaddstr(MNTEdit,5, 2, "[_____________________________________]");
		
		mvwgetnstr(MNTEdit, 5,3, Umountbuf, 30);
		wattroff(MNTEdit, A_REVERSE);
		noecho();
				
	
}

void DrawMountUI()
{
		MNTEdit =  newwin(16, 52, 3, 3);
		keypad(MNTEdit, TRUE);
		box(MNTEdit, ACS_VLINE, ACS_HLINE);
		
		/* Draw the Face */
		wattron(MNTEdit, A_BOLD);
		mvwprintw(MNTEdit,1, 15, "Mount a filesystem");
		mvwaddstr(MNTEdit,3, 2, "Device Name:");
		mvwaddstr(MNTEdit,4, 2, "Mount Point:");
		mvwaddstr(MNTEdit,5, 2, "Filesystem Type:");
		mvwaddstr(MNTEdit,6, 2, "Options:");
		
		
		wattroff(MNTEdit, A_BOLD);
		
		mvwaddstr(MNTEdit,3, 22, "[_________________________]");
		mvwaddstr(MNTEdit,4, 22, "[_________________________]");
		mvwaddstr(MNTEdit,5, 22, "[_________________________]");
		mvwaddstr(MNTEdit,6, 22, "[_________________________]");
		
		/* Fields  */
		mvwprintw(MNTEdit,3,23, "%s", mountfields.Device);
		mvwprintw(MNTEdit,4,23, "%s", mountfields.MntDir);
		mvwprintw(MNTEdit,5,23, "%s", mountfields.Fstyp);
		mvwprintw(MNTEdit,6,23, "%s", mountfields.Option);
		
		
		mvwaddstr(MNTEdit, 10, 2, "All Fields must be completed");
		
		wattron(MNTEdit, A_BOLD);
		mvwaddstr(MNTEdit, 12, 2, "F1=Help	F2=Device Name	F3=Mount Dir");
		mvwaddstr(MNTEdit, 13, 2, "F4=Fstype 	F9=Mount	F10=Cancel");
		//mvwaddstr(MNTEdit, 14, 2, "F7=Pass	F9=Add		F10=Cancel");
		wattroff(MNTEdit, A_BOLD);
		
		/* Window Refresh */
		wrefresh(MNTEdit);
		
}


int Mountafs()
{
	int MNTEditKey;
	
	while(1)
	{
		DrawMountUI();
		MNTEditKey = wgetch(MNTEdit);
		switch(MNTEditKey)
		{
			/* Help */
			case KEY_F(1):
			//help_func("addtofstab");
			break;
			
			/* Edit Keys */
			case KEY_F(2):  // Device 
			echo();
			wattron(MNTEdit,A_REVERSE);
			mvwprintw(MNTEdit, 3, 22,"[_________________________]");
			mvwgetnstr(MNTEdit, 3,23, fsmgrbuf, 25);
			strcpy(mountfields.Device, fsmgrbuf);
			wattroff(MNTEdit,A_REVERSE);
			noecho();
			
			break;
			
			case KEY_F(3):  // Mount Point
			echo();
			wattron(MNTEdit,A_REVERSE);
			mvwprintw(MNTEdit, 4, 22,"[_________________________]");
			mvwgetnstr(MNTEdit, 4,23, fsmgrbuf, 25);
			strcpy(mountfields.MntDir, fsmgrbuf);
			wattroff(MNTEdit,A_REVERSE);
			noecho();
			
			break;
			
			case KEY_F(4): // Fstype
			echo();
			wattron(MNTEdit,A_REVERSE);
			mvwprintw(MNTEdit, 5, 22,"[_________________________]");
			mvwgetnstr(MNTEdit, 5,23, fsmgrbuf, 25);
			strcpy(mountfields.Fstyp, fsmgrbuf);
			wattroff(MNTEdit,A_REVERSE);
			noecho();
			break;
			
			case KEY_F(5): // Options
			echo();
			wattron(MNTEdit,A_REVERSE);
			mvwprintw(MNTEdit, 6, 22,"[_________________________]");
			mvwgetnstr(MNTEdit, 6,23, fsmgrbuf, 25);
			strcpy(mountfields.Option, fsmgrbuf);
			wattroff(MNTEdit,A_REVERSE);
			noecho();
			
			break;
			
		
			
			case KEY_F(9):
				CommenceMount();
				return 0;
			break;
			
			
			/* Quit */
			case KEY_F(10):
			return 0;
			break;
			
		}
	}
	
	
	
	
	return 0;
}


int CommenceMount()
{
	int QKEY;
	
	while(1)
	{
		MsgBoxQuestion("Do you want to add this to fstab file", "Y/N");
		QKEY = getch();
		switch(QKEY)
		{
			case 'y':
				Mountdisk();
				return 0;
			break;
			
			case 'Y':
				Mountdisk();
				return 0;
			break;
			
			case 'n':
			return 0;
			break;
			
			case 'N':
			return 0;
			break;
		}
	}
		
}

int Mountdisk()
{
		
	return 0;
}
/****************************************************************************************************/

int Unmount_Fs()
{
	
			char msg[256];
			
			DrawUMountUI();
			sprintf(msg, "Unmounting %s", Umountbuf);
			MsgBoxInfoNoPause(msg);
			
			
				
				
				
	return 0;
	
}
