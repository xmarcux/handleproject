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

#include "projectwindow.h"
#include "../files.h"
#include "about.h"
#include "neweditdialog.h"
#include <glibmm/i18n.h>
#include <gtkmm/stock.h>

ProjectWindow::ProjectWindow(time_t project_id, MainWindow *mainwindow)
  : project("", "", ""), mainwindow(mainwindow), main_box(new Gtk::VBox(false, 0))
{
  project = get_project_from_db(project_id);
  set_title("Handle Project\t" + (_("Project number: ") + project.get_project_no()) +
	    _("\tProject name: ") + project.get_project_name());
  set_icon_from_file("images/HaPr_high_80x100_ver2.gif");
  set_position(Gtk::WIN_POS_CENTER);
  add(*Gtk::manage(main_box));
  create_menu();

  set_size_request(200, 200);
  set_default_size(500, 300);
  set_position(Gtk::WIN_POS_CENTER);
  maximize();
}

void ProjectWindow::update_view()
{
  set_title("Handle Project\t" + (_("Project number: ") + project.get_project_no()) +
	    _("\tProject name: ") + project.get_project_name());
}

void ProjectWindow::create_menu()
{
  // Create actions for menu and toolbar.
  refActionGroup = Gtk::ActionGroup::create();

  // File menu
  refActionGroup->add(Gtk::Action::create("MenuFile", _("_File")));

  // File submenu
  refActionGroup->add(Gtk::Action::create("FileExit", Gtk::Stock::QUIT, _("_Quit")),
		      sigc::mem_fun(*this, &ProjectWindow::on_action_file_exit));

  // Project menu
  refActionGroup->add(Gtk::Action::create("MenuProject", _("P_roject")));

  // Project submenu
  refActionGroup->add(Gtk::Action::create("ProjectActivities", Gtk::Stock::EDIT, _("Edit _activities...")));
  refActionGroup->add(Gtk::Action::create("ProjectProperties", Gtk::Stock::PROPERTIES, _("Pr_operties...")),
		      sigc::mem_fun(*this, &ProjectWindow::on_action_project_properties));

  // Help menu
  refActionGroup->add(Gtk::Action::create("MenuHelp", _("_Help")));

  // Help submenu
  refActionGroup->add(Gtk::Action::create("HelpHelp", Gtk::Stock::HELP));
  refActionGroup->add(Gtk::Action::create("HelpAbout", Gtk::Stock::ABOUT, _("About Handle Project")),
		      sigc::mem_fun(*this, &ProjectWindow::on_action_help_about));

  refUIManager = Gtk::UIManager::create();
  refUIManager->insert_action_group(refActionGroup);

  add_accel_group(refUIManager->get_accel_group());

  Glib::ustring ui_info =
    "<ui>"
    "  <menubar name='MenuBar'>"
    "    <menu action='MenuFile'>"
    "      <menuitem action='FileExit'/>"
    "    </menu>"
    "    <menu action='MenuProject'>"
    "      <menuitem action='ProjectProperties'/>"
    "      <separator/>"
    "      <menuitem action='ProjectActivities'/>"
    "    </menu>"
    "    <menu action='MenuHelp'>"
    "      <menuitem action='HelpHelp'/>"
    "      <menuitem action='HelpAbout'/>"
    "    </menu>"
    "  </menubar>"
    "  <toolbar name='ToolBar'>"
    "    <toolitem action='ProjectActivities'/>"
    "  </toolbar>"
    "</ui>";

  try
  {
    refUIManager->add_ui_from_string(ui_info);
  }
  catch(const Glib::Error& err)
  {
    new_error("Can not create menu and toolbar." + err.what(), "projectwindow.cpp",
	      "ProjectWindow::create_menu()");
  }

  Gtk::Widget* pMenubar = refUIManager->get_widget("/MenuBar");
  if(pMenubar)
    main_box->pack_start(*pMenubar, Gtk::PACK_SHRINK);
  Gtk::Widget* pToolbar = refUIManager->get_widget("/ToolBar");
  if(pToolbar)
    main_box->pack_start(*pToolbar, Gtk::PACK_SHRINK);
}

void ProjectWindow::on_action_file_exit()
{
  delete this;
}

void ProjectWindow::on_action_project_properties()
{
  NewEditDialog edit(mainwindow , this, &project);
}

void ProjectWindow::on_action_help_about()
{
  About a;
  a.run();
}

ProjectWindow::~ProjectWindow()
{

}
