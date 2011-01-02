/* Copyright (C) 2010  Lincoln de Sousa <lincoln@comum.org>
 *
 * This file is part of ratpoison.
 *
 * ratpoison is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * ratpoison is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 59 Temple Place, Suite 330,
 * Boston, MA 02111-1307 USA
 */

#include <X11/Xlib.h>
#include "ratpoison.h"

void
init_ewmh (void)
{
  Window net_swc, root;
  unsigned long data[1];

  root = DefaultRootWindow (dpy);

  /* Here we create a very simple window, it should not have any better
   * setup since it'll never be shown. */
  net_swc = XCreateSimpleWindow (dpy, root, 0, 0, 1, 1, 0, 0, 0);

  /* Now it's time to setup EWMH properties _NET_WM_NAME and
   * _NET_SUPPORTING_WM_CHECK (both in offscreen window and in root)  */
  XChangeProperty (dpy, net_swc, _net_wm_name, utf8_string,
                   8, PropModeReplace, (unsigned char *) "Ratpoison", 9);

  data[0] = net_swc;
  XChangeProperty (dpy, net_swc, _net_supporting_wm_check,
                   XA_WINDOW, 32, PropModeReplace,
                   (unsigned char *) data, 1);

  XChangeProperty (dpy, root,
                   XInternAtom (dpy, "_NET_SUPPORTING_WM_CHECK", False),
                   XA_WINDOW, 32, PropModeReplace,
                   (unsigned char *) data, 1);
}
