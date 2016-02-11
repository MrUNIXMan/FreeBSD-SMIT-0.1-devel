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

Description: Shared Functions for Reusable Code

----------------------------------------------------------------------------------------
*/
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <dirent.h>
#include "../include/SMIT.h"
#include "../include/kernel.h"
#include <sys/wait.h>


void use_console()
{
	 clear();
	 refresh();
	 savetty();
	 reset_shell_mode();
	 curs_set(2);
	 
	
}

void restore_curses()
{
	 curs_set(0);
	 resetty();
	
}


void consolepause(void)
{
		printf("Paused to view output\n\n");
		printf("When finished viewing\n");
		printf("Press Enter to Return to SMIT\n");
		while(!getchar()); 		
	
}


int execute_default_shell()
{
	 pid_t pid = fork();
	 /*Shell installed with SMIT */
	 char *argv[2] = {"/usr/local/bin/SMITsh", 0};
//	 char *argv[2] = {"/bin/sh", 0};
	 
	 use_console(); /* Restores the Screen for use with console apps */
	 if(pid == 0) 
	 {
/*		printf("Entering %s\n", defaultshell);
		printf("Type Exit or press CTRL+D to Return to SMIT when finished\n\n"); */
//		execv("/bin/sh", argv);
		execv("/usr/local/bin/SMITsh", argv);
		restore_curses();
	 }
	 else
	 {
		
		waitpid(pid, NULL,0);
		
	} 
	 restore_curses(); /* Sets Curses Mode back */
	
	
	return 0;
}
