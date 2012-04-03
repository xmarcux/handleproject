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

#include "about.h"
#include <glibmm/i18n.h>
#include <gdkmm/pixbuf.h>
#include <fstream>

About::About()
{
  set_icon_from_file("images/HaPr_high_80x100_ver2.gif");
  set_logo(Gdk::Pixbuf::create_from_file("images/HandleProject_300x70.gif"));
  set_program_name("Handle Project");
  set_version("Alpha");
  set_copyright("Copyright (C) 2011, 2012 Marcus Pedersén");
  set_comments(_("Be in control of your projects.\nHandle your projects.\n\nThis program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.\nFor details click \"License\""));
  //  set_license_type(Gtk::LICENSE_GPL_3_0);
  int length;
  char *buffer;
  std::fstream stream;
  stream.open("images/GPLV3", std::fstream::in);
  stream.seekg(0, std::fstream::end);
  length = stream.tellg();
  stream.seekg(0,std::fstream::beg);
  buffer = new char[length];
  stream.read(buffer, length);
  stream.close();
  set_license(buffer);
  delete[] buffer;
  

  set_wrap_license(true);
  set_website("http://www.handleproject.org");
}
