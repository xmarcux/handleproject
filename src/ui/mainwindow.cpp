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

#include "mainwindow.h"
#include "../files.h"
#include "../project/project.h"
#include <list>
#include <sstream>
#include <glibmm/i18n.h>

MainWindow::MainWindow()
{
  set_title("Handle Project");
  set_icon_from_file("images/HaPr_high_80x100_ver2.gif");
  set_size_request(200, 200);
  set_default_size(500, 300);
  set_position(Gtk::WIN_POS_CENTER);
  Gtk::VBox *const main_box = new Gtk::VBox(false, 0);
  add(*Gtk::manage(main_box));
  create_menu(main_box);
  std::list<Project> active_projects = get_projects_from_db();
  Glib::ustring str_no_proj, str_late_proj;
  std::stringstream ss, ss2;
  ss << active_projects.size();
  ss >> str_no_proj;
  int no_late = 0;
  for(std::list<Project>::iterator it = active_projects.begin(); it != active_projects.end(); it++)
  {
    if(it->is_late())
      no_late++;
  }
  ss2 << no_late;
  ss2 >> str_late_proj;
  
  Gtk::TreeView *treeview = new Gtk::TreeView();
  Gtk::manage(treeview);
  scrollview.add(*treeview);
  scrollview.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
  main_box->pack_start(scrollview);

  Gtk::TreeModel::ColumnRecord *col_record = new Gtk::TreeModel::ColumnRecord();
  Gtk::TreeModelColumn<time_t> *col_id = new Gtk::TreeModelColumn<time_t>();
  Gtk::TreeModelColumn<std::string> *col_no = new Gtk::TreeModelColumn<std::string>();
  Gtk::TreeModelColumn<std::string> *col_name = new Gtk::TreeModelColumn<std::string>();
  Gtk::TreeModelColumn<std::string> *col_desc = new Gtk::TreeModelColumn<std::string>();
  Gtk::TreeModelColumn<std::string> *col_leader_name = new Gtk::TreeModelColumn<std::string>();
  Gtk::TreeModelColumn<std::string> *col_leader_surname = new Gtk::TreeModelColumn<std::string>();
  Gtk::TreeModelColumn<std::string> *col_start_date = new Gtk::TreeModelColumn<std::string>();
  Gtk::TreeModelColumn<std::string> *col_end_date = new Gtk::TreeModelColumn<std::string>();

  col_record->add(*col_id);
  col_record->add(*col_no);
  col_record->add(*col_name);
  col_record->add(*col_desc);
  col_record->add(*col_leader_name);
  col_record->add(*col_leader_surname);
  col_record->add(*col_start_date);
  col_record->add(*col_end_date);

  Glib::RefPtr<Gtk::ListStore> ref_tree_model = Gtk::ListStore::create(*col_record);
  treeview->set_model(ref_tree_model);

  int j = 0;
  Gtk::TreeModel::Row row;
  for(std::list<Project>::iterator it = active_projects.begin(); it != active_projects.end(); it++)
  {
    row = *(ref_tree_model->append());
    row[*col_id] = it->get_id();
    row[*col_no] = it->get_project_no();
    row[*col_name] = it->get_project_name();
    row[*col_desc] = it->get_description();
    row[*col_leader_name] = it->get_project_leader_name();
    row[*col_leader_surname] = it->get_project_leader_surname();
    row[*col_start_date] = it->get_start_date_str_eu();
    row[*col_end_date] = it->get_end_date_str_eu();
    j++;
  }

  treeview->append_column(_("Number"), *col_no);
  treeview->append_column(_("Name"), *col_name);
  treeview->append_column(_("Description"), *col_desc);
  treeview->append_column(_("Leader name"), *col_leader_name);
  treeview->append_column(_("Leader surmane"), *col_leader_surname);
  treeview->append_column(_("Start date"), *col_start_date);
  treeview->append_column(_("End date"), *col_end_date);
  treeview->set_headers_clickable(true);
  treeview->set_grid_lines(Gtk::TREE_VIEW_GRID_LINES_BOTH);

  for(int i=0; i < 7; i++)
  {
    Gtk::TreeView::Column *pColumn = treeview->get_column(i);
    pColumn->set_resizable(true);
    pColumn->set_sort_column(i+1);
  }

  Gtk::Statusbar *statusbar = new Gtk::Statusbar();
  Gtk::manage(statusbar);
  statusbar->push(_("Number of active projects: ") +  str_no_proj + "               " +
		  _("Number of late projects: ") + str_late_proj);//Number of late projects: 
  main_box->pack_start(*statusbar, Gtk::PACK_SHRINK);
  show_all_children();
}

void MainWindow::create_menu(Gtk::VBox *vbox)
{
  // Create actions for menu and toolbar.
  refActionGroup = Gtk::ActionGroup::create();
  
  // File menu
  refActionGroup->add(Gtk::Action::create("MenuFile", _("_File")));

  // File submenu
  refActionGroup->add(Gtk::Action::create("FileNew", Gtk::Stock::NEW, _("_New project...")),
		      sigc::mem_fun(*this, &MainWindow::on_action_file_new));
  refActionGroup->add(Gtk::Action::create("FileOpen", Gtk::Stock::OPEN, _("_Open project")),
		      sigc::mem_fun(*this, &MainWindow::on_action_file_open));
  refActionGroup->add(Gtk::Action::create("FileExit", Gtk::Stock::QUIT, _("_Quit")),
		      sigc::mem_fun(*this, &MainWindow::on_action_file_exit));

  // Help menu
  refActionGroup->add(Gtk::Action::create("MenuHelp", _("_Help")));

  // Help submenu
  refActionGroup->add(Gtk::Action::create("HelpHelp", Gtk::Stock::HELP),
		      sigc::mem_fun(*this, &MainWindow::on_action_help_help));
  refActionGroup->add(Gtk::Action::create("HelpAbout", Gtk::Stock::ABOUT, _("_About Handle Project")),
		      sigc::mem_fun(*this, &MainWindow::on_action_help_about));

  refUIManager = Gtk::UIManager::create();
  refUIManager->insert_action_group(refActionGroup);

  add_accel_group(refUIManager->get_accel_group());

  Glib::ustring ui_info =
    "<ui>"
    "  <menubar name='MenuBar'>"
    "    <menu action='MenuFile'>"
    "      <menuitem action='FileNew'/>"
    "      <menuitem action='FileOpen'/>"
    "      <separator/>"
    "      <menuitem action='FileExit'/>"
    "    </menu>"
    "    <menu action='MenuHelp'>"
    "      <menuitem action='HelpHelp'/>"
    "      <menuitem action='HelpAbout'/>"
    "    </menu>"
    "  </menubar>"
    "  <toolbar name='ToolBar'>"
    "    <toolitem action='FileNew'/>"
    "    <toolitem action='FileOpen'/>"
    "  </toolbar>"
    "</ui>";

  try
  {
    refUIManager->add_ui_from_string(ui_info);
  }
  catch(const Glib::Error& err)
  {
    new_error("Can not create menu and toolbar."+ err.what(), "mainwindow.cpp", 
	      "MainWindow::create_menu()");
  }
  
  Gtk::Widget* pMenubar = refUIManager->get_widget("/MenuBar");
  if(pMenubar)
    vbox->pack_start(*pMenubar, Gtk::PACK_SHRINK);
  Gtk::Widget* pToolbar = refUIManager->get_widget("/ToolBar");
  if(pToolbar)
    vbox->pack_start(*pToolbar, Gtk::PACK_SHRINK);
}

void MainWindow::on_action_file_open()
{

}

void MainWindow::on_action_file_exit()
{
  hide();
}

void MainWindow::on_action_file_new()
{

}

void MainWindow::on_action_help_help()
{

}

void MainWindow::on_action_help_about()
{

}

MainWindow::~MainWindow()
{
}
