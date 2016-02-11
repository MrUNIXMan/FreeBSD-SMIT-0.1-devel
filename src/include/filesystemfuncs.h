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

 Rewritten pathnames.h by Vincent
 * All rights reserved.
 * 
 * 
 * Code used from pathnames.h from FreeBSD mount and was written by BSD.
 * 
 * ReWritten version of list mounted filesystem using Mount as 
 * a way to write this.
 * 
 * 
 * 
-------------------------------------------------------------------------------------------------------------- 
 */

#ifndef FILESYSTEMFUNCS_H_
#define FILESYSTEMFUNCS_H_

#define ESC 27

WINDOW *FSPAD;
static int counter_FS = 15;  // Counter Starts at 15 to keep it almost in middle

/*
static void printstat(struct statfs *sfsp, struct maxWidths *mwp);
static void update_maxwidths(struct maxWidths *mwp, const struct statfs *sfsp); */

#define FSMGR_MENU_MAX  5

/* Menu Windows */
WINDOW *FSTABMENU;
WINDOW *VIEWMENU;
WINDOW *DISKMENU;

#define VIEWMENU_MAX 3
#define FSTABMENU_MAX 5
#define DISKMENU_MAX 7

/* Buffer */
static char fsmgrbuf[256];


/* For Anything related to /etc/fstab */

struct FstabFields  {
	char Device[256];
	char MntDir[256];
	char Fstyp[256];
	char Option[256];
	char Dump[4];
	char pass[4];
 };




#endif

