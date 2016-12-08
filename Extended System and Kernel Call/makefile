# Name: (Ya) Naweeya Chutiraka
# UFID: 4663-3911
# Gator ID: nc10nchu

GCC=cc # this an example of a use of Macro
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)

# name the executable anything. I use the same name as its original here

all: procedure system library patching_table.c patching_callnr.h patching_proto.h patching_Makefile patching_unistd.h patching_Makefile.inc patching_forkexit.c

system:
	cd /usr/src/releasetools; make services; make install;
	
library:
	cd /usr/src; make build;  

procedure.o: procedure.c
	$(GCC) $(CFLAGS) procedure.c -c

procedure: procedure.o
	$(GCC) procedure.o -o procedure

patching_table.c: patch_table.c.txt	
	patch /usr/src/servers/pm/table.c patch_table.c.txt
	
patching_callnr.h: patch_callnr.h.txt
	patch /usr/src/include/minix/callnr.h patch_callnr.h.txt
	
patching_proto.h: patch_proto.h.txt
	patch /usr/src/servers/pm/proto.h patch_proto.h.txt
	
patching_Makefile: patch_Makefile.txt
	patch /usr/src/servers/pm/Makefile patch_Makefile.txt

patching_unistd.h: patch_unistd.h.txt
	patch /usr/src/include/unistd.h patch_unistd.h.txt

patching_Makefile.inc: patch_Makefile.inc.txt
	patch /usr/src/lib/libc/sys-minix/Makefile.inc patch_Makefile.inc.txt
	
patching_forkexit.c: patch_forkexit.c.txt
	patch /usr/src/servers/pm/forkexit.c patch_forkexit.c.txt

clean:
	rm -f procedure procedure.o

tarfile.tar:
	tar cvf Chutiraka_Proj1.tar makefile README.txt patch_table.c.txt patch_callnr.h.txt patch_proto.h.txt patch_Makefile.txt patch_unistd.h.txt patch_Makefile.inc.txt patch_forkexit.c.txt documentation.txt Buffer.h do_get_plog_byindex.c do_get_plog_byPID.c do_get_plog_size.c do_printmsg.c do_printppid.c do_reset_plog.c do_start_plog.c do_stop_plog.c get_plog_byindex.c get_plog_byPID.c get_plog_size.c start_plog.c stop_plog.c reset_plog.c procedure.c get_plog_byPID.2 get_plog_byindex.2 get_plog_size.2 start_plog.2 stop_plog.2 reset_plog.2
