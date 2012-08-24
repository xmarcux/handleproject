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

#ifndef PROJECTWINDOW_H
#define PROJECTWINDOW_H

#include "../project/project.h"
#include "mainwindow.h"
#include <gtkmm/window.h>
#include <gtkmm/actiongroup.h>
#include <gtkmm/uimanager.h>
#include <gtkmm/box.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/liststore.h>
#include <gtkmm/treeview.h>
#include <gtkmm/treemodelcolumn.h>
#include <glibmm/refptr.h>
#include <gtkmm/cellrenderer.h>
#include <gtkmm/treemodel.h>
#include <gtkmm/label.h>
#include <map>
#include <vector>

/* This class is the window that
 * shows one specific project.
 * Window will show all activities,
 * information on project and
 * ways to be able to change project.
 */
class ProjectWindow : public Gtk::Window
{
 public:
  /* Constructor that takes the
   * project id as an argument.
   * Project is loded from file.
   */
  ProjectWindow(time_t project_id, MainWindow *mainwindow);

  /* Updates the GUI if properites
   * for project has been changed.
   */
  void update_view();

  /* Updates the GUI if properties
   * for activities has been changed.
   */
  void update_activity_view();

  virtual ~ProjectWindow();

 private:
  Project project;
  MainWindow *mainwindow;
  Glib::RefPtr<Gtk::ActionGroup> refActionGroup;
  Glib::RefPtr<Gtk::UIManager> refUIManager;
  Gtk::VBox *const main_box;
  Gtk::ScrolledWindow scrollview;
  Glib::RefPtr<Gtk::ListStore> ref_tree_model;
  Gtk::TreeView *treeview;
  Gtk::TreeModelColumn<time_t> *col_id;
  Gtk::TreeModelColumn<std::string> *col_name;
  Gtk::HBox table_box, main_table_box, status_box;
  Gtk::VBox activity_box;
  Gtk::Label *act_label, *no_act_label, *on_time_label, *late_label, *finished_label;
  std::vector<Gtk::TreeView* > month_tables;
  std::vector<Gtk::VBox* > table_boxes;

  /* Updates values for the statusbar */
  void update_status_bar();

  /* Private method that
   * creates the menu.
   */
  void create_menu();

  /* Creates the layout
   * and view for the window
   */
  void create_view();

  /* Creates the table for a month.
   * starting_day is the day in the 
   * month where table should start.
   * month is the current month 1-12.
   * year is the current year with 4 digets i.e 2012
   * Returns a pointer to a treview
   * containing table.
   */
  Gtk::TreeView * create_month_view(int starting_day, int month, int year);

  /* Creates the information
   * bar at the bottom of the 
   * window
   */
  void create_status_bar();

  /* Callback method for
   * menues.
   */
  void on_action_file_exit();
  void on_action_help_about();
  void on_action_project_properties();
  void on_action_project_activities();
};

#endif
