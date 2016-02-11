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
*---------------------------------------------------------------------------------------
*
* Description: Shared MesgBox functions.  The MsgBox name does come out of Visual Basic
* but is used to display messages on SMIT so the code is re-used here.
* -------------------------------------------------------------------------------------
*/


#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include <unistd.h>
#include <sys/utsname.h>
#include "../include/SMITMenus.h"
#include "../include/SMIT.h"

int x, y;

/* Use of MsgBox ideas does come out of Visual Basic. Which then is used in C 
 * with the following stements below.
 * 
 * According to an artical if you cannot make a MSGBox by Coding then you have not
 * properly learned programming. This is sadly the case with Visual Basic.*/
 
/* Error Message BOX */

int MsgBoxError(char *errmsg)
{
			SPARE  = newwin(8,53,5,14);
			box(SPARE, ACS_VLINE, ACS_HLINE);
			wattron(SPARE, A_UNDERLINE | A_BOLD);
			mvwprintw(SPARE, 1, 20, "SMIT ERROR");
			wattroff(SPARE, A_UNDERLINE | A_BOLD);
			wrefresh(SPARE);
			DLGERR = newwin(5,51,7,15);   /* Dialog Declared at WINDOW */
	
			
			mvwprintw(DLGERR, 1, 2, "%s", errmsg);
			wrefresh(DLGERR);
			wgetch(DLGERR);
			werase(DLGERR);
			werase(SPARE);
	
	return 0;
}

/* Info Message Box */

int MsgBoxInfo(char *infomsg)
{
			SPARE  = newwin(8,53,5,14);
			box(SPARE, ACS_VLINE, ACS_HLINE);
			wattron(SPARE, A_UNDERLINE | A_BOLD);
			mvwprintw(SPARE, 1, 20, "INFORMATION");
			wattroff(SPARE, A_UNDERLINE | A_BOLD);
			wrefresh(SPARE);
	
			DLGINFO = newwin(5,51,7,15);   /* Dialog Declared at WINDOW */
		
		
			mvwprintw(DLGINFO, 1, 2, "%s", infomsg);
			wrefresh(DLGINFO);
			//napms(1000);
			wgetch(DLGINFO);
			werase(DLGINFO);
	
	return 0;
}

int MsgBoxInfoNoPause(char *infomsg)
{
			SPARE  = newwin(8,53,5,14);
			box(SPARE, ACS_VLINE, ACS_HLINE);
			wattron(SPARE, A_UNDERLINE | A_BOLD);
			mvwprintw(SPARE, 1, 20, "INFORMATION");
			wattroff(SPARE, A_UNDERLINE | A_BOLD);
			wrefresh(SPARE);
	
			DLGINFO = newwin(5,51,7,15);   /* Dialog Declared at WINDOW */
		
		
			mvwprintw(DLGINFO, 1, 2, "%s", infomsg);
			wrefresh(DLGINFO);
			napms(1000);
		
			werase(DLGINFO);
	
	return 0;
}


/* Warning Message Box */


int MsgBoxWarn(char *warnmsg)
{
			SPARE  = newwin(8,53,5,14);
			box(SPARE, ACS_VLINE, ACS_HLINE);
			wattron(SPARE, A_UNDERLINE | A_BOLD);
			mvwprintw(SPARE, 1, 20, "WARNING");
			wattroff(SPARE, A_UNDERLINE | A_BOLD);
			wrefresh(SPARE);
			
			DLGWARN = newwin(5,51,7,15);   /* Dialog Declared at WINDOW */
			
			mvwprintw(DLGWARN, 1, 2, "%s", warnmsg);
			wrefresh(DLGWARN);
			wgetch(DLGWARN);
			werase(DLGWARN);
	
	return 0;
}

int MsgBoxQuestion(char *qmsg, char *qans)
{
			SPARE  = newwin(8,53,5,14);
			box(SPARE, ACS_VLINE, ACS_HLINE);
			wattron(SPARE, A_UNDERLINE | A_BOLD);
			mvwprintw(SPARE, 1, 20, "QUESTION");
			wattroff(SPARE, A_UNDERLINE | A_BOLD);
			wrefresh(SPARE);
			
			DLGQUES = newwin(5,51,7,15);   /* Dialog Declared at WINDOW */
			
			mvwprintw(DLGQUES, 1, 2, "%s", qmsg);
			mvwprintw(DLGQUES, 2, 2, "%s", qans);
			wrefresh(DLGQUES);
	
	
	return 0;
}

int MsgBoxFileNotFound(char *filename, char *errmsg)
{
			SPARE  = newwin(8,53,5,14);
			box(SPARE, ACS_VLINE, ACS_HLINE);
			wattron(SPARE, A_UNDERLINE | A_BOLD);
			mvwprintw(SPARE, 1, 20, "SMIT ERROR");
			wattroff(SPARE, A_UNDERLINE | A_BOLD);
			wrefresh(SPARE);
			DLGERR = newwin(5,51,7,15);   /* Dialog Declared at WINDOW */
	
			mvwprintw(DLGERR, 1, 2, "Filename: %s", filename);
			mvwprintw(DLGERR, 2, 2, "%s", errmsg);
			wrefresh(DLGERR);
			wgetch(DLGERR);
			werase(DLGERR);
	
	return 0;
}

int MsgBoxCommence(char *title, char *CMSG)
{
			int countdown = 5;
			
			while(countdown != 0) {
			SPARE  = newwin(8,53,5,14);
			box(SPARE, ACS_VLINE, ACS_HLINE);
			wattron(SPARE, A_UNDERLINE | A_BOLD);
			mvwprintw(SPARE, 1, 13, "%s", title);
			wattroff(SPARE, A_UNDERLINE | A_BOLD);
			wrefresh(SPARE);
			DLGACTION = newwin(5,51,7,15);   /* Dialog Declared at WINDOW */
	
			mvwprintw(DLGACTION, 1, 2, "%s  starts in %d" , CMSG, countdown);
			mvwprintw(DLGACTION, 3, 2, "Whatever Key to Abort");
			wrefresh(DLGACTION);
			sleep(1);
			countdown--;
		}
			
			
			
	return 0;	
}

int RootPriv()
{
			SPARE  = newwin(8,53,5,14);
			box(SPARE, ACS_VLINE, ACS_HLINE);
			wattron(SPARE, A_UNDERLINE | A_BOLD);
			mvwprintw(SPARE, 1, 10, "This requires root's privileages");
			wattroff(SPARE, A_UNDERLINE | A_BOLD);
			wrefresh(SPARE);
			
			DLG = newwin(5,51,7,15);   /* Dialog Declared at WINDOW */
			
			mvwprintw(DLG, 1, 2, "Cannot Perform actions without");
			mvwprintw(DLG, 2, 2, "root's privileges");
			mvwprintw(DLG, 3, 2, "Press Enter to return");
			wrefresh(DLG);
			wgetch(DLG);
	
	
	return 0;
}

int MsgBoxKern(char *kfilename, char *kmsg)
{
			SPARE  = newwin(8,53,5,14);
			box(SPARE, ACS_VLINE, ACS_HLINE);
			wattron(SPARE, A_UNDERLINE | A_BOLD);
			mvwprintw(SPARE, 1, 18, "Kernel Module Information");
			wattroff(SPARE, A_UNDERLINE | A_BOLD);
			wrefresh(SPARE);
	
			DLGINFO = newwin(5,51,7,15);   /* Dialog Declared at WINDOW */
		
		
			mvwprintw(DLGINFO, 1, 2, "%s", kfilename);
			mvwprintw(DLGINFO, 2, 2, "%s", kmsg);
			wrefresh(DLGINFO);
			napms(3000);
			werase(DLGINFO);
	
	return 0;
}

int MsgBoxUser(char *login, char *msg)
{
			SPARE  = newwin(8,53,5,14);
			box(SPARE, ACS_VLINE, ACS_HLINE);
			wattron(SPARE, A_UNDERLINE | A_BOLD);
			mvwprintw(SPARE, 1, 18, "Manage User: %s", login);
			wattroff(SPARE, A_UNDERLINE | A_BOLD);
			wrefresh(SPARE);
	
			DLGINFO = newwin(5,51,7,15);   /* Dialog Declared at WINDOW */
		
		
			mvwprintw(DLGINFO, 1, 2, "%s", msg);
			mvwprintw(DLGINFO, 2, 2, "%s", login);
			wrefresh(DLGINFO);
			napms(4000);
			werase(DLGINFO);
	
	return 0;
}

int MsgBoxWaitPid()
{
			SPARE  = newwin(8,53,5,14);
			box(SPARE, ACS_VLINE, ACS_HLINE);
			wattron(SPARE, A_UNDERLINE | A_BOLD);
			mvwprintw(SPARE, 1, 18, "Waiting for Child Process");
			wattroff(SPARE, A_UNDERLINE | A_BOLD);
			wrefresh(SPARE);
	
			DLGINFO = newwin(5,51,7,15);   /* Dialog Declared at WINDOW */
		
			mvwprintw(DLGINFO, 2, 2, "Waitng for a process to end before returning");
			wrefresh(DLGINFO);
			napms(4000);
			werase(DLGINFO);
	
	return 0;
}

