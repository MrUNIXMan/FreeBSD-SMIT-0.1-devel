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

Description: Menu Specific Header Files

----------------------------------------------------------------------------------------
*/

#ifndef SMITMENUS_H_
#define SMITMENUS_H_

/* Controls and Messages */

/* Global Chars to be reused*/
 
   static char mesg[] = "Please move the cursor to the desired item and press Enter";
   static char FKEY1[] = "F1=Help		F2=Refresh		F3=Cancel";
   static char FKEY2[] = "F9=Shell		F10=Quit		Enter=Do"; 			/*Controls on bottom */



/* MAX Menu Items for Each Menus */

/* Main Menu */
#define MAINMENU_MAX 9

/* Sysconfig Menu */
#define SYSCFGMENU_MAX 8

/* Kernel Configuration Manager Menu */

  #define KERN_MENU_MAX 9

/* Sys Information */

#define SYSINFOMENU_MAX 9

/* User & Group */
#define USER_MENU_MAX 9



#endif
