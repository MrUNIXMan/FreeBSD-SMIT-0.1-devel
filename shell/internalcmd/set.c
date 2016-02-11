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
* SMIT Shell Interpreter - This is the Internal Shell for Smit
* /
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../includes/common.h"


int SMITsh_set(char **args)
{
	
	char input[256];
	char cwd[1024];

   /* printf("Argument 0:	%s\n", args[0]);
    printf("Argument 1: %s\n", args[1]);
    printf("argument 2: %s\n", args[2]); */
    
    
    if(args[1] == NULL)
		{
			printf("_What: ");
			scanf("%s", &input);
			printf("\n");
			
			printf("%s\n", input);
			return 1;
		}
    
    


	if(strcmp(args[1], "default") == 0) 
	//if(strcmp(input, "default") == 0) 
	//if((strcmp(args[1], "default") == 0) || (strcmp(input, "default") == 0))
	{
		if(args[2] == NULL)
		{
			fprintf(stderr, "%s: expected argument to \"set default\"\n", SHELL_NAME);
		} else {
			if(chdir(args[2]) != 0) {
				perror(SHELL_NAME);
			}
		}
		return 1;
	}











    return 1;
}
