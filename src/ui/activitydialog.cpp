/****************************************************************************
 *                                                                          *
 *    Handle Project, an application for managing projects and employees.   *
 *    Copyright (C) 2011, 2012  Marcus Pedersén marcux@handleproject.org    *
 *                                                                          *
 *    This program is free software: you can redistribute it and/or modify  *
 *    it under the terms of the GNU General Public License as published by  *
 *    the Free Software Foundation, either version 3 of the License, or     *
 *    (at your option) any later version.                                   *
 *                                                                          *
 *    This program is distributed in the hope that it will be useful,       *
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *    GNU General Public License for more details.                          *
 *                                                                          *
 *    You should have received a copy of the GNU General Public License     *
 *    along with this program.  If not, see <http://www.gnu.org/licenses/>. *
 *                                                                          *
 ****************************************************************************/

#include <glibmm/i18n.h>
#include "activitydialog.h"

ActivityDialog::ActivityDialog(ActivitiesWindow *parent, Activity *activity)
  : parent(parent), activity(activity)
{
  Gtk::Dialog(_("A test"), parent);
  set_icon_from_file("images/HaPr_high_80x100_ver2.gif");
  if(activity)
  {
    set_title(_("Edit activity"));
  }
  else
  {
    set_title(_("New activity"));
  }
}

ActivityDialog::~ActivityDialog()
{

}
