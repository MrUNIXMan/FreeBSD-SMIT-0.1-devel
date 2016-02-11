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


#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../includes/common.h"

int SMITsh_directory(char **args)
{
	
	DIR *dir;
	char type[256];
	char curdir[5];
	sprintf(curdir, ".");

	struct dirent *mydirent;
	int i = 1;


	/* This will Check if any arguments are supplied, if none attempt to use
	 * the current directory.
	 * 
	 * If an argument is supplied then process that arguments */

	if(args[1] == NULL) {
		if((dir = opendir(curdir)) == NULL)
		{
		fprintf(stderr, "%s: Unable to Open Directory\n", SHELL_NAME);
		return 1;
		}
	}
	else if((dir = opendir(args[1])) == NULL) 
	{
		fprintf(stderr, "%s: Unable to Open Directory\n", SHELL_NAME);
		fprintf(stderr, "You typed: %s\n\n", args[1]);
		return 1;
	}
		

	/* Print Title */
	
		if(args[1] == NULL) {
			printf("Viewing Directory: %s\n\n", "Current Directory");
		} else {
			printf("Viewing Directory: %s\n\n", args[1]);
		}
			

	/* Print Header */
		printf("[ %-17s ] \t %s\n", "List Types", "Entries");
		printf("%1s\n", "------------------------------------------------------------");
		
	/* Process dirs and files  to the types
	 * d_type = u8int 
	 * 0 = Unknown
	 * 1 = Fifo
	 * 2 = Charactor Device
	 * 4 = Directory
	 * 6 = Block
	 * 8 = Regular File
	 * 10 = Link 
	 * 12 = Sock
	 * 14 = White
	 * */
		
		while((mydirent = readdir(dir)) != NULL) 
		{
					
			/* Display */
			
			if(((unsigned int)mydirent->d_type) == 2)
			{
				sprintf(type, "Charractor Device");
			}

			if(((unsigned int)mydirent->d_type) == 4)
			{
				sprintf(type, "Directory");
			}
			
			if(((unsigned int)mydirent->d_type) == 6)
			{
				sprintf(type, "Block");
			}
			
			if(((unsigned int)mydirent->d_type) == 8)
			{
				sprintf(type, "Regular File");
			}
			
			if(((unsigned int)mydirent->d_type) == 10)
			{
				sprintf(type, "Link");
			}
			
			if(((unsigned int)mydirent->d_type) == 12)
			{
				sprintf(type, "Sock");
			}
			
			if(((unsigned int)mydirent->d_type) == 14)
			{
				sprintf(type, "White");
			}
			
			if(strcmp(mydirent->d_name, ".") == 0)
			{
				sprintf(type, "Current Directory");
			}
			if(strcmp(mydirent->d_name, "..") == 0)
			{
				sprintf(type, "Parent Directory");
			}
				
			/* Print contents  */
				
			//printf("%s %hhu\n", mydirent->d_name, mydirent->d_type);
			printf("[ %17s ] \t %s\n", type, mydirent->d_name);
			
			
			
		}




	closedir(dir);
	return 1;
}
