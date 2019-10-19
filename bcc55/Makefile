CC = bcc32
CFLAGS = -P -O2 -w

all: helpdeco splitmrb zapres

helpdeco:
		$(CC) $(CFLAGS) ../src/helpdec1.c ../src/helpdeco.c

splitmrb:
		$(CC) $(CFLAGS) ../src/splitmrb.c

zapres:
		$(CC) $(CFLAGS) ../src/zapres.c

clean:
		del *.obj
		del *.exe
		del *.tds
