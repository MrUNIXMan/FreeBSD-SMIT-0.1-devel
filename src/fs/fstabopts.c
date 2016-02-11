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

Description: Options from the FStab Menu in the Filesystem Manager

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

WINDOW *FSTABEdit;
FILE *fp;

int CommenceAdd();
int Writetofstab();


char fstab_file[] = "/etc/fstab";
struct FstabFields fstfield;


void DrawAddtoFstab()
{
		FSTABEdit =  newwin(16, 52, 3, 3);
		keypad(FSTABEdit, TRUE);
		box(FSTABEdit, ACS_VLINE, ACS_HLINE);
		
		/* Draw the Face */
		wattron(FSTABEdit, A_BOLD);
		mvwprintw(FSTABEdit,1, 15, "Add to %s", fstab_file);
		mvwaddstr(FSTABEdit,3, 2, "Device Name:");
		mvwaddstr(FSTABEdit,4, 2, "Mount Point:");
		mvwaddstr(FSTABEdit,5, 2, "Filesystem Type:");
		mvwaddstr(FSTABEdit,6, 2, "Options:");
		mvwaddstr(FSTABEdit,7, 2, "Dump:");
		mvwaddstr(FSTABEdit,8, 2, "Pass:");
		
		wattroff(FSTABEdit, A_BOLD);
		
		mvwaddstr(FSTABEdit,3, 22, "[_________________________]");
		mvwaddstr(FSTABEdit,4, 22, "[_________________________]");
		mvwaddstr(FSTABEdit,5, 22, "[_________________________]");
		mvwaddstr(FSTABEdit,6, 22, "[_________________________]");
		mvwaddstr(FSTABEdit,7, 22, "[______]");
		mvwaddstr(FSTABEdit,8, 22, "[______]");
		
		/* Fields  */
		mvwprintw(FSTABEdit,3,23, "%s", fstfield.Device);
		mvwprintw(FSTABEdit,4,23, "%s", fstfield.MntDir);
		mvwprintw(FSTABEdit,5,23, "%s", fstfield.Fstyp);
		mvwprintw(FSTABEdit,6,23, "%s", fstfield.Option);
		mvwprintw(FSTABEdit,7,23, "%s", fstfield.Dump);
		mvwprintw(FSTABEdit,8,23, "%s", fstfield.pass);
		
		mvwaddstr(FSTABEdit, 10, 2, "All Fields must be completed");
		
		wattron(FSTABEdit, A_BOLD);
		mvwaddstr(FSTABEdit, 12, 2, "F1=Help	F2=Device Name	F3=Mount Dir");
		mvwaddstr(FSTABEdit, 13, 2, "F4=Fstype	F5=Options	F6=Dump");
		mvwaddstr(FSTABEdit, 14, 2, "F7=Pass	F9=Add		F10=Cancel");
		wattroff(FSTABEdit, A_BOLD);
		
		/* Window Refresh */
		wrefresh(FSTABEdit);
		
}


int AddtoFstab()
{
	int FstabEditKey;
	
	while(1)
	{
		DrawAddtoFstab();
		FstabEditKey = wgetch(FSTABEdit);
		switch(FstabEditKey)
		{
			/* Help */
			case KEY_F(1):
			help_func("addtofstab");
			break;
			
			/* Edit Keys */
			case KEY_F(2):  // Device 
			echo();
			wattron(FSTABEdit,A_REVERSE);
			mvwprintw(FSTABEdit, 3, 22,"[_________________________]");
			mvwgetnstr(FSTABEdit, 3,23, fsmgrbuf, 25);
			strcpy(fstfield.Device, fsmgrbuf);
			wattroff(FSTABEdit,A_REVERSE);
			noecho();
			
			break;
			
			case KEY_F(3):  // Mount Point
			echo();
			wattron(FSTABEdit,A_REVERSE);
			mvwprintw(FSTABEdit, 4, 22,"[_________________________]");
			mvwgetnstr(FSTABEdit, 4,23, fsmgrbuf, 25);
			strcpy(fstfield.MntDir, fsmgrbuf);
			wattroff(FSTABEdit,A_REVERSE);
			noecho();
			
			break;
			
			case KEY_F(4): // Fstype
			echo();
			wattron(FSTABEdit,A_REVERSE);
			mvwprintw(FSTABEdit, 5, 22,"[_________________________]");
			mvwgetnstr(FSTABEdit, 5,23, fsmgrbuf, 25);
			strcpy(fstfield.Fstyp, fsmgrbuf);
			wattroff(FSTABEdit,A_REVERSE);
			noecho();
			break;
			
			case KEY_F(5): // Options
			echo();
			wattron(FSTABEdit,A_REVERSE);
			mvwprintw(FSTABEdit, 6, 22,"[_________________________]");
			mvwgetnstr(FSTABEdit, 6,23, fsmgrbuf, 25);
			strcpy(fstfield.Option, fsmgrbuf);
			wattroff(FSTABEdit,A_REVERSE);
			noecho();
			
			break;
			
			case KEY_F(6): // Dump
			echo();
			wattron(FSTABEdit,A_REVERSE);
			mvwprintw(FSTABEdit, 7, 22,"[______]");
			mvwgetnstr(FSTABEdit, 7,23, fsmgrbuf, 7);
			strcpy(fstfield.Dump, fsmgrbuf);
			wattroff(FSTABEdit,A_REVERSE);
			noecho();
			break;
			
			case KEY_F(7): // Pass
			echo();
			wattron(FSTABEdit,A_REVERSE);
			mvwprintw(FSTABEdit, 8, 22,"[______]");
			mvwgetnstr(FSTABEdit, 8,23, fsmgrbuf, 7);
			strcpy(fstfield.pass, fsmgrbuf);
			wattroff(FSTABEdit,A_REVERSE);
			noecho();
			
			break;
			
			case KEY_F(9):
				CommenceAdd();
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


int CommenceAdd()
{
	int QKEY;
	
	while(1)
	{
		MsgBoxQuestion("Do you want to add this to fstab file", "Y/N");
		QKEY = getch();
		switch(QKEY)
		{
			case 'y':
				Writetofstab();
				return 0;
			break;
			
			case 'Y':
				Writetofstab();
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

int Writetofstab()
{
		/* If Yes then Process */
	
	/* Test if file exists */
	if((fopen(fstab_file, "r") == NULL))
	{
		MsgBoxError("Unable to Open fstab file.");
		return(1);
	}
	
	fp = fopen(fstab_file, "a");
	
	MsgBoxInfoNoPause("Adding to fstab");
	fprintf(fp, "%-16s %-15s %-5s %-9s	%-8s %-8s\n", fstfield.Device, fstfield.MntDir, fstfield.Fstyp, fstfield.Option, fstfield.Dump, fstfield.pass);
	MsgBoxInfoNoPause("Adding to fstab, complete");

	
	fclose(fp);
	return 0;
}

