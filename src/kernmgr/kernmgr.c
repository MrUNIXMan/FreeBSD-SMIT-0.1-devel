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

Description: Functions used by Kernel Manager
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
#include <signal.h>
#include "../include/SMIT.h"
#include "../include/kernel.h"


WINDOW *CFGFIleSelect; /* Menu for CFG file select */
FILE *infile, *outfile, *editfile;

char *kerncfgfile;

int c;



void DrawSelectCFGFile(int cfgitem)
{
	int cfgctr;
	

	CFGFIleSelect = newwin(10,39,5,25);	
	box(CFGFIleSelect, ACS_VLINE, ACS_HLINE);
	wrefresh(CFGFIleSelect);
	
	char kernelconfigfiles [SELECT_CFG_MAX] [24] = {
		"GENERIC", 
		"GENERIC-NODEBUG", 
		"Cancel"
		};
	
	
	/* Draw out the Menu */
	
	wattron(CFGFIleSelect, A_BOLD);
	mvwaddstr(CFGFIleSelect, 1, 2, "Select kernel config file to copy");
	mvwaddstr(CFGFIleSelect, 8, 1, "F3=Cancel	Enter=Do");
	wattroff(CFGFIleSelect, A_BOLD);
		
		for (cfgctr=0; cfgctr < SELECT_CFG_MAX; cfgctr++)
		{
			if(cfgctr==cfgitem)		
				wattron(CFGFIleSelect, A_REVERSE);
				mvwaddstr(CFGFIleSelect, 3+(cfgctr*1), 2, kernelconfigfiles[cfgctr]);
				wattroff(CFGFIleSelect, A_REVERSE);
		}
	
}


/* Load and Unload of Kernel Modules */
int load_kernel_module()
{
	return 0;
}

int unload_kernel_module()
{
	return 0;
}
/* Copy Default Config Files */


int SelectDefaultConfigFiles()
{
	
	/* SDCF = Select Default Config File */
	int SDCFItem, SDCFKey;
	
	SDCFItem = 0;
	
	while(SDCFItem != 2)
	{
		DrawSelectCFGFile(SDCFItem);
		wrefresh(CFGFIleSelect);
		
		do
		{
			SDCFKey = getch();
			switch(SDCFKey)
			{
				
				case KEY_DOWN:
				SDCFItem++;
				if(SDCFItem > SELECT_CFG_MAX) SDCFItem = 0;
				break;;
				
				case KEY_UP:
				SDCFItem--;
				if(SDCFItem < 0) SDCFItem = SELECT_CFG_MAX-1;		
				break;;
				
				case KEY_F(3):
				delwin(CFGFIleSelect);
				return 1;
				break;;
			}
		
			DrawSelectCFGFile(SDCFItem);
			wrefresh(CFGFIleSelect);
	    } while(SDCFKey != '\n');
			
		/* Other Menu Functions */
		
		if(SDCFItem == 0)
		{
			delwin(CFGFIleSelect);
			copycfgfile("GENERIC");
			return 0;
			
		}
		if(SDCFItem == 1)
		{
			copycfgfile("GENERIC-NODEBUG");
			return 0;
			delwin(CFGFIleSelect);
		}
		if(SDCFItem == 2)
		{
			return 1;
			delwin(CFGFIleSelect);
		}


	};/* End of while */
		
	return 0;
}

/* Copy Config Files */

int copycfgfile(char *cfgfile)
{
	
	
	if ((kerncfgfile = malloc(sizeof(char) * KERNEL_BUFFER + 1)) == NULL)
		{
			MsgBoxError("Malloc Error");	
		return(1);
		}; 
		
		
		
		echo();
		DLG = newwin(8,50, 5, 20);
		box(DLG, ACS_VLINE, ACS_HLINE);
		mvwprintw(DLG,2,2, "Please Type a new filename to give for the");
		mvwprintw(DLG,3,2, "Kernel configuration file");
		mvwprintw(DLG,5,2, "[__________________________]");
		wrefresh(DLG);

		wattron(DLG, A_REVERSE);
		mvwprintw(DLG,5,2, "[__________________________]");
		wrefresh(DLG);
		
		mvwgetnstr(DLG,5,3, kerncfgfile, 20);
		wattroff(DLG, A_REVERSE);
		wrefresh(DLG);
	
		wclear(DLG);
		box(DLG, ACS_VLINE, ACS_HLINE);
		noecho();
		mvwprintw(DLG, 2, 2, "Copying %s to %s", cfgfile, kerncfgfile);
		wrefresh(DLG);
		sprintf(conffile, "%s", kerncfgfile);
		
		/* Changes to the config file directory */
		
		if(archlevel < 1) {
			if(chdir(AMD64Conf) < 0) {
				MsgBoxError("Unable to change directory");
			}
		}
		else {
		  if(chdir(I386Conf) < 0) {
			  MsgBoxError("Unable to change directory");
		  }
	  };
	  
		/* Attempt to Copy file but checks for it's existant 1st */
				
		if(fopen(cfgfile, "r") == NULL) {
			MsgBoxFileNotFound(cfgfile, "Is not found");
		};
		
		if(fopen(kerncfgfile, "w") == NULL) {
			MsgBoxError("Error writing destination config file");
			//sprintf(conffile, "%s - not written", kerncfgfile);
			return 1;
		};
		
		
		infile =  fopen(cfgfile, "r");
		outfile = fopen(kerncfgfile, "w");
		
		
		while((c = 	fgetc(infile)) != EOF)
		fputc(c,outfile);
			
		wclear(DLG);
		box(DLG, ACS_VLINE, ACS_HLINE);
		mvwprintw(DLG, 2, 2, "Completed Copying %s to %s", cfgfile, kerncfgfile);
	
		
		wrefresh(DLG);
		napms(3000);
	
	
		/* Finish up and Close files */
		delwin(DLG);
	
		noecho();
		fclose(outfile);
		fclose(infile);
		
		free(kerncfgfile); 
	
return 0;	
}

int Use_Existing_Kernel_Conf_file()
{
	DIR *dir;
	
	
	struct dirent *mydirent;
	int i = 1;
		
	
	if ((kerncfgfile = malloc(sizeof(char) * KERNEL_BUFFER + 1)) == NULL)
		{
			MsgBoxError("Malloc Error");	
		return(1);
		}; 
		
		echo();
	DLG = newwin(8,38, 5, 2);
	box(DLG, ACS_VLINE, ACS_HLINE);
	mvwprintw(DLG,1,2, "Please Type existing ");
	mvwprintw(DLG,2,2, "Kernel configuration filename");
	mvwprintw(DLG,3,2, "as seen on list to the right");
	
	mvwprintw(DLG,5,2, "[__________________________]");
	wrefresh(DLG);

	wattron(DLG, A_REVERSE);
	mvwprintw(DLG,5,2, "[__________________________]");
	wrefresh(DLG);
	
	
	/* List files in to another Dialog */
	
	SPARE=newwin(8,32, 5, 40);
	box(SPARE, ACS_VLINE, ACS_HLINE);
	DLG2 = newwin(6,30, 6, 41);
	scrollok(DLG2, TRUE);
	refresh();
	wrefresh(SPARE);
	wrefresh(DLG2);
	
	/* List Dirs */
	
	if (archlevel < 1) {
		
		if((dir = opendir(AMD64Conf)) == NULL) 
			MsgBoxError("Cannot Open Dir");
			while((mydirent = readdir(dir)) != NULL) {
			
			/* Remove the Unnecessary from list 
			 * This also includes the GENERIC Kernel config files
			 * as there is another option on the menu for them.
			 * This only uses custom kernel files.
			 * 
			 * 
			 * */
				if(strcmp(mydirent->d_name, ".") == 0)
				continue;
				if(strcmp(mydirent->d_name, "..") == 0)
				continue;
				if(strcmp(mydirent->d_name, "GENERIC") == 0)
				continue;
				if(strcmp(mydirent->d_name, "GENERIC-NODEBUG") == 0)
				continue;
				if(strcmp(mydirent->d_name, "MINIMAL") == 0)
				continue;
				if(strcmp(mydirent->d_name, "NOTES") == 0)
				continue;
				if(strcmp(mydirent->d_name, "DEFAULTS") == 0)
				continue;
				if(strcmp(mydirent->d_name, "GENERIC.hints") == 0)
				continue;
				if(strcmp(mydirent->d_name, "Makefile") == 0)
				continue;
				
				
				mvwprintw(DLG2, i, 2, "%s", mydirent->d_name);
				wmove(DLG2, i++, 2);
			};
		}
		else
		{
			if((dir = opendir(I386Conf)) == NULL) 
			MsgBoxError("Cannot Open Dir");
			while((mydirent = readdir(dir)) != NULL) {
				
				/* Remove the Unnecessary from list */
				if(strcmp(mydirent->d_name, ".") == 0)
				continue;
				if(strcmp(mydirent->d_name, "..") == 0)
				continue;
				if(strcmp(mydirent->d_name, "NOTES") == 0)
				continue;
				if(strcmp(mydirent->d_name, "DEFAULTS") == 0)
				continue;
				if(strcmp(mydirent->d_name, "GENERIC") == 0)
				continue;
				if(strcmp(mydirent->d_name, "GENERIC-NODEBUG") == 0)
				continue;
				if(strcmp(mydirent->d_name, "MINIMAL") == 0)
				continue;
				if(strcmp(mydirent->d_name, "GENERIC.hints") == 0)
				continue;
				if(strcmp(mydirent->d_name, "Makefile") == 0)
				continue;
				
				mvwprintw(DLG2, i, 2, "%s", mydirent->d_name);
				wmove(DLG2, i++, 2);
			};
		};
		
		
	refresh();
	wrefresh(SPARE);
	wrefresh(DLG2);
	
	mvwgetnstr(DLG,5,3, kerncfgfile, 20);
	wattroff(DLG, A_REVERSE);
	wrefresh(DLG);
	sprintf(conffile, "%s", kerncfgfile);
	delwin(DLG);
	noecho();
	free(kerncfgfile);
	return 0;
	
	
	
	
	return 0;
}

/* Edit Kernel Config Files */

int EditKernelConfigFile(void)
{
	
	/* Check if the Directory Exists */
	
	if(archlevel <1){
		if(chdir(AMD64Conf) <0 )
		{
			MsgBoxError("Unable to Change directory");
			return 1;
		}
	}
	else {
		if(chdir(I386Conf) <0 )
		{
			MsgBoxError("Unable to Change directory");
			return 1;
		}
	}
	
	/* Open up a file */
	
	if(fopen(conffile, "r") == NULL)
	{
		MsgBoxFileNotFound(conffile, "Not found");
		return 1;
	}
	/* Execute an Editor */
	
	else {
			pid_t pid;
			pid = fork();
			use_console();
	
	
			if (pid == 0)
			{
			 char *argv[] = {"ee", conffile};
			 execv("/usr/bin/ee", argv);
			 restore_curses();		
		
			}
			else
			{
			waitpid(pid, NULL,0);
			}
	 }

	restore_curses();
	return 0;
}

/* Compile or Install Kernel */

int DoKernelStuff(char *argument)
{
	/* Determine Arch and Arch Specific dirs */
	
	if(archlevel <1){
		if(chdir(AMD64Conf) <0) {
			MsgBoxError("Unable to Change directory");
			return 1;
		  }
		}
 	else
 	    {
			if(chdir(I386Conf) <0) {
			MsgBoxError("Unable to Change directory");
			return 1;
		}
    };
	
	/* If config file exists then go on */
	
	if(fopen(conffile, "r") == NULL) {
		MsgBoxError("Unable to Open Selected Kernel Config file");
		return 1;
	}
	
	/* If /usr/src dir exists then go on */
	
	if(chdir(srcdir) <0)	{
		MsgBoxError("Unable to change to /usr/src dir");
		return 1;
	}
	

	/* Compare String with Argument */

	if(strcmp(argument, "compile") == 0)
	{
		MsgBoxCommence("Kernel Compile Starting", "Compile Kernel");
		use_console();
		sleep(1);
		printf("Compiling the Kernel is commencing\n\n");
		printf("Command used: make buildkernel KERNCONF=%s\n\n", conffile);
		sleep(4);
	
		execute_kernel_compile();
	
		consolepause();
		restore_curses();
	}
	if(strcmp(argument, "install") == 0) 
	{
		MsgBoxCommence("Kernel Install Starting", "Installing Kernel");
		use_console();
		sleep(1);
		printf("Install the Kernel is commencing\n\n");
		printf("Command used: make installkernel KERNCONF=%s\n\n", conffile);
		sleep(4);
	
		install_kernel_execution();
	
		consolepause();
		restore_curses();
	}
	
	
	return 0;
}


	
int execute_kernel_compile()
{
	
	sprintf(buf, "KERNCONF=%s", conffile);
	char *argv[] = {"make", "buildkernel", buf, 0};
	
	
	pid_t pid = fork();
	
	if(pid < 0)
	{
		printf("Fork Failed\n\n");
		consolepause();
	}
	else if(pid == 0) {
		
		execv("/usr/bin/make", argv);
		
      }
      else
      {
		  waitpid(pid, NULL, 0);
		  	/* Return to Smit */		
		}
	
	return 0;
}

int install_kernel_execution()
{
	
	sprintf(buf, "KERNCONF=%s", conffile);
	char *argv[] = {"make", "installkernel", buf, 0};
	
	
	pid_t pid = fork();
	
	if(pid < 0)
	{
		printf("Fork Failed\n\n");
		consolepause();
	}
	else if(pid == 0) {
		
		execv("/usr/bin/make", argv);
		
      }
      else
      {
		  waitpid(pid, NULL, 0);
		  	/* Return to Smit */		
		}
	
	return 0;
}

