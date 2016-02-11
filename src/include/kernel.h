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

Description: Kernel Related header Files

----------------------------------------------------------------------------------------
*/

#ifndef KERNEL_H_
#define KERNEL_H_

#define SELECT_CFG_MAX 4
#define KERNEL_BUFFER 20



char buf[256];
char dirbuf[256]; /* Dir putting dir and filenames to gether */

char computer[256];
int errorlevel; /* Determines errors */
int archlevel;  /*0 = AMD64, 1=i386 */	


/* Kernel Directories for Arch */
static char AMD64Conf[] = "/usr/src/sys/amd64/conf";
static char I386Conf[] = "/usr/src/sys/i386/conf";



/* Source Directory and Kernel Config File dirs */
static char srcdir[] = "/usr/src";


/* Master Kernel Config Files to copy from */
static char GENERIC_FILE[] = "GENERIC";
static char GENERIC_NODEBUG_FILE[] = "GENERIC-NODEBUG";

/* Kernel Config File to accept at input as it is required on the Menu too*/
char conffile[256];

/* /boot and kernel modules */
	
static char kernelmoddir[]= "/boot/kernel";
	
	
#endif
