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

Description: System Information Module

 * sysinfo.c - System Info program which has been used on many occassions while learning C
 * was decided to be included in to SMIT. However the whole program is entirely put in curses by myself
 * while some code came from either a book. The Code that contains uptime came from another user called YMRT when
 * a friend required help with C. This program was previously written as a console app without ncurses.
-------------------------------------------------------------------------------------------------------------- 
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pwd.h>
#include <time.h>
#include <sys/sysctl.h>
#include <sys/utsname.h>
#include <ncurses.h>
#include "../include/SMIT.h"



/* CPU Stuff Code given to us by YMRT in 2013 */

static const struct {
	const char *ctls;
	const char *names;
} values [] = {
	{ "hw.model", "CPU:" }
};

/* CPU Information function */

static void sysctls(int i)
{
	size_t len;
	if (i == 2) {
		/* Nothing Here */
	}
	else
	{
		sysctlbyname(values[i].ctls, NULL, &len, NULL, 0);
		char *type = malloc(len);
		sysctlbyname(values[i].ctls, type, &len, NULL, 0);
		attron(A_BOLD);
		mvprintw(11, 10, "%s", values[i].names);
		attroff(A_BOLD);
		mvprintw(11, 25, "%s", type);
		free(type);
	}
}

/* Uptime Information  Code Provided by YMRT */

static void uptime(time_t *nowp) {
	struct timeval boottime;
	time_t uptime;
	int days, hrs, mins, secs;
	int mib[2];
	size_t size;
	char buf[256];
	if(strftime(buf, sizeof(buf), NULL, localtime(nowp)))
		mib[0] = CTL_KERN;
	mib[1] = KERN_BOOTTIME; /* Requires sys/sysctl.h */
	size = sizeof(boottime);
	if(sysctl(mib, 2, &boottime, &size, NULL, 0) != -1 &&
		boottime.tv_sec) {
		uptime = *nowp - boottime.tv_sec;
		if(uptime > 60)
			uptime += 60;
		days = (int)uptime / 86400;
		uptime %= 86400;
		hrs = (int)uptime / 3600;
		uptime %= 3600;
		mins = (int)uptime / 60;
		secs = uptime % 60;
		
		/* Print Uptime */
		attron(A_BOLD);
		mvprintw(13, 10, "Uptime:");
		attroff(A_BOLD);
		mvprintw(13, 25, "%d day%s", days, days > 1? "s " : " ");
		if (hrs > 0 && mins > 0)
			mvprintw(13, 35, "%d:%d (hrs:mins)", hrs, mins);
		else if(hrs == 0 && mins > 0)
			mvprintw(13, 35, "00:%d (hrs:mins)", mins);
		else
			mvprintw(13, 35, "00:00 (hrs:mins)");
				
		
		
		
		}
	
}





int sysinfo(void)
{
	/* Declarations for System Info stuff */
	
	char computer[256];   /* Declare Keyword computer */
	struct utsname uts; /* Structure of uts from utsname */
	
	if(gethostname(computer, 255) !=0 || uname(&uts) < 0)
	{
		
		MsgBoxError("Unable to Open Host Information");
		
	}
	
	
	/* Declare Date and Time */
	
	time_t timeval;
	
	(void)time(&timeval);
	
	
	
	/* If the test passed then draw the screen */
	
	clear();
	box(stdscr, ACS_VLINE, ACS_HLINE);
	
	/* Print Various Stuff out to Screen */
	
	attron(A_UNDERLINE);
	mvprintw(1, 25, "%s System Information", PROGNAME); /* Title */
	attroff(A_UNDERLINE);

		
	attron(A_BOLD);
	
	mvprintw(3, 10, "Date/Time: ");
	mvprintw(5, 10, "Username: "); 
	mvprintw(6, 10, "Hostname: ");

	mvprintw(8, 10, "O/S: ");
	mvprintw(9, 10, "Release: ");
	mvprintw(10, 10, "ARCH: ");
	attroff(A_BOLD);

	/* The  information for each field */
	mvprintw(3, 25, "%s", ctime(&timeval));
	mvprintw(5, 25, "%s", getlogin());
	mvprintw(6, 25, "%s", computer);

	mvprintw(8, 25, "%s", uts.sysname);
	mvprintw(9, 25, "%s", uts.release);
	mvprintw(10, 25, "%s", uts.machine);
	
	sysctls(0); /* Run CPU Information */
	
	/* Uptime Stuff */
	time_t now;        
	time(&now);
	uptime(&now);
	
	
	
	mvprintw(17, 2, "Press Enter when finished viewing & return to previous");
	move(18,2); 
	

	/* Causes a Pause at the End */
	getch();
		
	return 0;
}
