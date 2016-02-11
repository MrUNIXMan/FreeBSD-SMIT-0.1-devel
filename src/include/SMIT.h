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

Description: SMIT Header File which contains various stuff and declarations
	     for SMIT.

----------------------------------------------------------------------------------------
*/

#ifndef SMIT_H_
#define SMIT_H_

#include "SMITprotos.h"

#define PROGNAME "FreeBSD-SMIT"
#define VERSION	 "0.1"
#define COPYRIGHT "Copyright (C) 2015-2016 by Vincent"

/* Windows for Dialogs or Interfaces */

WINDOW *DLGERR; /* a Error MsgBox */
WINDOW *DLGINFO; /* a Info MsgBox */
WINDOW *DLGWARN; /* a Warning MsgBox */
WINDOW *DLGQUES; /* A Question MSGBOX */
WINDOW *DLGACTION; /* Dialog that mentions actions */

WINDOW *DLG; /* A Spare Dialog Box */
WINDOW *DLG2; /* Another Spare Dialog Box for General Use */
WINDOW *SPARE; /* A Spare Window for certain operations */

/* Uses /bin/sh as default on FreeBSD base */

static char defaultshell[] = "/bin/sh";
#define DEFAULT_SHELL "/bin/sh"


	
#endif
