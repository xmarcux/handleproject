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

void ActivitiesWindow::on_action_file_new()
{

}

void ActivitiesWindow::on_action_file_edit()
{

}

void ActivitiesWindow::on_action_file_delete()
{

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
