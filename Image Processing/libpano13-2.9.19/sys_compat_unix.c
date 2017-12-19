/* Panorama_Tools	-	Generate, Edit and Convert Panoramic Images
   Copyright (C) 1998,1999 - Helmut Dersch  der@fh-furtwangen.de
   
   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this software; see the file COPYING.  If not, a copy
   can be downloaded from http://www.gnu.org/licenses/gpl.html, or
   obtained by writing to the Free Software Foundation, Inc.,
   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.  */

/*------------------------------------------------------------*/

#include "sys_compat.h"
#include <assert.h>

#ifdef __APPLE__
#include <stdlib.h>
#endif

int panoTimeToStrWithTimeZone(char *sTime, int len, struct tm  *time) 
{
    assert(len >= 11);
    return strftime(sTime, len, "%H%M%S%z", time);

}

char *panoBasenameOfExecutable(void)
{
#ifdef __APPLE__
    return getprogname();
#else
    extern char *__progname;
    return __progname;
#endif
}
