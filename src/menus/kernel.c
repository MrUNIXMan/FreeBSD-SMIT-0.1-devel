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

Description: Kernel Manager UI & Controls



----------------------------------------------------------------------------------------
*/


#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include <unistd.h>
#include <sys/utsname.h>


#include "../include/SMITMenus.h"
#include "../include/SMITprotos.h"
#include "../include/SMIT.h"
#include "../include/kernel.h"


/* Computer Declaration to Display Information */


struct utsname uts;





int startkernmenu()
{
	/* If this fails the host information will be set to Unknown */
	if (gethostname(computer, 255) != 0 || uname(&uts) <0)
	{
		errorlevel = 1; /* This means not able to display host information */
		MsgBoxError("Unable to Open Host information. Will continue without it");
	}
	
	
	/* Sets the Arch of the Machine 
	 * 0 for AMD64 as it is now most used
	 * 1 for I386 as it is least used */
	 
	if (strcmp(uts.machine, "amd64") == 0) {
			archlevel = 0;
		}
	else if (strcmp(uts.machine, "i386") == 0) {
			archlevel = 1;
			}; // End of if (strcmp(uts.machine statments
			
	
	int KernelMenuItems, KernelMenuKey;
	KernelMenuItems = 0;
	
	while(KernelMenuItems != 8)
	{
		DrawKernelMenuUI(KernelMenuItems);
		refresh();
		do
		 {
			KernelMenuKey = getch();
			switch(KernelMenuKey)
			{
				case KEY_UP:
					 KernelMenuItems--;
					if(KernelMenuItems < 0) KernelMenuItems = KERN_MENU_MAX-1;
				break;;
				case KEY_DOWN:
					KernelMenuItems++;
					if(KernelMenuItems > KERN_MENU_MAX) KernelMenuItems = 0;
				break;;
				case KEY_F(1):
					help_func("kernmgr");
				break;;
				
				case KEY_F(10):
				return 0;
				break;;
				
				
			}
			DrawKernelMenuUI(KernelMenuItems);
			refresh();
		} while(KernelMenuKey != '\n');
		
		/* Menu Responses go here */
			if(KernelMenuItems == 0)
			{
				kernel_module_inputbox();	
			}
			if(KernelMenuItems == 1)
			{
				unload_kernel_module_inputbox();
			}
			if(KernelMenuItems == 2)
			{
				ShowLoadedKernelModules();
			}
			if(KernelMenuItems == 3) /* Copies a GENERIC Kernel File to a filename */
			{	
				SelectDefaultConfigFiles();
			
			}
			if(KernelMenuItems == 4) /* selects previously copied config file */
			{
				Use_Existing_Kernel_Conf_file();
			}
			if(KernelMenuItems == 5) /* Runs an Editor to Edit a config File */
			{
				EditKernelConfigFile();
			}
			if(KernelMenuItems == 6)
			{
				DoKernelStuff("compile");
			}
			if(KernelMenuItems == 7)
			{
				DoKernelStuff("install");
			}
			if(KernelMenuItems == 8) /* Quit */
			{
			}
	
	} /* End of While */
	
	
	return 0;
}
