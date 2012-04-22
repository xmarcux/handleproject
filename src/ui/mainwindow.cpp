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
#include "about.h"
#include "neweditdialog.h"
#include "projectwindow.h"
#include "../files.h"
#include "../project/project.h"
#include "../project/activity.h"
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
  signal_hide().connect(sigc::mem_fun(*this, &MainWindow::on_action_file_exit));
  Gtk::VBox *const main_box = new Gtk::VBox(false, 0);
  add(*Gtk::manage(main_box));
  create_menu(main_box);
  std::list<Project> active_projects = get_projects_from_db();
  Glib::ustring str_no_proj, str_late_proj, str_history_proj;
  std::stringstream ss, ss2, ss3;
  no_active = active_projects.size();
  ss << no_active;
  ss >> str_no_proj;
  std::list<Project> hist_projects = get_projects_from_db(HISTORY_PROJECT);
  no_history = hist_projects.size();
  ss3 << no_history;
  ss3 >> str_history_proj;
  no_late = 0;
  for(std::list<Project>::iterator it = active_projects.begin(); it != active_projects.end(); it++)
  {
    if(it->is_late())
      no_late++;
  }
  ss2 << no_late;
  ss2 >> str_late_proj;
  
  treeview = new Gtk::TreeView();
  Gtk::manage(treeview);
  scrollview.add(*treeview);
  scrollview.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
  treeviewhist = new Gtk::TreeView();
  Gtk::manage(treeviewhist);
  Gtk::ScrolledWindow *scrollhistory = new Gtk::ScrolledWindow();
  Gtk::manage(scrollhistory);
  scrollhistory->add(*treeviewhist);
  scrollhistory->set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
  tabview = new Gtk::Notebook();
  Gtk::manage(tabview);
  tabview->append_page(scrollview, _("_Active projects"), true);
  tabview->append_page(*scrollhistory, _("P_roject history"), true);
  main_box->pack_start(*tabview);

  //Table for active projects.
  Gtk::TreeModel::ColumnRecord *col_record = new Gtk::TreeModel::ColumnRecord();
  col_id = new Gtk::TreeModelColumn<time_t>();
  col_no = new Gtk::TreeModelColumn<std::string>();
  col_name = new Gtk::TreeModelColumn<std::string>();
  col_desc = new Gtk::TreeModelColumn<std::string>();
  col_leader_name = new Gtk::TreeModelColumn<std::string>();
  col_leader_surname = new Gtk::TreeModelColumn<std::string>();
  col_start_date = new Gtk::TreeModelColumn<std::string>();
  col_end_date = new Gtk::TreeModelColumn<std::string>();

  col_record->add(*col_id);
  col_record->add(*col_no);
  col_record->add(*col_name);
  col_record->add(*col_desc);
  col_record->add(*col_leader_name);
  col_record->add(*col_leader_surname);
  col_record->add(*col_start_date);
  col_record->add(*col_end_date);

  ref_tree_model = Gtk::ListStore::create(*col_record);
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

  //Table for history.
  Gtk::TreeModel::ColumnRecord *col_record_hist = new Gtk::TreeModel::ColumnRecord();
  col_id_hist = new Gtk::TreeModelColumn<time_t>();
  col_no_hist = new Gtk::TreeModelColumn<std::string>();
  col_desc_hist = new Gtk::TreeModelColumn<std::string>();
  col_name_hist = new Gtk::TreeModelColumn<std::string>();
  col_leader_name_hist = new Gtk::TreeModelColumn<std::string>();
  col_leader_surname_hist = new Gtk::TreeModelColumn<std::string>();
  col_start_date_hist = new Gtk::TreeModelColumn<std::string>();
  col_end_date_hist = new Gtk::TreeModelColumn<std::string>();

  col_record_hist->add(*col_id_hist);
  col_record_hist->add(*col_no_hist);
  col_record_hist->add(*col_name_hist);
  col_record_hist->add(*col_desc_hist);
  col_record_hist->add(*col_leader_name_hist);
  col_record_hist->add(*col_leader_surname_hist);
  col_record_hist->add(*col_start_date_hist);
  col_record_hist->add(*col_end_date_hist);

  ref_tree_model_hist = Gtk::ListStore::create(*col_record_hist);
  treeviewhist->set_model(ref_tree_model_hist);

  Gtk::TreeModel::Row row_hist;
  for(std::list<Project>::iterator it = hist_projects.begin(); it != hist_projects.end(); it++)
  {
    row_hist = *(ref_tree_model_hist->append());
    row_hist[*col_id_hist] = it->get_id();
    row_hist[*col_no_hist] = it->get_project_no();
    row_hist[*col_name_hist] = it->get_project_name();
    row_hist[*col_desc_hist] = it->get_description();
    row_hist[*col_leader_name_hist] = it->get_project_leader_name();
    row_hist[*col_leader_surname_hist] = it->get_project_leader_surname();
    row_hist[*col_start_date_hist] = it->get_start_date_str_eu();
    row_hist[*col_end_date_hist] = it->get_end_date_str_eu();
    j++;
  }

  treeviewhist->append_column(_("Number"), *col_no_hist);
  treeviewhist->append_column(_("Name"), *col_name_hist);
  treeviewhist->append_column(_("Description"), *col_desc_hist);
  treeviewhist->append_column(_("Leader name"), *col_leader_name_hist);
  treeviewhist->append_column(_("Leader surmane"), *col_leader_surname_hist);
  treeviewhist->append_column(_("Start date"), *col_start_date_hist);
  treeviewhist->append_column(_("End date"), *col_end_date_hist);
  treeviewhist->set_headers_clickable(true);
  treeviewhist->set_grid_lines(Gtk::TREE_VIEW_GRID_LINES_BOTH);

  for(int i=0; i < 7; i++)
  {
    Gtk::TreeView::Column *pColumn_hist = treeviewhist->get_column(i);
    pColumn_hist->set_resizable(true);
    pColumn_hist->set_sort_column(i+1);
  }

  Gtk::HBox *const status_box = new Gtk::HBox(false, 0);
  Gtk::manage(status_box);
  active_label = new Gtk::Label(_("Number of active projects: ") +  str_no_proj);
  late_label = new Gtk::Label(_("Number of late projects: ") + str_late_proj);
  history_label = new Gtk::Label(_("Number of projects in history: ") + str_history_proj);
  Gtk::manage(active_label);
  Gtk::manage(late_label);
  Gtk::manage(history_label);
  
  status_box->pack_start(*active_label);
  status_box->pack_start(*late_label);
  status_box->pack_start(*history_label);

  main_box->pack_start(*status_box, Gtk::PACK_SHRINK);
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
  refActionGroup->add(Gtk::Action::create("FileDelete", Gtk::Stock::DELETE, _("_Delete project")),
		      sigc::mem_fun(*this, &MainWindow::on_action_file_delete));
  refActionGroup->add(Gtk::Action::create("FileExport", Gtk::Stock::GO_FORWARD, _("_Export project...")),
		      sigc::mem_fun(*this, &MainWindow::on_action_file_export));
  refActionGroup->add(Gtk::Action::create("FileImport", Gtk::Stock::GO_BACK, _("_Import project...")),
		      sigc::mem_fun(*this, &MainWindow::on_action_file_import));
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
    "      <menuitem action='FileDelete'/>"
    "      <separator/>"
    "      <menuitem action='FileExport'/>"
    "      <menuitem action='FileImport'/>"
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
    "    <toolitem action='FileDelete'/>"
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

void MainWindow::add_new_project(Project p)
{
  Gtk::TreeModel::Row row;
  row = *(ref_tree_model->append());
  row[*col_id] = p.get_id();
  row[*col_no] = p.get_project_no();
  row[*col_name] = p.get_project_name();
  row[*col_desc] = p.get_description();
  row[*col_leader_name] = p.get_project_leader_name();
  row[*col_leader_surname] = p.get_project_leader_surname();
  row[*col_start_date] = p.get_start_date_str_eu();
  row[*col_end_date] = p.get_end_date_str_eu();

  no_active++;
  std::string str_active;
  std::stringstream ss;
  ss << no_active;
  ss >> str_active;
  if(!ss.fail())
    active_label->set_text(_("Number of active projects: ") + str_active);

  if(p.is_late())
  {
    no_late++;
    std::string str_late;
    std::stringstream ss2;
    ss2 << no_late;
    ss2 >> str_late;
    if(!ss2.fail())
      late_label->set_text(_("Number of late projects: ") + str_late);
  }
}

void MainWindow::on_action_file_open()
{

}

void MainWindow::on_action_file_delete()
{
  Glib::RefPtr<Gtk::TreeSelection> ref_tree_selection;
  Gtk::TreeModel::iterator iter;
  if(tabview->get_current_page() == 0)
  {
    ref_tree_selection = treeview->get_selection();
    iter = ref_tree_selection->get_selected();
  }
  else
  {
    ref_tree_selection = treeviewhist->get_selection();
    iter = ref_tree_selection->get_selected();
  }
  if(iter)
  {
    Gtk::TreeModel::Row row = *iter;
    Glib::ustring msg;
    if(tabview->get_current_page() == 0)
    {
      msg =  row.get_value(*col_no);
      msg += "\n" + row.get_value(*col_name);
      msg += "\n" + row.get_value(*col_desc);
    }
    else
    {
      msg =  row.get_value(*col_no_hist);
      msg += "\n" + row.get_value(*col_name_hist);
      msg += "\n" + row.get_value(*col_desc_hist);
    }
    Gtk::MessageDialog delete_dialog(*this, "", false, Gtk::MESSAGE_WARNING, Gtk::BUTTONS_YES_NO, true);
    delete_dialog.set_message(_("Do you want to delete project?"));
    delete_dialog.set_secondary_text(msg);
    int response = delete_dialog.run();
    if(response == Gtk::RESPONSE_YES)
    {
      delete_dialog.hide();
      time_t proj_no;
      std::stringstream ss;
      if(tabview->get_current_page() == 0)
	ss << row.get_value(*col_id);
      else
	ss << row.get_value(*col_id_hist);
      ss >> proj_no;
      if(!ss.fail())
      {
	bool del_ok = true;
	Project p("", "", "");
	if(tabview->get_current_page() == 0)
	  p = get_project_from_db(proj_no);
	else
	  p = get_project_from_db(proj_no, HISTORY_PROJECT);
	std::list<Activity> act_list = p.get_activities();
	for(std::list<Activity>::iterator it=act_list.begin(); it!=act_list.end(); it++)
	{
	  int act_del;
	  if(tabview->get_current_page() == 0)
	    act_del = delete_activity_from_db(&(*it), proj_no);
	  else
	    act_del = delete_activity_from_db(&(*it), proj_no, HISTORY_PROJECT);
	  if(act_del <= 0)
	  {
	    std::stringstream ss, ss2;
	    ss << p.get_id();
	    ss2 << it->get_id();
	    del_ok = false;
	    new_error("Error: Can not delete activity with id: " + ss2.str() +
		      " in project with id: " + ss.str(), 
		      "mainwindow.cpp", "void MainWindow::on_action_file_delete()");
	  }
	}
        if(del_ok)
	{
	  int proj_del;
	  if(tabview->get_current_page() == 0)
	    proj_del = delete_object_from_db(&p);
	  else
	    proj_del = delete_object_from_db(&p, HISTORY_PROJECT);
	  if(proj_del <= 0)
	  {
	    std::stringstream ss;
	    ss << p.get_id();
	    new_error("Error: Can not delete project with id: " + ss.str(), 
		      "mainwindow.cpp", "void MainWindow::on_action_file_delete()");
	    Gtk::MessageDialog error_dialog(*this, "", false, Gtk::MESSAGE_ERROR, Gtk::BUTTONS_OK, true);
	    error_dialog.set_message(_("Error: Can not delete project:"));
	    error_dialog.set_secondary_text(msg);
	    error_dialog.run();
	  }
	  else
	  {
	    if(tabview->get_current_page() == 0)
	    {
	      ref_tree_model->erase(iter);
	      no_active--;
	      if(p.is_late())
		no_late--;
	      std::string no_act_str, no_late_str;
	      std::stringstream s_act, s_late;
	      s_act << no_active;
	      s_act >> no_act_str;
	      s_late << no_late;
	      s_late >> no_late_str;
	      active_label->set_text(_("Number of active projects: ") + no_act_str);
	      late_label->set_text(_("Number of late projects: ") + no_late_str);
	    }
	    else
	    {
	      ref_tree_model_hist->erase(iter);
	      no_history--;
	      std::string no_hist_str;
	      std::stringstream s_hist;
	      s_hist << no_history;
	      s_hist >> no_hist_str;
	      history_label->set_text(_("Number of projects in history: ") + no_hist_str);
     	    }
	    Gtk::MessageDialog confirm_dialog(*this, "", false, Gtk::MESSAGE_INFO, Gtk::BUTTONS_OK, true);
	    confirm_dialog.set_message(_("Project deleted: "));
	    confirm_dialog.set_secondary_text(msg);
	    confirm_dialog.run();
	  }
	}
	else
	{
	  Gtk::MessageDialog error_dialog(*this, "", false, Gtk::MESSAGE_ERROR, Gtk::BUTTONS_OK, true);
	  error_dialog.set_message(_("Error: Can not delete project:"));
	  error_dialog.set_secondary_text(msg);
	  error_dialog.run();
	}
      }
      else
      {
	Gtk::MessageDialog error_dialog(*this, "", false, Gtk::MESSAGE_ERROR, Gtk::BUTTONS_OK, true);
	error_dialog.set_message(_("Error: Can not delete project:"));
	error_dialog.set_secondary_text(msg);
	error_dialog.run();
	new_error("Error: Can not delete project with id: " + row.get_value(*col_id),
		  "mainwindow.cpp", "void MainWindow::on_action_file_delete()");
      }
    }
  }
}

void MainWindow::on_action_file_exit()
{
  Gtk::Main::quit();
}

void MainWindow::on_action_file_new()
{
  NewEditDialog d(this);
}

void MainWindow::on_action_file_export()
{
  Glib::RefPtr<Gtk::TreeSelection> ref_tree_selection;
  Gtk::TreeModel::iterator iter;
  if(tabview->get_current_page() == 0)
  {
    ref_tree_selection = treeview->get_selection();
    iter = ref_tree_selection->get_selected();
  }
  else
  {
    ref_tree_selection = treeviewhist->get_selection();
    iter = ref_tree_selection->get_selected();
  }
  if(iter)
  {
    Gtk::TreeModel::Row row = *iter;
    time_t proj_id;
    Project export_p("", "", "");
    std::stringstream s_proj_id;
    if(tabview->get_current_page() == 0)
    {
      proj_id = row.get_value(*col_id);
      export_p = get_project_from_db(proj_id);
    }
    else
    {
      proj_id = row.get_value(*col_id_hist);
      export_p = get_project_from_db(proj_id, HISTORY_PROJECT);
    }
    s_proj_id << proj_id;

    Gtk::FileChooserDialog export_dialog(*this, _("Export project"), Gtk::FILE_CHOOSER_ACTION_SAVE);
    export_dialog.add_button(Gtk::Stock::CANCEL, 1);
    export_dialog.add_button(Gtk::Stock::SAVE, 2);
    bool cont = true;
    while(cont)
    {
      int response = export_dialog.run();
      if(response == 2)
      {
	Glib::ustring file_name = export_dialog.get_filename();
	if(file_name.size() == 0)
	{
	  Gtk::MessageDialog no_file_dialog(*this, "", false, Gtk::MESSAGE_WARNING, Gtk::BUTTONS_OK, true);
	  no_file_dialog.set_message(_("Please specify a name for the export"));
	  no_file_dialog.run();
	}
	else
	{
	  file_name += "_" + s_proj_id.str() + ".tar";
	  if(export_project_from_db(export_p, file_name) == 1)
	  {
	    file_name = _("Project exported to file: \n") + file_name + ".gz";
	    file_name = _("Project number: ") + export_p.get_project_no() + "\n" +
	      _("Project name: ") + export_p.get_project_name() + "\n" +
	      _("Project description: ") + export_p.get_description() + "\n\n" + 
	      file_name;
	    Gtk::MessageDialog response_dialog(*this, "", false, Gtk::MESSAGE_INFO, Gtk::BUTTONS_OK, true);
	    response_dialog.set_message(_("Project exported:"));
	    response_dialog.set_secondary_text(file_name);
	    response_dialog.run();
	    cont = false;
	  }
	  else
	  {
	    Gtk::MessageDialog err_exp_dialog(*this, "", false, Gtk::MESSAGE_ERROR, Gtk::BUTTONS_OK, true);
	    err_exp_dialog.set_message("Error!");
	    err_exp_dialog.set_secondary_text("Can not export project!");
	  }
	}
      }
      else
	cont = false;
    }
  }
}

void MainWindow::on_action_file_import()
{

}

void MainWindow::on_action_help_help()
{

}

void MainWindow::on_action_help_about()
{
  About a;
  a.run();
}

MainWindow::~MainWindow()
{

}
