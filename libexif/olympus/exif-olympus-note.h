/* exif-olympus-note.h
 *
 * Copyright (C) 2002 Lutz M�ller <lutz@users.sourceforge.net>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful, 
 * but WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details. 
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#ifndef __EXIF_OLYMPUS_NOTE_H__
#define __EXIF_OLYMPUS_NOTE_H__

#include <libexif/exif-note.h>

typedef struct _ExifOlympusNote ExifOlympusNote;

#include <libexif/olympus/exif-olympus-entry.h>

struct _ExifOlympusNote {
	ExifNote parent;

	ExifOlympusEntry **entries;
	unsigned int count;
};

ExifNote *exif_olympus_note_new (void);

#endif /* __EXIF_OLYMPUS_NOTE_H__ */
