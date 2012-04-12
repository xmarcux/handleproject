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

#include "splashwindow.h"
#include "mainwindow.h"
#include <gtkmm/box.h>
#include <gtkmm/image.h>
#include <gtkmm/label.h>
#include <glibmm/i18n.h>

SplashWindow::SplashWindow()
{
  set_title("Handle Project");
  set_decorated(false);
  set_icon_from_file("images/HaPr_high_80x100_ver2.gif");
  set_position(Gtk::WIN_POS_CENTER);

  Gtk::VBox *main_box = new Gtk::VBox();
  Gtk::manage(main_box);
  Gtk::Image *logo = new Gtk::Image("images/HandleProject_300x70.gif");
  main_box->pack_start(*logo);
  Gtk::manage(logo);

  Gtk::Label *cright = new Gtk::Label("Copyright (C) 2011, 2012 Marcus Pedersén\n");
  main_box->pack_start(*cright);
  Gtk::manage(cright);

  Gtk::Label *info1 = new Gtk::Label(_("Be in control of your projects."));
  main_box->pack_start(*info1);
  Gtk::manage(info1);

  Gtk::Label *info2 = new Gtk::Label(_("Handle your projects."));
  main_box->pack_start(*info2);
  Gtk::manage(info2);

  Gtk::Label *comment = new Gtk::Label(_("\n\nThis program is free software: you can redistribute it\nand/or modify it under the terms\nof the GNU General Public License\nas published by the Free Software Foundation,\neither version 3 of the License,\nor (at your option) any later version."));
  main_box->pack_start(*comment);
  Gtk::manage(comment);

  Gtk::Box *cont_area = get_vbox();
  cont_area->pack_start(*main_box);
  show_all_children();
}

SplashWindow::~SplashWindow()
{

}
