/*
helpdeco -- utility program to dissect Windows help files
Copyright (C) 1996 Manfred Winterhoff
Copyright (C) 2001 Ben Collver

This file is part of helpdeco; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software Foundation,
Inc., 59 Temple Place, Suite 330, Boston, MA, 02111-1307, USA or visit:
http://www.gnu.org
*/

/*
ZAPRES - removes resolution information from Windows bitmap files - Version 1.1
M.Winterhoff <mawin@gmx.net>, Geschw.-Scholl-Ring 17, 38444 Wolfsburg, Germany

usage:	ZAPRES filename1[.BMP] filename2[.BMP] ...

option: Normally ZAPRES will create a .BAK file before it attempts to modify
	the input file. Specify option /b if you don't want to backup files.

This program removes the resolution information from Windows .BMP bitmaps, .MRB
multi resolution bitmaps, and .SHG segmented hotspot graphics. This way WinHelp
will not rescale the image and MRBC can be applied to specify a new resolution.
*/

#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#ifndef _WIN32
#include <sys/dir.h>
#endif
#include <string.h>
#ifdef _WIN32
#include "helper.h"
#else
#include "compat.h"
#endif

int backup(FILE* f, char* oldname)
{
	char drive[_MAX_DRIVE], dir[PATH_MAX], fname[NAME_MAX], ext[_MAX_EXT];
	char path[PATH_MAX];
	char buffer[512];
	long pos, size;
	size_t bytes;
	FILE* bak;
	int result = 0;

	_splitpath(oldname, drive, dir, fname, ext);
	_makepath(path, drive, dir, fname, ".bak");
	bak = fopen(path, "wb");
	if (bak)
	{
		result = 1;
		pos = ftell(f);
		fseek(f, 0L, SEEK_END);
		size = ftell(f);
		fseek(f, 0L, SEEK_SET);
		while (size)
		{
			bytes = size > sizeof(buffer) ? sizeof(buffer) : size;
			if (fread(buffer, 1, bytes, f) != bytes)
			{
				fprintf(stderr, "Can not read from %s\n", oldname);
				result = 0;
				break;
			}
			if (fwrite(buffer, 1, bytes, bak) != bytes)
			{
				fprintf(stderr, "Can not write to %s\n", path);
				result = 0;
				break;
			}
			size -= bytes;
		}
		fclose(bak);
		fseek(f, pos, SEEK_SET);
	}
	else
	{
		fprintf(stderr, "Can not create %s\n", path);
	}
	return result;
}

int main(int argc, char* argv[])
{
	FILE* f;
	int b, n, i, k, bb;
	long w, h, zero, pos;
	char drive[_MAX_DRIVE], dir[PATH_MAX], fname[NAME_MAX], ext[_MAX_EXT];
	char path[PATH_MAX];

	for (b = i = 1; i < argc; i++)
	{
		if (stricmp(argv[i], "/b") != 0 && stricmp(argv[i], "-b") != 0)
		{
			argv[b++] = argv[i];
		}
	}
	if (b < 2)
	{
		printf("ZAPRES - removes resolution information from Windows bitmap files - Version 1.1\n"
			"M.Winterhoff <mawin@gmx.net>, Geschw.-Scholl-Ring 17, 38444 Wolfsburg, Germany\n"
			"\n"
			"usage:	ZAPRES filename1[.BMP] filename2[.BMP] ...\n"
			"\n"
			"option: Normally ZAPRES will create a .BAK file before it attempts to modify\n"
			"	the input file. Specify option /b if you don't want to backup files.\n"
			"\n"
			"This program removes the resolution information from Windows .BMP bitmaps, .MRB\n"
			"multi resolution bitmaps, and .SHG segmented hotspot graphics. This way WinHelp\n"
			"will not rescale the image and MRBC can be applied to specify a new resolution.\n"
			"\n");
	}
	else for (i = 1; i < b; i++)
	{
		_splitpath(argv[i], drive, dir, fname, ext);
		if (!ext[0]) strcpy(ext, ".bmp");
		_makepath(path, drive, dir, fname, ext);
		f = fopen(path, "r+b");
		if (f)
		{
			n = getw(f);
			if (n == 0x4D42)
			{
				fseek(f, 38L, SEEK_SET);
				fread(&w, sizeof(long), 1, f);
				fread(&h, sizeof(long), 1, f);
				if (w == 0 && h == 0)
				{
					fprintf(stderr, "Resolution was already removed from %s\n", path);
				}
				else if (b < argc || backup(f, path))
				{
					fseek(f, 38L, SEEK_SET);
					zero = 0;
					fwrite(&zero, sizeof(long), 1, f);
					fwrite(&zero, sizeof(long), 1, f);
					fprintf(stderr, "Resolution %lux%lu (%ldx%ld dpi) removed from %s\n", w, h, (w * 2) / 79, (h * 2) / 79, path);
				}
			}
			else if (n == 0x506C || n == 0x706C)
			{
				n = getw(f); /* number of bitmaps */
				bb = 0;
				for (k = 0; k < n; k++)
				{
					fseek(f, 4L + 4 * k, SEEK_SET);
					fread(&pos, sizeof(pos), 1, f);
					fseek(f, pos, SEEK_SET);
					switch (getc(f)) /* picture type */
					{
					case 5: /* DDB */
					case 6: /* DIB */
						getc(f); /* packing method ignored */
						w = getw(f);
						if (w & 1) w |= (long)getw(f) << 16;
						h = getw(f);
						if (h & 1) h |= (long)getw(f) << 16;
						if (w / 2 == 0 && h / 2 == 0)
						{
							fprintf(stderr, "Resolution was already removed from bitmap %u of %s\n", k, path);
						}
						else if (b < argc || bb || backup(f, path))
						{
							fseek(f, pos + 2, SEEK_SET);
							zero = w & 1;
							fwrite(&zero, (w & 1) + 1, 2, f);
							zero = h & 1;
							fwrite(&zero, (h & 1) + 1, 2, f);
							fprintf(stderr, "Resolution %lux%lu removed from bitmap %u of %s\n", w / 2, h / 2, k, path);
							bb = 1;
						}
					}
				}
			}
			else
			{
				fprintf(stderr, "%s is no valid Windows .BMP, .MRB, or .SHG file\n", path);
			}
			fclose(f);
		}
		else
		{
			fprintf(stderr, "Can not open %s\n", path);
		}
	}
	return 0;
}
