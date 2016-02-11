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
* 
* Basic Commands that don't really need a module to themselves
* /
*/



#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "../includes/common.h"


/*
  Builtin function implementations.
*/


/**
   @brief Bultin command: change directory.
   @ No Args will show the path like DOS versions do
   @param args List of args.  args[0] is "cd".  args[1] is the directory.
   @return Always returns 1, to continue executing.
 */
int SMITsh_cd(char **args)
{
   char CWD[1024];
   
  if (args[1] == NULL) {
   // fprintf(stderr, "%s: expected argument to \"cd\"\n", SHELL_NAME);
	  if(getcwd(CWD, sizeof(CWD)) != NULL)
		fprintf(stdout, "Current Dir: %s\n", CWD);
  } else {
    if (chdir(args[1]) != 0) {
		perror(SHELL_NAME);
    }
  }
  return 1;
}


int SMITsh_ver(char **args)
{
	printf("\nSMIT Shell version: %s\nSMIT Version %s\n\n", SHELL_VER, SMIT_VER);
	
	return 1;
}


int SMITsh_about(char **args)
{
	printf("\nSMIT Shell Copyright (C) 2016 Vincent\n\n");
	printf("Smit Shell is SMIT's own shell with different commands\n\n");
	
	return 1;
}
