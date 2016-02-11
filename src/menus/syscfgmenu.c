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

Description: Sys Config  Menu 



----------------------------------------------------------------------------------------
*/


#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include <unistd.h>

#include "../include/SMITMenus.h"
#include "../include/SMITprotos.h"
#include "../include/SMIT.h"



int syscfgmenu()
{
	int SysCFGMenuItems, SysCFGMenuKey;
	SysCFGMenuItems = 0;
	
	while(SysCFGMenuItems != 7)
	{
		DrawSysConfigMenu(SysCFGMenuItems);
		refresh();
		do
		 {
			SysCFGMenuKey = getch();
			switch(SysCFGMenuKey)
			{
				case KEY_UP:
					 SysCFGMenuItems--;
					if(SysCFGMenuItems < 0) SysCFGMenuItems = SYSCFGMENU_MAX-1;
				break;;
				case KEY_DOWN:
					SysCFGMenuItems++;
					if(SysCFGMenuItems > SYSCFGMENU_MAX) SysCFGMenuItems = 0;
				break;;
				case KEY_F(10):
				return 0;
				break;;
				
				
			}
			DrawSysConfigMenu(SysCFGMenuItems);
			refresh();
		} while(SysCFGMenuKey != '\n');
		
		/* Menu Responses go here */
		if (SysCFGMenuItems == 0)
		{
			edit_file("bootloader");
		}
		if (SysCFGMenuItems == 1)
		{
			edit_file("hosts");
		}
		if (SysCFGMenuItems == 2)
		{
			edit_file("rcconf");
		}
		if (SysCFGMenuItems == 3)
		{
			edit_file("fstab");
		}
		if (SysCFGMenuItems == 4)
		{
			edit_file("xorgcfg");
		}
		else if (SysCFGMenuItems == 5)
		{
			startkernmenu();
		}
		
		
	
	} /* End of While */
	
	
	return 0;
}
