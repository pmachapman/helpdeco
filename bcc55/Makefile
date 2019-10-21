CC = bcc32
CFLAGS = -O2

all: helpdeco splitmrb zapres

helpdeco:
		$(CC) $(CFLAGS) ../src/helpdeco.c ../src/helpdec1.c

splitmrb:
		$(CC) $(CFLAGS) ../src/splitmrb.c

zapres:
		$(CC) $(CFLAGS) ../src/zapres.c

clean:
		del *.obj
		del *.exe
		del *.tds
