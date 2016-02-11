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



int sysinfomenu()
{
	int SiItems, SiKey;
	SiItems = 0;
	
	while(SiItems != 5)
	{
		DrawSysInfoMenu(SiItems);
		refresh();
		do
		 {
			SiKey = getch();
			switch(SiKey)
			{
				case KEY_UP:
					 SiItems--;
					if(SiItems < 0) SiItems = SYSINFOMENU_MAX-1;
				break;;
				case KEY_DOWN:
					SiItems++;
					if(SiItems > SYSINFOMENU_MAX) SiItems = 0;
				break;;
				case KEY_F(10):
				return 0;
				break;;
				
				
			}
			DrawSysInfoMenu(SiItems);
			refresh();
		} while(SiKey != '\n');
		
		/* Menu Responses go here */
	
		if (SiItems == 0)
		{
			 sysinfo();
		}
		if (SiItems == 1)
		{
			ShowLoggedUsers();
		}  
		if (SiItems == 2)
		{
			mntlistmain();
		} 
		if (SiItems == 3)
		{
		 showdiskspace();
		}
		
		if (SiItems == 4)
		{
			ShowLoadedKernelModules();
		} /*
		else if (SiItems == 5)
		{
			startkernmenu();
		}
		* */
		
		
	
	} /* End of While */
	
	
	return 0;
}
