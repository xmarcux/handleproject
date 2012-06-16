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

#ifndef ACTIVITIESWINDOW_H
#define ACTIVITIESWINDOW_H

#include <gtkmm/window.h>
#include <gtkmm/uimanager.h>
#include <gtkmm/actiongroup.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/liststore.h>
#include <gtkmm/treeview.h>
#include <gtkmm/treemodelcolumn.h>
#include <gtkmm/label.h>
#include <gtkmm/box.h>
#include <glibmm/refptr.h>
#include <string>
#include "../project/project.h"
#include "projectwindow.h"

class ActivitiesWindow : public Gtk::Window
{
 public:
  /* This window shows all the activities
   * in a table where you are able to manage
   * the activities for a specific project.
   * Edit, delete and create new activities.
   */
  ActivitiesWindow(Project *proj, ProjectWindow *parent);

  /* Method is used when a new activity
   * is added or an activity has been 
   * edited and needs saving.
   * GUI is updated and project window
   * will get noticed that it needs to
   * update its GUI.
   */
  void add_edit_activity(Activity *activity);

 private:
  Project *project;
  ProjectWindow *parent;


  Glib::RefPtr<Gtk::UIManager> refUIManager;
  Glib::RefPtr<Gtk::ActionGroup> refActionGroup;
  Gtk::VBox *main_box;
  Gtk::ScrolledWindow scrollview;

  //Table for activities
  Glib::RefPtr<Gtk::ListStore> ref_tree_model;
  Gtk::TreeView *treeview;
  Gtk::TreeModelColumn<time_t> *col_id;
  Gtk::TreeModelColumn<std::string> *col_no;
  Gtk::TreeModelColumn<std::string> *col_name;
  Gtk::TreeModelColumn<std::string> *col_desc;
  Gtk::TreeModelColumn<std::string> *col_start_date;
  Gtk::TreeModelColumn<std::string> *col_end_date;
  Gtk::TreeModelColumn<bool> *col_finished;

  Gtk::Label *proj_no_label, *proj_name_label;

  // Creates the menu, use to initialze
  void create_menu();

  // Creates the main table where the activities are shown.
  void create_activities_table();

  // Signal handlers
  void on_action_file_new();
  void on_action_file_edit();
  void on_action_file_delete();
  void on_action_file_exit();
  void on_action_help_help();
  void on_action_help_about();
};

#endif
