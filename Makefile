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

build: helpdeco splitmrb zapres

helpdeco: helpdeco.o helpdec1.o compat.o

zapres: zapres.o compat.o

clean:
	rm -f *.o helpdeco zapres splitmrb

install:
	install helpdeco zapres splitmrb $(prefix)/bin
	install README README.de NEWS helpfile.txt $(prefix)/share/doc