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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "../project/project.h"
#include <gtkmm.h>

/* The main window for Handle Project.
 * This window shows a list with all
 * projects in the database, and an 
 * open project button.
 */
class MainWindow : public Gtk::Window
{
 public:
  MainWindow();
  virtual ~MainWindow();

  void add_new_project(Project p);

 protected:
  Glib::RefPtr<Gtk::UIManager> refUIManager;
  Glib::RefPtr<Gtk::ActionGroup> refActionGroup;
  Gtk::ScrolledWindow scrollview;

  //Table for active projects
  Gtk::TreeView *treeview;
  Glib::RefPtr<Gtk::ListStore> ref_tree_model;
  Gtk::TreeModelColumn<time_t> *col_id;
  Gtk::TreeModelColumn<std::string> *col_no;
  Gtk::TreeModelColumn<std::string> *col_name;
  Gtk::TreeModelColumn<std::string> *col_desc;
  Gtk::TreeModelColumn<std::string> *col_leader_name;
  Gtk::TreeModelColumn<std::string> *col_leader_surname;
  Gtk::TreeModelColumn<std::string> *col_start_date;
  Gtk::TreeModelColumn<std::string> *col_end_date;

  //Table for project history
  Gtk::TreeView *treeviewhist;
  Glib::RefPtr<Gtk::ListStore> ref_tree_model_hist;
  Gtk::TreeModelColumn<time_t> *col_id_hist;
  Gtk::TreeModelColumn<std::string> *col_no_hist;
  Gtk::TreeModelColumn<std::string> *col_name_hist;
  Gtk::TreeModelColumn<std::string> *col_desc_hist;
  Gtk::TreeModelColumn<std::string> *col_leader_name_hist;
  Gtk::TreeModelColumn<std::string> *col_leader_surname_hist;
  Gtk::TreeModelColumn<std::string> *col_start_date_hist;
  Gtk::TreeModelColumn<std::string> *col_end_date_hist;

  Gtk::Notebook *tabview;

  Gtk::Label *active_label, *late_label, *history_label;
  int no_active, no_late, no_history;

  // Creates the menu, use to initialize.
  void create_menu(Gtk::VBox *vbox);

  //Signal handlers:
  void on_action_file_open();
  void on_action_file_delete();
  void on_action_file_exit();
  void on_action_file_new();
  void on_action_file_export();
  void on_action_file_import();
  void on_action_help_help();
  void on_action_help_about();
};
#endif
