/* exif-utils.c
 *
 * Copyright � 2001 Lutz M�ller <lutz@users.sourceforge.net>
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

#include <config.h>

#include <libexif/exif-utils.h>

typedef signed short ExifSShort;

void
exif_array_set_byte_order (ExifFormat f, unsigned char *b, unsigned int n,
		ExifByteOrder o_orig, ExifByteOrder o_new)
{
	unsigned int j;
	unsigned int fs = exif_format_get_size (f);
	ExifShort s;
	ExifLong l;
	ExifSLong sl;
	ExifRational r;
	ExifSRational sr;

	if (!b || !n) return;

	switch (f) {
	case EXIF_FORMAT_SHORT:
		for (j = 0; j < n; j++) {
			s = exif_get_short (b + j * fs, o_orig);
			exif_set_short (b + j * fs, o_new, s);
		}
		break;
	case EXIF_FORMAT_LONG:
		for (j = 0; j < n; j++) {
			l = exif_get_long (b + j * fs, o_orig);
			exif_set_long (b + j * fs, o_new, l);
		}
		break;
	case EXIF_FORMAT_RATIONAL:
		for (j = 0; j < n; j++) {
			r = exif_get_rational (b + j * fs, o_orig);
			exif_set_rational (b + j * fs, o_new, r);
		}
		break;
	case EXIF_FORMAT_SLONG:
		for (j = 0; j < n; j++) {
			sl = exif_get_slong (b + j * fs, o_orig);
			exif_set_slong (b + j * fs, o_new, sl);
		}
		break;
	case EXIF_FORMAT_SRATIONAL:
		for (j = 0; j < n; j++) {
			sr = exif_get_srational (b + j * fs, o_orig);
			exif_set_srational (b + j * fs, o_new, sr);
		}
		break;
	case EXIF_FORMAT_UNDEFINED:
	case EXIF_FORMAT_BYTE:
	case EXIF_FORMAT_ASCII:
	default:
		/* Nothing here. */
		break;
	}
}

static ExifSShort
exif_get_sshort (const unsigned char *buf, ExifByteOrder order)
{
	if (!buf) return 0;
        switch (order) {
        case EXIF_BYTE_ORDER_MOTOROLA:
                return ((buf[0] << 8) | buf[1]);
        case EXIF_BYTE_ORDER_INTEL:
                return ((buf[1] << 8) | buf[0]);
        }

	/* Won't be reached */
	return (0);
}

ExifShort
exif_get_short (const unsigned char *buf, ExifByteOrder order)
{
	return (exif_get_sshort (buf, order) & 0xffff);
}

void
exif_set_short (unsigned char *b, ExifByteOrder order, ExifShort value)
{
	if (!b) return;
	switch (order) {
	case EXIF_BYTE_ORDER_MOTOROLA:
		b[0] = (unsigned char) (value >> 8);
		b[1] = (unsigned char) value;
		break;
	case EXIF_BYTE_ORDER_INTEL:
		b[0] = (unsigned char) value;
		b[1] = (unsigned char) (value >> 8);
		break;
	}
}

ExifSLong
exif_get_slong (const unsigned char *b, ExifByteOrder order)
{
	if (!b) return 0;
        switch (order) {
        case EXIF_BYTE_ORDER_MOTOROLA:
                return ((b[0] << 24) | (b[1] << 16) | (b[2] << 8) | b[3]);
        case EXIF_BYTE_ORDER_INTEL:
                return ((b[3] << 24) | (b[2] << 16) | (b[1] << 8) | b[0]);
        }

	/* Won't be reached */
	return (0);
}

void
exif_set_slong (unsigned char *b, ExifByteOrder order, ExifSLong value)
{
	if (!b) return;
	switch (order) {
	case EXIF_BYTE_ORDER_MOTOROLA:
		b[0] = (unsigned char) (value >> 24);
		b[1] = (unsigned char) (value >> 16);
		b[2] = (unsigned char) (value >> 8);
		b[3] = (unsigned char) value;
		break;
	case EXIF_BYTE_ORDER_INTEL:
		b[3] = (unsigned char) (value >> 24);
		b[2] = (unsigned char) (value >> 16);
		b[1] = (unsigned char) (value >> 8);
		b[0] = (unsigned char) value;
		break;
	}
}

ExifLong
exif_get_long (const unsigned char *buf, ExifByteOrder order)
{
        return (exif_get_slong (buf, order) & 0xffffffff);
}

void
exif_set_long (unsigned char *b, ExifByteOrder order, ExifLong value)
{
	exif_set_slong (b, order, value);
}

ExifSRational
exif_get_srational (const unsigned char *buf, ExifByteOrder order)
{
	ExifSRational r;

	r.numerator   = buf ? exif_get_slong (buf, order) : 0;
	r.denominator = buf ? exif_get_slong (buf + 4, order) : 0;

	return (r);
}

ExifRational
exif_get_rational (const unsigned char *buf, ExifByteOrder order)
{
	ExifRational r;

	r.numerator   = buf ? exif_get_long (buf, order) : 0;
	r.denominator = buf ? exif_get_long (buf + 4, order) : 0;

	return (r);
}

void
exif_set_rational (unsigned char *buf, ExifByteOrder order,
		   ExifRational value)
{
	if (!buf) return;
	exif_set_long (buf, order, value.numerator);
	exif_set_long (buf + 4, order, value.denominator);
}

void
exif_set_srational (unsigned char *buf, ExifByteOrder order,
		    ExifSRational value)
{
	if (!buf) return;
	exif_set_slong (buf, order, value.numerator);
	exif_set_slong (buf + 4, order, value.denominator);
}
