.include <bsd.own.mk>

# Makefile for Process Manager (PM)
PROG=	pm
SRCS=	main.c forkexit.c break.c exec.c time.c alarm.c \
	signal.c utility.c table.c getset.c misc.c \
	profile.c schedule.c do_printmsg.c do_printppid.c do_start_plog.c \
	do_stop_plog.c do_reset_plog.c do_get_plog_size.c do_get_plog_byPID.c \
	do_get_plog_byindex.c Buffer.h do_plog.c mproc.h pm.h plog_buffer_entry.h

.if ${USE_MCONTEXT} != "no"
SRCS+= mcontext.c
CPPFLAGS+= -DUSE_MCONTEXT
.endif

.if ${USE_TRACE} != "no"
SRCS+= trace.c
CPPFLAGS+= -DUSE_TRACE
.endif

DPADD+=	${LIBSYS} ${LIBTIMERS}
LDADD+=	-lsys -ltimers

MAN=

BINDIR?= /usr/sbin

CPPFLAGS.main.c+=	-I${NETBSDSRCDIR}
CPPFLAGS.misc.c+=	-I${NETBSDSRCDIR}
CPPFLAGS.schedule.c+=	-I${NETBSDSRCDIR}
CPPFLAGS.utility.c+=	-I${NETBSDSRCDIR}

.include <minix.bootprog.mk>
