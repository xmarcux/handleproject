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

#include "activitieswindow.h"
#include "../files.h"
#include "about.h"
#include "../project/activity.h"
#include "activitydialog.h"
#include <list>
#include <glibmm/i18n.h>

ActivitiesWindow::ActivitiesWindow(Project *proj, ProjectWindow *parent)
  : project(proj), parent(parent), main_box(new Gtk::VBox(false, 0))
{
  set_title(_("Edit activities"));
  set_icon_from_file("images/HaPr_high_80x100_ver2.gif");
  add(*Gtk::manage(main_box));
  set_size_request(200, 200);
  set_default_size(500, 300);
  set_position(Gtk::WIN_POS_CENTER);
  create_menu();
  create_activities_table();

  proj_no_label = new Gtk::Label(_("Project number: ") + project->get_project_no());
  proj_name_label = new Gtk::Label(_("Project name: ") + project->get_project_name());
  proj_no_label->set_alignment(Gtk::ALIGN_CENTER, Gtk::ALIGN_CENTER);
  proj_name_label->set_alignment(Gtk::ALIGN_CENTER, Gtk::ALIGN_CENTER);
  Gtk::manage(proj_no_label);
  Gtk::manage(proj_name_label);
  Gtk::HBox *infobar = new Gtk::HBox(false, 0);
  Gtk::manage(infobar);
  infobar->pack_start(*proj_name_label);
  infobar->pack_start(*proj_no_label);
  main_box->pack_start(*infobar, Gtk::PACK_SHRINK);
}

void ActivitiesWindow::create_menu()
{
  refActionGroup = Gtk::ActionGroup::create();
  
  //File menu
  refActionGroup->add(Gtk::Action::create("MenuFile", _("_File")));

  //File submenu
  refActionGroup->add(Gtk::Action::create("FileNew", Gtk::Stock::NEW, _("_New activity")),
		      sigc::mem_fun(*this, &ActivitiesWindow::on_action_file_new));
  refActionGroup->add(Gtk::Action::create("FileEdit", Gtk::Stock::EDIT, _("Edit activity")),
		      sigc::mem_fun(*this, &ActivitiesWindow::on_action_file_edit));
  refActionGroup->add(Gtk::Action::create("FileDelete", Gtk::Stock::DELETE, _("Delete activity")),
		      sigc::mem_fun(*this, &ActivitiesWindow::on_action_file_delete));
  refActionGroup->add(Gtk::Action::create("FileExit", Gtk::Stock::QUIT, _("_Quit")),
		      sigc::mem_fun(*this, &ActivitiesWindow::on_action_file_exit));

  //Help menu
  refActionGroup->add(Gtk::Action::create("MenuHelp", _("_Help")));
  
  //Help submenu
  refActionGroup->add(Gtk::Action::create("HelpHelp", Gtk::Stock::HELP, _("_Help")),
		      sigc::mem_fun(*this, &ActivitiesWindow::on_action_help_help));
  refActionGroup->add(Gtk::Action::create("HelpAbout", Gtk::Stock::ABOUT, _("_About Handle Project")),
		      sigc::mem_fun(*this, &ActivitiesWindow::on_action_help_about));

  refUIManager = Gtk::UIManager::create();
  refUIManager->insert_action_group(refActionGroup);

  add_accel_group(refUIManager->get_accel_group());

  Glib::ustring ui_info =
    "<ui>"
    "  <menubar name='MenuBar'>"
    "    <menu action='MenuFile'>"
    "      <menuitem action='FileNew'/>"
    "      <menuitem action='FileEdit'/>"
    "      <menuitem action='FileDelete'/>"
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
    "    <toolitem action='FileEdit'/>"
    "    <toolitem action='FileDelete'/>"
    "  </toolbar>"
    "</ui>";

  try
  {
    refUIManager->add_ui_from_string(ui_info);
  }
  catch(const Glib::Error& err)
  {
    new_error("Can not create menu and toolbar." + err.what(), "activitieswindow.cpp",
	      "ActivitiesWindow::create_menu()");
  }

  Gtk::Widget* pMenubar = refUIManager->get_widget("/MenuBar");
  if(pMenubar)
    main_box->pack_start(*pMenubar, Gtk::PACK_SHRINK);
  Gtk::Widget* pToolbar = refUIManager->get_widget("/ToolBar");
  if(pToolbar)
    main_box->pack_start(*pToolbar, Gtk::PACK_SHRINK);
}

void ActivitiesWindow::create_activities_table()
{
  treeview = new Gtk::TreeView();
  Gtk::manage(treeview);
  scrollview.add(*treeview);
  scrollview.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
  main_box->pack_start(scrollview);
  
  //The table
  Gtk::TreeModel::ColumnRecord *col_record = new Gtk::TreeModel::ColumnRecord();
  col_id = new Gtk::TreeModelColumn<time_t>();
  col_no = new Gtk::TreeModelColumn<std::string>();
  col_name = new Gtk::TreeModelColumn<std::string>();
  col_desc = new Gtk::TreeModelColumn<std::string>();
  col_start_date = new Gtk::TreeModelColumn<std::string>();
  col_end_date = new Gtk::TreeModelColumn<std::string>();
  col_finished = new Gtk::TreeModelColumn<bool>();

  col_record->add(*col_id);
  col_record->add(*col_no);
  col_record->add(*col_name);
  col_record->add(*col_desc);
  col_record->add(*col_start_date);
  col_record->add(*col_end_date);
  col_record->add(*col_finished);

  ref_tree_model = Gtk::ListStore::create(*col_record);
  treeview->set_model(ref_tree_model);

  std::list<Activity> lact = project->get_activities();
  Gtk::TreeModel::Row row;
  for(std::list<Activity>::iterator it = lact.begin(); it != lact.end(); it++)
  {
    row = *(ref_tree_model->append());
    row[*col_id] = it->get_id();
    row[*col_no] = it->get_number();
    row[*col_name] = it->get_name();
    row[*col_desc] = it->get_description();
    row[*col_start_date] = it->get_start_date_str_eu();
    row[*col_end_date] = it->get_end_date_str_eu();
    row[*col_finished] = it->is_finished();
  }
  
  treeview->append_column(_("Number"), *col_no);
  treeview->append_column(_("Name"), *col_name);
  treeview->append_column(_("Description"), *col_desc);
  treeview->append_column(_("Start date"), *col_start_date);
  treeview->append_column(_("End date"), *col_end_date);
  treeview->append_column(_("Finished"), *col_finished);
  treeview->set_headers_clickable(true);
  treeview->set_grid_lines(Gtk::TREE_VIEW_GRID_LINES_BOTH);

  for(int i=0; i < 6; i++)
  {
    Gtk::TreeView::Column *pColumn = treeview->get_column(i);
    pColumn->set_resizable(true);
    pColumn->set_sort_column(i+1);
  }
}

void ActivitiesWindow::on_action_file_new()
{
  ActivityDialog ad(this);
  ad.run();
}

void ActivitiesWindow::on_action_file_edit()
{

}

void ActivitiesWindow::on_action_file_delete()
{
  Glib::RefPtr<Gtk::TreeSelection> ref_tree_selection;
  Gtk::TreeModel::iterator iter;
  ref_tree_selection = treeview->get_selection();
  iter = ref_tree_selection->get_selected();
  if(iter)
  {
    Gtk::TreeModel::Row row = *iter;
    Glib::ustring msg;
    time_t act_id = row.get_value(*col_id);
    msg = row.get_value(*col_no);
    msg += "\n" + row.get_value(*col_name);
    msg += "\n" + row.get_value(*col_desc);
    
    Gtk::MessageDialog delete_dialog(*this, "", false, Gtk::MESSAGE_WARNING, Gtk::BUTTONS_YES_NO, true);
    delete_dialog.set_message(_("Do you want to delete activity?"));
    delete_dialog.set_secondary_text(msg);
    int response = delete_dialog.run();
    delete_dialog.hide();
    if(response == Gtk::RESPONSE_YES)
    {
      if(project->remove_activity(act_id))
      {
	ref_tree_model->erase(iter);
	Gtk::MessageDialog confirm_dialog(*this, "", false, Gtk::MESSAGE_INFO, Gtk::BUTTONS_OK, true);
	confirm_dialog.set_message(_("Activity deleted: "));
	confirm_dialog.set_secondary_text(msg);
	confirm_dialog.run();
      }
      else
      {
	Gtk::MessageDialog err_dialog(*this, "", false, Gtk::MESSAGE_ERROR, Gtk::BUTTONS_OK, true);
	err_dialog.set_message(_("Error: Can not delete activity: "));
	err_dialog.set_secondary_text(msg);
	err_dialog.run();
	new_error("Error: Can not delete activity with id: " + act_id, 
		  "activitieswindow.cpp", "void ActivitiesWindow::on_action_file_delete()");
      }
    }


  }
}

void ActivitiesWindow::on_action_file_exit()
{
  delete this;
}

void ActivitiesWindow::on_action_help_help()
{

}

void ActivitiesWindow::on_action_help_about()
{
  About a;
  a.run();
}
