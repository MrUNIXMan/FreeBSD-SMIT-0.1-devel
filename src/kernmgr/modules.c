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

Description: FreeBSD-SMIT Kernel manager's Module for dealing with kernel modules.
* 
This has more dealing with Kernel Modules ie loading and unloading of Modules
----------------------------------------------------------------------------------------
*/


#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <dirent.h>
#include <sys/wait.h>

#include "../include/SMIT.h"
#include "../include/kernel.h"


char *modulestoload;
char *modulestounload;
char kernpathbuf[250];
int KernelModuleExists;  /* This is set to 1 if it exists */

int check_path();
void loadmodule();
void unloadmodule();

int kernel_module_inputbox()
{
	KernelModuleExists = 0;
	
	if ((modulestoload = malloc(sizeof(char) * KERNEL_BUFFER + 1)) == NULL)
		{
			MsgBoxError("Malloc Error");	
		return(1);
		}; 
		
		echo();
	DLG = newwin(8,38, 5, 20);
	box(DLG, ACS_VLINE, ACS_HLINE);
	mvwprintw(DLG,1,2, "Please type a Kernel module,");
	mvwprintw(DLG,2,2, "that you wish to load.");
	mvwprintw(DLG,3,2, "They are found in /boot/kernel");
	
	
	
	mvwprintw(DLG,5,2, "[__________________________]");
	wrefresh(DLG);

	wattron(DLG, A_REVERSE);
	mvwprintw(DLG,5,2, "[__________________________]");
	wrefresh(DLG);
	
	
	mvwgetnstr(DLG,5,3, modulestoload, 20);
	wattroff(DLG, A_REVERSE);
	
	
	sprintf(kernpathbuf, "%s/%s.ko", kernelmoddir, modulestoload);
	
	check_path();
	loadmodule();
	
	return 0;
}

int unload_kernel_module_inputbox()
{
	KernelModuleExists = 0;
	
	
	if ((modulestounload = malloc(sizeof(char) * KERNEL_BUFFER + 1)) == NULL)
		{
			MsgBoxError("Malloc Error");	
		return(1);
		}; 
		
		echo();
	DLG = newwin(8,45, 5, 20);
	box(DLG, ACS_VLINE, ACS_HLINE);
	mvwprintw(DLG,1,2, "Please type a Kernel module, that");
	mvwprintw(DLG,2,2, "you wish to unload.");
	mvwprintw(DLG,3,2, "Check Modules list to view loaded Modules");
	
	
	
	mvwprintw(DLG,5,2, "[__________________________]");
	wrefresh(DLG);

	wattron(DLG, A_REVERSE);
	mvwprintw(DLG,5,2, "[__________________________]");
	wrefresh(DLG);
	
	
	mvwgetnstr(DLG,5,3, modulestounload, 20);
	wattroff(DLG, A_REVERSE);
	
	sprintf(kernpathbuf, "%s/%s.ko", kernelmoddir, modulestounload);
	
	check_path();
	unloadmodule();
	
	return 0;
}


int check_path()
{
	wclear(DLG);
	DLG = newwin(8,45, 5, 20);
	box(DLG, ACS_VLINE, ACS_HLINE);
	mvwprintw(DLG,1,2, "Kernel Path: %s",kernpathbuf);
	wrefresh(DLG);
	
	
	
	if(fopen(kernpathbuf, "r") == NULL )
		{
			MsgBoxFileNotFound(kernpathbuf, "No such module");
			return(1);
			
		};
	
	
	/* Go Next Step */
	KernelModuleExists = 1;
	return 0;
}

/* This will execute Kldload or Kldunload */

void loadmodule()
{
	if(KernelModuleExists > 0)
		{
			MsgBoxKern(kernpathbuf, "Attempting to load kernel Module");
			
			char *argv[] = {"kldload", kernpathbuf, NULL};
			
			pid_t pid = fork();
			napms(3000);
			
			if(pid < 0) 
				MsgBoxError("Fork Failed");
			
			else if(pid == 0) {
				execv("/sbin/kldload", argv);
				}
			else {
				 waitpid(pid, NULL, 0);
				}
			
			
		}
	
	
	
	
}



void unloadmodule()
{
	if(KernelModuleExists > 0)
		{
			MsgBoxKern(kernpathbuf, "Attempting to un-load kernel Module");
			char *argv[] = {"kldunload", kernpathbuf,NULL};
			
			pid_t pid = fork();
			napms(3000);
			
			if(pid < 0) 
				MsgBoxError("Fork Failed");
			
			else if(pid == 0) {
				execv("/sbin/kldunload", argv);
				}
			else {
				 waitpid(pid, NULL, 0);
				}
			
			
		}
	
	
}


