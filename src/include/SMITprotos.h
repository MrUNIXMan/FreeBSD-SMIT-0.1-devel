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
	     
	     This one is for Protoypes of functions which often are reported
	     when compiling

----------------------------------------------------------------------------------------
*/

#ifndef SMITPROTOS_H_
#define SMITPROTOS_H_



/* Start Main Smit */
	
int startsmit();


/* Menu Controls */
int execute_default_shell();

/* Sorts out screen */
void use_console();
void restore_curses();


/* Allows pausing in the console */
void consolepause(void);


/* Menu Specific */
void drawmenuscreen();

/* Main Menu */
void DrawMainMenuUI(int mainmenuitem);

/* System Config Menu */
void DrawSysConfigMenu(int syscfgitem);

/* Main of SysCfg Menu */
int syscfgmenu();

/* System Info menu */
void DrawSysInfoMenu(int SysInfoMNUItem);
int sysinfomenu();

/* Kernel */
void DrawKernelMenuUI(int KernelMenuItem);
int startkernmenu();
int SelectDefaultConfigFiles();
void DrawSelectCFGFile(int cfgitem);
int load_kernel_module();
int unload_kernel_module();
int copycfgfile(char *cfgfile);
int Use_Existing_Kernel_Conf_file();
int EditKernelConfigFile(void);
int CompileKernel(void);
int InstallKernel(void);
int Check_File_and_Dir();

/* Kernel Module Viewer */
int ShowLoadedKernelModules();

/* Kernel Modules Unload/Load */
int kernel_module_inputbox();
int unload_kernel_module_inputbox();	



/* Both Deals with the Kernel Compiling and Installing via fork */
int execute_kernel_compile();
int install_kernel_execution();
int kernel_executes(char *argument);
int DoKernelStuff(char *argument);

/* Message Boxes - See msgbox.c */

int MsgBoxQuestion(char *qmsg, char *qans); /* Question */
int MsgBoxWarn(char *warnmsg);  /* Warning */
int MsgBoxInfo(char *infomsg);  /* Info */
int MsgBoxError(char *errmsg);  /* Error */
int MsgBoxFileNotFound(char *filename, char *errmsg);
int MsgBoxCommence(char *title, char *CMSG);
int RootPriv();
int MsgBoxKern(char *kfilename, char *kmsg);
int MsgBoxWaitPid();
int MsgBoxUser(char *login, char *msg);
int MsgBoxInfoNoPause(char *infomsg);

/* SMIT HELP */

int help_func(char *help);
int DrawHelpScreen();
int readhelpfile();

/* System Config */

int edit_file(char *arg);
void do_edit_file();

/* User Manager */
int UserMgr();
int DrawUserMgrScreen(int useritem);

/* User & group menu */
int userandgroupmenu();
void DrawUserandGroupMenu(int ugmenuitem);
int GroupMgr(); // Group Manager

/* Logged in Users */
int ShowLoggedUsers();

/* Add User */
void DrawAddUserScreen();
int useradd();
int add_user();

/* Remove Users */
int removeuser(void);

/* User Info */
int userinfo(void);
int progerror(void);

/* System Info */

int sysinfo(void);

/* Filesystem Stuff */
int DrawFSDefaultScreen(char *title);
int showmountedfs();
int showdiskspace();

int mntlistmain();
int showdiskspace();
int chkfilesysname(const char *VFSname, const char **VFSlst);

/* Filesystem Mgr */

int FilesystemManager();
int process_filesystem_lists();
/* Menus */

int showFstabMenu();
int ShowViewMenu();


int AddtoFstab();


int Mountafs();
int Unmount_Fs();

int ShowDiskMenu();

#endif
