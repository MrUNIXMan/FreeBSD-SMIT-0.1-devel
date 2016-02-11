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

Description: Main Menu 



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



int startsmit()
{
	int MainMenuItems, MainMenuKey;
	MainMenuItems = 0;
	
	while(MainMenuItems != 8)
	{
		DrawMainMenuUI(MainMenuItems);
		refresh();
		do
		 {
			MainMenuKey = getch();
			switch(MainMenuKey)
			{
				case KEY_UP:
					 MainMenuItems--;
					if(MainMenuItems < 0) MainMenuItems = MAINMENU_MAX-1;
				break;;
				case KEY_DOWN:
					MainMenuItems++;
					if(MainMenuItems > MAINMENU_MAX) MainMenuItems = 0;
				break;;
				case KEY_F(1):
				    help_func("smitmain");
				    break;;
				case KEY_F(9):
					execute_default_shell();
				break;;
				case KEY_F(10):
				return 0;
				break;;
				
				
			}
			DrawMainMenuUI(MainMenuItems);
			refresh();
		} while(MainMenuKey != '\n');
		
		/* Menu Responses go here */
		
		if (MainMenuItems == 0)
		{
			sysinfomenu();
		}
		else if(MainMenuItems == 1)
		{
			userandgroupmenu();
		}
		else if(MainMenuItems == 2)
		{
			FilesystemManager();
		}
		else if(MainMenuItems == 5)
		{
			syscfgmenu();
			
		}
		else if(MainMenuItems == 6)
		{
			//
			
		}
		else if(MainMenuItems == 7)
		{
			DLG = newwin(5,51,6,15);   /* Dialog Declared at WINDOW */
			box(DLG, ACS_VLINE, ACS_HLINE);
			wattron(DLG, A_UNDERLINE);
			mvwprintw(DLG, 1, 16, "About %s", PROGNAME);
			wattroff(DLG, A_UNDERLINE);
			mvwprintw(DLG, 2, 11, "%s", COPYRIGHT);
			wrefresh(DLG);
			wgetch(DLG);
			werase(DLG);
		}
		
	
	} /* End of While */
	
	
	return 0;
}
