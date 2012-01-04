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
#include <iostream>

using namespace std;

int main (int argc, char *argv[])
{
	initdb();

	Staff s("Marcus", "Pedersén", "Serviceingenjör", 40.0);
	cout << s.get_name() << " " << s.get_surname() << s.get_profession() << endl;
	cout << s.get_week_working_hours() << "" << s.get_day_working_hours();
	cout << " " << s.get_working_days_per_week() << endl;
	
	s.set_working_days_per_week(7.0);
	cout << s.get_name() << " " << s.get_surname() << s.get_profession() << endl;
	cout << s.get_week_working_hours() << "" << s.get_day_working_hours();
	cout << " " << s.get_working_days_per_week() << endl;

	cout << s.get_obj_xml_str();

	s.set_week_working_hours(7.0);
	cout << s.get_name() << " " << s.get_surname() << s.get_profession() << endl;
	cout << s.get_week_working_hours() << "" << s.get_day_working_hours();
	cout << " " << s.get_working_days_per_week() << endl << endl;

	string xmlstr = "<?xml version=\"1.0\" ?>\
<!DOCTYPE staff [\
	<!ELEMENT staff(name, surname, profession, week_hours, day_hours, days_per_week)>\
	<!ELEMENT name		(#CDATA)>\
	<!ELEMENT surname	(#CDATA)>\
	<!ELEMENT profession	(#CDATA)>\
	<!ELEMENT week_hours	(#CDATA)>\
	<!ELEMENT day_hours	(#CDATA)>\
	<!ELEMENT days_per_week	(#CDATA)>\
]>\
<staff>\
	<name>Putte</name>\
	<surname>Karlsson</surname>\
	<profession>Rörmockare</profession>\
	<id>1234567890</id>\
	<week_hours>100</week_hours>\
	<day_hours>20</day_hours>\
	<days_per_week>5</days_per_week>\
</staff>";

	Staff p(xmlstr);

	cout << p.get_name() << " " << p.get_surname() << " " <<  p.get_profession() << endl;
	cout << p.get_week_working_hours() << " " << p.get_day_working_hours();
	cout << " " << p.get_working_days_per_week() << endl << p.get_id() << endl;
	
}
