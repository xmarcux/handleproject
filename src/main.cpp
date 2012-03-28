/****************************************************************************
 *                                                                          *
 *    Handle Project, an application for managing projects and employees.   *
 *    Copyright (C) 2011,2012  Marcus Pedersén marcux@handleproject.org     *
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

/* This is where the main loop starts for Handle Project.
 * Database is initialized if needed and the main gtk+ loop
 * is started.
 */

#include "files.h"

//testing
//#include "xmlstr.h"
#include <string>

#include "staff/staff.h"
#include "staff/job.h"
#include "project/project.h"
#include "project/activity.h"
#include "ui/mainwindow.h"
#include <iostream>
#include <list>
#include <ctime>
#include <gtkmm/main.h>

using namespace std;

int main (int argc, char *argv[])
{
  initdb();
  /* To create projects in database for test
    Project p1(12345678, "we-92771-900", "A small house", 
	     "This project just contains a construction of a small house.",
	     "Kit", "Meiers", "KM", 
	     2011, 2, 18,
	     2012, 6, 5);
  save_object_to_db(&p1);
  Activity a1(1234567801, "Put down concreate", "Make the base of the house.",
	      "2011-02-28", "2011-08-11");
  p1.add_activity(a1);
  Activity a2(1234567802, "Build walls", "Build up all walls for the house.",
	      "2011-08-11", "2011-09-23");
  p1.add_activity(a2);
  Activity a3(1234567803, "Make roof", "After the walls are built, put the roof on top.",
	      "2011-09-27", "2012-03-01");
  p1.add_activity(a3);

  Project p2(12345679, "827773", "Burner", 
	     "Implementation and installation of small burner for a\n single family house",
	     "John", "Fergusson", "JF", 
	     2009, 1, 4,
	     2011, 9, 18);
  save_object_to_db(&p2);
  Activity a4(1234567901, "Order burner", "Burner must be ordered to be delivered in time.",
	      "2009-01-08", "2009-01-08");
  p2.add_activity(a4);
  Activity a5(1234567902, "Burner delivery", "Latest date for burner delivery",
	      "2011-01-10", "2011-01-10");
  p2.add_activity(a5);

  Project p3(123456710, "AA 79 JB", "New block", 
	     "A project in building up an entire block with houses and infrastructure.",
	     "Bert", "Johnsson", "BJ", 
	     2006, 8, 30,
	     2026, 1, 1);
  save_object_to_db(&p3);
  Activity a6(12345671001, "Concreate.", "Other entrepeneur put down concreate.",
	      "2007-02-28", "2007-10-18");
  p3.add_activity(a6);
  Activity a7(12345671002, "Build houses", "Building of all 16 houses in the block.",
	      "2008-04-20", "2010-01-01");
  p3.add_activity(a7);

  Project p4(123456711, "P1", "New server delivery", 
	     "Configuration, installation and delivery of one new server,",
	     "Curt", "Jobs", "KJ", 
	     2012, 2, 1,
	     2012, 12, 23);
  save_object_to_db(&p4);
  Activity a8(12345671101, "Make specification", "Make calculations and decide hardware needed.",
	      "2012-02-05", "2012-03-01");
  p4.add_activity(a8);
  Activity a9(12345671102, "Build houses", "Building of all 16 houses in the block.",
	      "2008-04-20", "2010-01-01");
  p4.add_activity(a9);

  Project p5(123456712, "QQQ-22-LLL", "Fibercabel", 
	     "Digging, installation, patching of a 12 miles long fibercabel.",
	     "Ann", "Sets", "AS", 
	     2006, 3, 18,
	     2008, 1, 6);
  save_object_to_db(&p5);
  Activity a10(12345671201, "Messure length", "Messure length and dicide way to draw cable.",
	      "2006-04-01", "2006-11-29");
  p5.add_activity(a10);
  Activity a11(12345671202, "Dig the road", "Digging of the road where the fiber shoul be.",
	      "2007-05-02", "2007-10-02");
  p5.add_activity(a11);

  Project p6(123456713, "PROJ1", "First official job", 
	     "The first job sold by our salesperson.",
	     "John", "Johnsson", "JJ", 
	     2001, 2, 23,
	     2003, 12, 8);
  save_object_to_db(&p6);*/
  Gtk::Main kit(argc, argv);
  MainWindow w;
  Gtk::Main::run(w);
  
  return 0;
}
