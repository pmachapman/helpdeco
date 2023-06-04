# helpdeco -- utility program to dissect Windows help files
# Copyright (C) 2005 Paul Wise

# This file is part of helpdeco; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software Foundation,
# Inc., 59 Temple Place, Suite 330, Boston, MA, 02111-1307, USA or visit:
# http://www.gnu.org

prefix = /usr/local
distdir = helpdeco-2.1.4
vpath = ../src
files = \
        ../src/compat.c \
        ../src/compat.h \
        ../src/helpdec1.c \
        ../src/helpdeco.c \
        ../src/helpdeco.h \
        ../src/splitmrb.c \
        ../src/zapres.c \
        Makefile \
        ../helpfile.txt \
        ../NEWS \
        ../README \
        ../README.de \
        ../LICENSE \
        ../TODO

CC=clang
CFLAGS+=-O -Weverything
LDFLAGS+=-s

all: build

build: helpdeco splitmrb zapres

helpdeco: ../src/helpdeco.o ../src/helpdec1.o ../src/compat.o
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

splitmrb: ../src/splitmrb.o ../src/compat.o
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

zapres: ../src/zapres.o ../src/compat.o
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

clean:
	rm -f ../src/*.o helpdeco zapres splitmrb

install: build
	-mkdir $(prefix) $(prefix)/bin $(prefix)/share $(prefix)/share/doc $(prefix)/share/doc/helpdeco
	install helpdeco zapres splitmrb $(prefix)/bin
	install README README.de NEWS helpfile.txt $(prefix)/share/doc/helpdeco

dist:
	-rm -rf $(distdir)
	mkdir -p $(distdir)/src
	for file in $(files); do \
	  if test -d $$file; then \
	    cp -p --recursive $$file $(distdir)/src/$$file; \
	  else \
	    test -f $(distdir)/$$file \
	    || cp -p $$file $(distdir)/src/$$file; \
	  fi; \
	done
	tar --gzip --create --file $(distdir).tar.gz $(distdir)
	-rm -rf $(distdir)

ChangeLog:
	git2cl
