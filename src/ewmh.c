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
  XChangeProperty (dpy, net_swc, _net_wm_name, xa_utf8_string,
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

void
ewmh_set_number_of_desktops (void)
{
  unsigned long data[1];

  data[0] = list_size (&rp_groups);
  XChangeProperty (dpy, DefaultRootWindow (dpy),
                   XInternAtom (dpy, "_NET_NUMBER_OF_DESKTOPS", False),
                   XA_CARDINAL, 32, PropModeReplace,
                   (unsigned char *) data, 1);
}

void
ewmh_set_current_desktop (int group)
{
  unsigned long data[1];

  data[0] = group;
  XChangeProperty (dpy, DefaultRootWindow (dpy),
                   XInternAtom (dpy, "_NET_CURRENT_DESKTOP", False),
                   XA_CARDINAL, 32, PropModeReplace,
                   (unsigned char *) data, 1);
}

void
ewmh_set_client_list ()
{
  rp_window_elem *we;
  int count, i, j;
  Window *windows, *stacked_windows;

  count = list_size (&rp_current_group->mapped_windows);
  windows = xmalloc (sizeof (Window) * count);
  stacked_windows = xmalloc (sizeof (Window) * count);
  i = 0;

  list_for_each_entry (we, &rp_current_group->mapped_windows, node)
    windows[i++] = we->win->w;
  for (i = 0, j = count-1; j >= 0; j--, i++)
    stacked_windows[j] = windows[i];

  XChangeProperty (dpy, DefaultRootWindow (dpy),
                   XInternAtom (dpy, "_NET_CLIENT_LIST", False),
                   XA_WINDOW, 32, PropModeReplace,
                   (unsigned char *) windows, count);
  XChangeProperty (dpy, DefaultRootWindow (dpy),
                   XInternAtom (dpy, "_NET_CLIENT_LIST_STACKING", False),
                   XA_WINDOW, 32, PropModeReplace,
                   (unsigned char *) stacked_windows, count);
  free (windows);
  free (stacked_windows);
}

void
ewmh_set_wm_desktop (rp_window *window)
{
  unsigned long data[1];

  data[0] = rp_current_group->number;
  XChangeProperty (dpy, window->w,
                   XInternAtom (dpy, "_NET_WM_DESKTOP", False),
                   XA_CARDINAL, 32, PropModeReplace,
                   (unsigned char *) data, 1);

}
