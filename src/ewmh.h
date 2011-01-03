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

#ifndef EWMH_H
#define EWMH_H

void init_ewmh (void);
void ewmh_set_number_of_desktops (void);
void ewmh_set_current_desktop (int group);
void ewmh_set_client_list (void);
void ewmh_set_wm_desktop (rp_window *window);

#endif
