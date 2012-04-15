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

#ifndef NEWEDITDIALOG_H
#define NEWEDITDIALOG_H

#include <gtkmm/dialog.h>
#include <gtkmm/window.h>
#include <gtkmm/entry.h>
#include <gtkmm/textview.h>
#include "../project/project.h"
#include "mainwindow.h"

class NewEditDialog : public Gtk::Dialog
{
 public:
  /* If no project is given as attribute
   * a window for creating a new project
   * is displayed.
   * If project is given the edit 
   * window will show up.
   */
  NewEditDialog(MainWindow *parent, Project *proj = 0);
  virtual ~NewEditDialog();

 private:
  void show_calendar(bool start_date_cal = true);
  void on_click_start_calendar();
  void on_click_end_calendar();
  Gtk::Entry number_entry, name_entry, leader_name_entry, leader_surname_entry, 
    leader_initials_entry, start_date_entry, end_date_entry,
    hour_per_day_entry, days_per_week_entry;
  Gtk::TextView desc_view;
  MainWindow *parent_window;
};

#endif
