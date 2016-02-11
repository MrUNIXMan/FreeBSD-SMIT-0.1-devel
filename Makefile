CC = cc

RELEASEDIR = ../release
SRCHELP = ./help
DESTHELP = /usr/local/share/smit
INSTALLDIR = /usr/local
MANSRCDIR = ./man/man1
MANDESTDIR = /usr/local/man/man1
SRCDIR = ./src

bsdsmit:
	$(CC) -DTEST_BUILTIN -Wall -o smit -l util -l ncurses \
	$(SRCDIR)/smit.c \
	$(SRCDIR)/menus/mainmenu.c \
	$(SRCDIR)/menus/syscfgmenu.c \
	$(SRCDIR)/menus/kernel.c \
	$(SRCDIR)/menus/menufunc.c  \
	$(SRCDIR)/menus/sysinfomenu.c \
	$(SRCDIR)/shared/msgbox.c \
	$(SRCDIR)/shared/sharedfuncs.c \
	$(SRCDIR)/kernmgr/kernmgr.c \
	$(SRCDIR)/kernmgr/modules.c \
	$(SRCDIR)/kernmgr/kstatpad.c \
	$(SRCDIR)/help/helpprog.c \
	$(SRCDIR)/sysinfo/sysinfo.c \
	$(SRCDIR)/sysinfo/whoson.c \
	$(SRCDIR)/sysinfo/diskfree.c \
	$(SRCDIR)/fs/listfs.c \
	$(SRCDIR)/fs/fsmgr.c \
	$(SRCDIR)/fs/fsmgr-topmenu.c \
	$(SRCDIR)/fs/fstabopts.c \
	$(SRCDIR)/fs/mntumnt.c \
	$(SRCDIR)/shared/listvfilesys.c \
	$(SRCDIR)/shared/FSUI.c \
	$(SRCDIR)/cfg/sysconf.c \
	$(SRCDIR)/user/usermgr.c \
	$(SRCDIR)/user/grpmgr.c \
	$(SRCDIR)/user/addusers.c \
	$(SRCDIR)/user/removeuser.c \
	$(SRCDIR)/user/userinfo.c \
	$(SRCDIR)/menus/ugmenu.c
	
# Shell

	$(CC) -DTEST_BUILTIN -Wall -o SMITsh \
	shell/smitsh.c \
	shell/internalcmd/basic.c \
	shell/internalcmd/dir.c \
	shell/internalcmd/show.c \
	shell/internalcmd/set.c 



	
	

install:
	cp smit $(INSTALLDIR)/bin
	cp SMITsh $(INSTALLDIR)/bin

	cp -R smitty $(INSTALLDIR)/bin
	mkdir -p $(DESTHELP)
	cp $(SRCHELP)/* $(DESTHELP)
#	gzip -9 $(MANSRCDIR)/smit.1
	cp $(MANSRCDIR)/smit.1.gz $(MANDESTDIR)

release:
	mkdir $(RELEASEDIR)
	mkdir $(RELEASEDIR)/bin
	cp smit $(RELEASEDIR)/bin
	
	mkdir -p $(RELEASEDIR)/man/man1
	mkdir -p $(RELEASEDIR)/share/smit

	cp -R smitty $(RELEASEDIR)/bin
	mkdir -p $(DESTHELP)
	cp $(SRCHELP)/* $(RELEASEDIR)/share/smit
#	gzip -9 $(MANSRCDIR)/smit.1
	cp $(MANSRCDIR)/smit.1.gz $(RELEASEDIR)/man/man1



clean:
	rm *.o  smit SMITsh
#	gunzip $(MANSRCDIR)/smit.1.gz

