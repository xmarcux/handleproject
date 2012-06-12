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

#ifndef ACTIVITYDIALOG_H
#define ACTIVITYDIALOG_H

#include <gtkmm/dialog.h>
#include <gtkmm/window.h>
#include <gtkmm/entry.h>
#include <gtkmm/textview.h>
#include <gtkmm/checkbutton.h>
#include "../project/activity.h"
#include "activitieswindow.h"

class ActivityDialog : public Gtk::Dialog
{
 public:
  ActivityDialog(ActivitiesWindow *parent, Activity *activity = 0);
  virtual ~ActivityDialog();

 private:
  ActivitiesWindow *parent;
  Activity *activity;

  Gtk::Entry number_entry, name_entry, start_date_entry, end_date_entry;
  Gtk::TextView desc_area;
  Gtk::CheckButton check_button_finished;

  void on_click_start_calendar();
  void on_click_end_calendar();
  void show_calendar(bool start_cal=true);
};

#endif
