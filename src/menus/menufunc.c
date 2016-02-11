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

Description: Shared Menu functions. This contains all layout of all menus and some 
* shared functions.

----------------------------------------------------------------------------------------
*/


#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include <unistd.h>
#include <sys/utsname.h>
#include "../include/SMITMenus.h"
#include "../include/SMIT.h"
#include "../include/kernel.h"

int x, y;

struct utsname uts;

/* Draw Screen Just Draws the Usual often Required Stuff */
void drawmenuscreen()
{
	clear();
	getmaxyx(stdscr, y, x);
	box(stdscr, ACS_VLINE, ACS_HLINE);
	
	 attron(A_BOLD);
	 mvaddstr(y-4,2, FKEY1); /* Bottom Bar */
	 mvaddstr(y-3,2, FKEY2); /* Bottom Bar */
	 attroff(A_BOLD);
	
	
}




/* Draw Out the Main Menu */

void DrawMainMenuUI(int mainmenuitem)
{
	drawmenuscreen();
	char MainMenuTitle[] = "System Management";
	
	/* Counter */
	int MainMenuCTR;
	
	/* Menu Items for the main menu */
	
	char mainmenu [MAINMENU_MAX] [34] = {
		"System Information",
		"User & Group manager",
		"Filesystem management",
		"Software management",
		"Network Management",
		"System Configuration manager",
		"Help",
		"About FreeBSD SMIT",
		"Quit"
	};
	
	 /* This now Draws the Menu Titles to the Screen */
	 
	 attron(A_BOLD);
	 mvaddstr(1, 27, MainMenuTitle); /* Title for Main menu */
	 mvaddstr(3, 2, mesg); /* Message Below the title */
	
	 
	 attroff(A_BOLD);  /* Turn off BOLD */
	
	/* Menu Items */
	
	/* Print Menu item during highlight */
	 
	 for (MainMenuCTR=0; MainMenuCTR <MAINMENU_MAX; MainMenuCTR++)
	 {
		if(MainMenuCTR==mainmenuitem)
			attron(A_REVERSE);
			mvaddstr(5+(MainMenuCTR*1), 5, mainmenu[MainMenuCTR]);
			attroff(A_REVERSE);
		}
	
	/* Refresh the screen */ 
	 refresh();
	
}
/*************************************************************************************************************/

/* System Configuration Menu */

void DrawSysConfigMenu(int syscfgitem)
{
	drawmenuscreen();
	
	char SysCfgMenuTitle[] = "System Configuration";
	
	/* Counter */
	int SysCfgMenuCTR;
	
	/* Menu Items for the main menu */
	
	char syscfgmenu [SYSCFGMENU_MAX] [34] = {
		"Edit Boot Loader file",
		"Edit hosts file",
		"Edit rc.conf file",
		"Edit fstab file",
		"Edit Xorg.conf file",
		"Kernel Configuration Manager",	
		"Help",
		"Quit"
	};
	
	 /* This now Draws the Menu Titles to the Screen */
	 
	 attron(A_BOLD);
	 mvaddstr(1, 27, SysCfgMenuTitle); /* Title for SysCFG menu */
	 mvaddstr(3, 2, mesg); /* Message Below the title */
	
	 
	 attroff(A_BOLD);  /* Turn off BOLD */
	
	/* Menu Items */
	
	/* Print Menu item during highlight */
	 
	 for (SysCfgMenuCTR=0; SysCfgMenuCTR <SYSCFGMENU_MAX; SysCfgMenuCTR++)
	 {
		if(SysCfgMenuCTR==syscfgitem)
			attron(A_REVERSE);
			mvaddstr(5+(SysCfgMenuCTR*1), 5, syscfgmenu[SysCfgMenuCTR]);
			attroff(A_REVERSE);
		}
	
	/* Refresh the screen */ 
	 refresh();
	
	
}

/**********************************************************************************************************/

/* Kernel Manager Menu */


void DrawKernelMenuUI(int KernelMenuItem)
{
	drawmenuscreen();
	
	char KernelMenuTitle[] = "Kernel Manager";
	
	/* Counter */
	int KernelMenuCTR;
	
	/* Menu Items for the main menu */
	
	char kernelmenu [KERN_MENU_MAX] [34] = {
		"Load a Kernel Module",
		"Unload a Kernel Module",
		"View loaded Kernel Modules",
		"Copy GENERIC file to new name",
		"Use Existing Kernel config file", 
		"Edit a Kernel Config file",
		"Compile Kernel",
		"Install Kernel", 
		"Quit"
	};
	
	 /* This now Draws the Menu Titles to the Screen */
	 
	 attron(A_BOLD);
	 mvaddstr(1, 27, KernelMenuTitle); /* Title for SysCFG menu */
	 attroff(A_BOLD);  /* Turn off BOLD */
	/* Print Out System Info */
	if(errorlevel <1) {
		
	mvprintw(3, 2, "ARCH: %s", uts.machine);
	mvprintw(3, 20, "O/S: %s", uts.sysname);
	mvprintw(3, 40, "Release: %s", uts.release);
	
	/* Check for Arch */
		if(archlevel <1) {	
			mvprintw(4, 2,  "Kernel Config File Path: %s", AMD64Conf);
			mvprintw(5,2, "Kernel Configuration file: %s", conffile);
		   }
		else
		{
			mvprintw(4, 2,  "Kernel Config File Path: %s", I386Conf);
			mvprintw(5,2, "Kernel Configuration file: %s", conffile);
		};
	}
	else /* Default to I386 */
	{
	mvprintw(3, 2, "Kernel Config File Path: %s", I386Conf);
	mvprintw(4,2, "Kernel Configuration file: %s", conffile);
	};
	
	refresh();
	
	
	
	
	
	/* Menu Items */
	
	/* Print Menu item during highlight */
	 
	 for (KernelMenuCTR=0; KernelMenuCTR <KERN_MENU_MAX; KernelMenuCTR++)
	 {
		if(KernelMenuCTR==KernelMenuItem)
			attron(A_REVERSE);
			
			/* This Lowers the Menu if Errorlevel is not 1 */
			if(errorlevel < 1) {
			mvaddstr(7+(KernelMenuCTR*1), 5, kernelmenu[KernelMenuCTR]);
			}
			else {
				mvaddstr(5+(KernelMenuCTR*1), 5, kernelmenu[KernelMenuCTR]);
			};
			
			attroff(A_REVERSE);
		}
	
	/* Refresh the screen */ 
	 refresh();
	
}

/**************************************************************************************************************** */

/* System Information Menu */

void DrawSysInfoMenu(int SysInfoMNUItem)
{
	char SysInfoTitle[] = "System Information";
	int SysInfCtr;
	
	
	char MNUSysInfo [SYSINFOMENU_MAX] [34] = {
		"System Specs",
		"Users logged on to system", 
		"Show Mounted Filesystems",
		"Show Disk Spaces",
		"Show Loaded Kernel Modules",
		"Quit"
		
	};

	drawmenuscreen();
	
	 /* This now Draws the Menu Titles to the Screen */
	 
	 attron(A_BOLD);
	 mvaddstr(1, 27, SysInfoTitle); /* Title for SysCFG menu */
	 mvaddstr(3, 2, mesg); /* Message Below the title */
	
	 
	 attroff(A_BOLD);  /* Turn off BOLD */
	
	
	
	/* Menu Items */
	
	/* Print Menu item during highlight */
	 
	 for (SysInfCtr=0; SysInfCtr <SYSINFOMENU_MAX; SysInfCtr++)
	 {
		if(SysInfCtr==SysInfoMNUItem)
			attron(A_REVERSE);
			mvaddstr(5+(SysInfCtr*1), 5, MNUSysInfo[SysInfCtr]);
			attroff(A_REVERSE);
		}
	


}
/*********************************************************************************************************************/
/* User & Group Menu */

void DrawUserandGroupMenu(int ugmenuitem)
{
	char UGTitle[] = "User & Groups";
	int  UGCTR;
	
	char UGMENU[USER_MENU_MAX] [34] =  {
		"User Manager",
		"Group Manager",
		"User Info",
		"Quit"
	};
	
	drawmenuscreen();
	
	/* This now Draws the Menu Titles to the Screen */
	 
	 attron(A_BOLD);
	 mvaddstr(1, 27, UGTitle); /* Title for SysCFG menu */
	 mvaddstr(3, 2, mesg); /* Message Below the title */
	 attroff(A_BOLD);  /* Turn off BOLD */
	
	/* Print Menu item during highlight */
	 
	 for (UGCTR=0; UGCTR <SYSINFOMENU_MAX; UGCTR++)
	 {
		if(UGCTR==ugmenuitem)
			attron(A_REVERSE);
			mvaddstr(5+(UGCTR*1), 5, UGMENU[UGCTR]);
			attroff(A_REVERSE);
		}
	
	
	
}
