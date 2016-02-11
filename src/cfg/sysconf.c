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

Description: FreeBSD-SMIT System  Configuration
* 
----------------------------------------------------------------------------------------
*/
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>
#include "../include/SMIT.h"

#define EDITOR_DEF "ee"

#define ETC_DIR "/etc"
#define FSTAB_FILE "fstab"
#define RC_CONF "rc.conf"
#define HOSTS_FILE "hosts"
#define BOOTLOADER "/boot/loader.conf"

#define XORG_CONF "X11/xorg.conf"


char editor[100];
char filenames[256];


int edit_file(char *arg)
{
	if(strcmp(arg, "bootloader") == 0) {
		sprintf(filenames, "%s", BOOTLOADER);
		do_edit_file();
	}
	
	if(strcmp(arg, "hosts") == 0) {
		sprintf(filenames, "%s/%s", ETC_DIR, HOSTS_FILE);
		do_edit_file();
	}
	
	if(strcmp(arg, "rcconf") == 0) {
		sprintf(filenames, "%s/%s", ETC_DIR, RC_CONF);
		do_edit_file();
	}
	
	if(strcmp(arg, "fstab") == 0) {
		sprintf(filenames, "%s/%s", ETC_DIR, FSTAB_FILE);
		do_edit_file();
	}
	
	if(strcmp(arg, "xorgcfg") == 0) {
		sprintf(filenames, "%s/%s", ETC_DIR, XORG_CONF);
		do_edit_file();
	}
	
	
	
	
	if(fopen(filenames, "r") == NULL) {
		MsgBoxError("Unable to find selected file to edit");
		return 1;
		}
	/* If successful then commence the Edit */
	
	sprintf(editor, "%s", EDITOR_DEF);
	

	use_console();
	
	do_edit_file();
	

	restore_curses();
	
	
	return 0;
}


void do_edit_file()
{		
		int status;
		char *argv[] = {editor, filenames, NULL};
		
		pid_t pid = fork();
		
		if(pid == 0)
		{	
			    napms(10);
			    execv("/usr/bin/vi",argv);
			    napms(100);
			    restore_curses();
		 }
		 else
		    {
			napms(10);
			waitpid(pid, NULL, 0);
			//pid = wait(&status);
		    } 

}




