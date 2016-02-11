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

 Rewritten vfslist.c by Vincent
 * All rights reserved.
 * 
 * This is a helper program used by mount and df they both will become something else
 * as it will be put in to SMIT.
 * 
 * Code used from vfslist.c from FreeBSD mount and was written by BSD.
 * 
 * 
 * 
-------------------------------------------------------------------------------------------------------------- 
 */
 
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

#include "../include/SMITextern.h"
#include "../include/SMIT.h"


static int skipvfilesystem;


int chkfilesysname(const char *VFSname, const char **VFSlst)
{
	if(VFSlst == NULL)
		return(0);
	while(*VFSlst != NULL) {
		if(strcmp(VFSname, *VFSlst) == 0)
			return(skipvfilesystem);
			++VFSlst;
		}
		return(!skipvfilesystem);
}
	
const char **mkfilesyslist(char *FileSystemList )
{
	const char **AV;
	int counter;
	char  *nextcp;
	
	if(FileSystemList == NULL)
		return(NULL);
	
	if(FileSystemList[0] == 'n' && FileSystemList[1] == 'o') {
		FileSystemList += 2;
		skipvfilesystem = 1;
	};
	
	for(counter = 1, nextcp = FileSystemList; *nextcp; nextcp++)
		if(*nextcp == ',')
		counter++;
		
	if((AV = malloc((size_t)(counter +2) * sizeof(char *))) == NULL) {
		MsgBoxError("VFSlist Malloc failed");
		return(NULL);
	};
	
	nextcp = FileSystemList;
	counter = 0;
	AV[counter++] = nextcp;
	
	while((nextcp = strchr(nextcp, ',')) != NULL) {
		*nextcp++ = '\0';
		AV[counter++] = nextcp;
	};
	AV[counter++] = NULL;
	return(AV);
	
	
}
