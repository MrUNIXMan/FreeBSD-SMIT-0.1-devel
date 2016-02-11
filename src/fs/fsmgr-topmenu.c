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

 *This deals with the Top Menu on the filesystem manager
 * 
-------------------------------------------------------------------------------------------------------------- 
 */
 
 #include <stdio.h>
 #include <stdlib.h>
 #include <ncurses.h>
 #include "../include/SMIT.h"
 #include "../include/filesystemfuncs.h"
 #include "../include/fsvals.h"

void DrawFstabMenu(int FstabItem)
{
	int Fstabctr;
	char FstabMenuOpt[FSTABMENU_MAX] [24] = {
		"Add to Fstab",
		"Test "
		};
		
	FSTABMENU = newwin(6, 18, 2, 2);
	keypad(FSTABMENU, TRUE);
	box(FSTABMENU, ACS_VLINE, ACS_HLINE);

	for(Fstabctr=0 ; Fstabctr < FSTABMENU_MAX; Fstabctr++)
	{
		if(Fstabctr == FstabItem)
		wattron(FSTABMENU,A_REVERSE);
			  mvwaddstr(FSTABMENU, 1+(Fstabctr*1), 2, FstabMenuOpt[Fstabctr]);
			wattroff(FSTABMENU,A_REVERSE);

	}

	wrefresh(FSTABMENU);
	
}

void DrawViewMenu(int VMItem)
{
	int VMCTR;
	
	char ViewItems [VIEWMENU_MAX] [24] = {
		"Mounted filesystems", 
		"FStab List",
		"Back"
		};

	VIEWMENU = newwin(6, 27, 2, 18);
	keypad(VIEWMENU, TRUE);
	box(VIEWMENU, ACS_VLINE, ACS_HLINE);
	
	
	
	
	for(VMCTR = 0 ; VMCTR < VIEWMENU_MAX; VMCTR++)
	{
		if(VMCTR == VMItem)
			wattron(VIEWMENU,A_REVERSE);
			  mvwaddstr(VIEWMENU, 1+(VMCTR*1), 2, ViewItems[VMCTR]);
			wattroff(VIEWMENU,A_REVERSE);
		
	}
	
	
	wrefresh(VIEWMENU);
	
	
	
}

/* Disk Menu */
void DrawDiskMenu(int DiskItem)
{
	int DiskCTR;
	
	char DiskItems [DISKMENU_MAX] [24] = {
		"List Paritions",
		"Partition Disk", 
		"Format Disk",
		"Mount Disk",	
		"Dismount Disk",
		"Back"
		};

	DISKMENU = newwin(8, 20, 2, 10);
	keypad(DISKMENU, TRUE);
	box(DISKMENU, ACS_VLINE, ACS_HLINE);
	
	
	
	
	for(DiskCTR = 0 ; DiskCTR < DISKMENU_MAX; DiskCTR++)
	{
		if(DiskCTR == DiskItem)
			wattron(DISKMENU,A_REVERSE);
			  mvwaddstr(DISKMENU, 1+(DiskCTR*1), 2, DiskItems[DiskCTR]);
			wattroff(DISKMENU,A_REVERSE);
		
	}
	
	
	wrefresh(DISKMENU);
	
	
	
}



int showFstabMenu()
{
	int FstabKey;
	int FstabMitem = 0;

	while(FstabMitem != 1)
	{
		DrawFstabMenu(FstabMitem);
		do
			{
				FstabKey = wgetch(FSTABMENU);
				switch(FstabKey)
				{
					case KEY_F(10):
					return 0;
					break;
					
					case KEY_DOWN:
					FstabMitem++;
					
					if(FstabMitem > FSTABMENU_MAX) FstabMitem = 0;
					break;
					
					case KEY_UP:
					FstabMitem--;
					if(FstabMitem < 0) FstabMitem = FSTABMENU_MAX-1;
					break;
					
				}
				DrawFstabMenu(FstabMitem);
			} while(FstabKey != '\n');
			
			/* Menu options */
			
			if(FstabMitem == 0)
			{
				delwin(FSTABMENU);
				AddtoFstab();
				
			}
			
			return 0;
		}
	
	
	return 0;
}

int ShowViewMenu()
{
	
	int ViewMenuItem = 0;
	int ViewKey;
	
	while(ViewMenuItem != 2)
	{
		DrawViewMenu(ViewMenuItem);
		do
		{
			ViewKey = wgetch(VIEWMENU);
			switch(ViewKey)
			{
				case KEY_DOWN:
					ViewMenuItem++;	
					if(ViewMenuItem >  VIEWMENU_MAX)  ViewMenuItem = 0;
				break;
				
				case KEY_UP:
					ViewMenuItem--;
					if(ViewMenuItem < 0)  ViewMenuItem = VIEWMENU_MAX-1;				
				break;
				case KEY_F(10):
					return 0;
				break;
			}
			
			DrawViewMenu(ViewMenuItem);
		} while(ViewKey != '\n');
		
		/* Options here */
		
		if(ViewMenuItem == 0)
		{
			wclear(FSPAD);
			FS_counter = 15;
			FsMgrViewFStab = 0;
			FsMgrViewMounts = 1;
			FsMgrRelist = 0;
	
			//return 0;
			
		}
		else if(ViewMenuItem == 1)
		{
			wclear(FSPAD);
			FS_counter = 15;
			FsMgrViewFStab = 1;
			
			FsMgrViewMounts = 0;
			
			FsMgrRelist = 0;
			
			//return 0;
		}
	
		return 0;
	}
		
	
	
	return 0;
}


int ShowDiskMenu()
{
	int DiskMenuItem = 0;
	int DiskKey;
	
	while(DiskMenuItem != 2)
	{
		DrawDiskMenu(DiskMenuItem);
		do
		{
			DiskKey = wgetch(DISKMENU);
			switch(DiskKey)
			{
				case KEY_DOWN:
				DiskMenuItem++;
				if(DiskMenuItem > DISKMENU_MAX) DiskMenuItem = 0;
				
				break;
				
				case KEY_UP:
				DiskMenuItem--;
				if(DiskMenuItem < 0) DiskMenuItem = DISKMENU_MAX-1;
				break;
				
				case KEY_F(10):
				return 0;
				break;
				
				
			}
			DrawDiskMenu(DiskMenuItem);
		} while(DiskKey != '\n');
		/* Menu Opts */
		
		if(DiskMenuItem == 3)
			{
				Mountafs();
			}
		else if(DiskMenuItem == 4)
			{
				Unmount_Fs();
			}
			return 0;
		
	}
	
	
	
	return 0;
}
