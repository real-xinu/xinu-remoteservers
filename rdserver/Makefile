#########################################################################
#									#
#									#
#  Makefile for the remote disk server (rdserver)			#
#									#
#									#
#########################################################################

# Ensure one and only one of the following are set
#DEBUGFLAGS= 	-DDEBUG
DEBUGFLAGS=

all:		rdserver rddump

rddump:		rddump.c
		gcc -o rddump rddump.c

rdserver:	rdserver.o rdopen.o rdclose.o rdread.o rdwrite.o	\
		rddelete.o rdofile.o snderr.o sndok.o
		gcc -o rdserver rdserver.o rdopen.o			\
			rdclose.o rdread.o rdwrite.o rddelete.o		\
			rdofile.o snderr.o sndok.o

rdserver.o:	rdserver.c rdserver.h
		gcc $(DEBUGFLAGS) -c rdserver.c

clean:
		rm -f *.o .,* core rdserver rddump

rdopen.o:	rdopen.c rdserver.h
		gcc $(DEBUGFLAGS) -c rdopen.c

rdclose.o:	rdclose.c rdserver.h
		gcc $(DEBUGFLAGS) -c rdclose.c

rdread.o:	rdread.c rdserver.h
		gcc $(DEBUGFLAGS) -c rdread.c

rdwrite.o:	rdwrite.c rdserver.h
		gcc $(DEBUGFLAGS) -c rdwrite.c

rddelete.o:	rddelete.c rdserver.h
		gcc $(DEBUGFLAGS) -c rddelete.c

rdofile.o:	rdofile.c rdserver.h
		gcc $(DEBUGFLAGS) -c rdofile.c

snderr.o:	snderr.c rdserver.h
		gcc $(DEBUGFLAGS) -c snderr.c

sndok.o:	sndok.c rdserver.h
		gcc $(DEBUGFLAGS) -c sndok.c
