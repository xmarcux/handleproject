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
#include <gtkmm/window.h>

//#include <gtkmm/treemodelcolumn.h>

/* This class is the window that
 * shows one specific project.
 * Window will show all activities,
 * information on project and
 * ways to be able to change project.
 */
class ProjectWindow : public Gtk::Window
{
 public:
  ProjectWindow();
  //  ProjectWindow(Project p);
  virtual ~ProjectWindow();

 private:
  //Gtk::TreeModelColumn<std::string> *test_c;
};

#endif
