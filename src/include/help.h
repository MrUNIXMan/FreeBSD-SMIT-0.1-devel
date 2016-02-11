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

Description: FreeBSD-SMIT Help Viewer
This module displays Help.
----------------------------------------------------------------------------------------
*/

 #ifndef HELP_H_
 #define HELP_H_
 
 /* Max Char Per Line */
 #define MAX_CHAR 500
 

 #define HELP_PATH "/usr/local/share/smit/"
 
 /* Help Files */
 #define MAIN_HELP_FILE "smitmainhlp.txt"  // Main Menu
 #define USER_HELP_FILE "usrmenuhelp.txt"  // User Menu
 #define USERMGR_HELP "usrmgrhelp.txt" // User Manager Help
 #define KERNEL_MGR_HELP "kernelmgr.txt" // Kernel Mgr
 #define ADDTOFSTAB_HELP "addtofstab.txt" // Add to Fstab Help
 
 
 int readhelpfile();
 int DrawHelpScreen();
 int help_func(char *help);
 
 #endif
 
 
 
