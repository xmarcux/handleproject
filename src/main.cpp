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
#include <iostream>
#include <list>
#include <ctime>

using namespace std;

int main (int argc, char *argv[])
{
	initdb();

	//testing
	//	Job j(1234, "My first job", 4321, 1912, 3, 4, 2012, 4, 5, 8);
	Job j(1234, "My first job");
	cout << "Startyear: " << j.get_start_year() << endl;
	cout << "Startmonth: " << j.get_start_month() << endl;
	cout << "Startday: " << j.get_start_day() << endl;
	cout << "Endyear: " << j.get_end_year() << endl;
	cout << "Endmonth: " << j.get_end_month() << endl;
	cout << "Endday: " << j.get_end_day() << endl;
	cout << "Hours per day: " << j.get_hours_per_day() << endl;
	cout << "Staffid: " << j.get_staff_id() << endl;
	cout << "Projectid: " << j.get_project_id() << endl;
	cout << "Desc: " << j.get_description() << endl;
	cout << "Startdtate str eu: " << j.get_start_date_str_eu() << endl;
	cout << "Enddate str eu: " << j.get_end_date_str_eu() << endl;
	cout << "Startdtate str us: " << j.get_start_date_str_us() << endl;
	cout << "Enddate str us: " << j.get_end_date_str_us() << endl << endl;
	cout << "Start_year: " << j.get_start_year() << endl;
	j.set_start_date("2012-01-04");
	j.set_end_date("2012-02-16");

	cout << j.get_obj_xml_str() << endl;
	cout << "working days: " << j.total_working_hours(5) << endl << endl;
	//	string s1 = j.get_obj_xlm_str();
	Job j2(j.get_obj_xml_str());
	cout << "j2" << endl << j2.get_obj_xml_str() << endl << endl;
	j.set_finished(true);
	//	string s2 = j.get_obj_xlm_str();
	Job j3(j.get_obj_xml_str());
	cout << "j3" << endl << j3.get_obj_xml_str() << endl << endl;
	/* 	cout << "Startdtate str eu: " << j.get_start_date_str_eu() << endl;
 	cout << "Enddate str eu: " << j.get_end_date_str_eu() << endl;
	j.set_start_date("1919-01-32");*/
	//	j.set_end_date("1/2/11");
	// 	cout << "Startdtate str eu: " << j.get_start_date_str_eu() << endl;
	// 	cout << "Enddate str eu: " << j.get_end_date_str_eu() << endl;
	/*	j.set_start_date("12-02-29");
	j.set_end_date("6/30/1800");
 	cout << "Startdtate str eu: " << j.get_start_date_str_eu() << endl;
 	cout << "Enddate str eu: " << j.get_end_date_str_eu() << endl;
	/*
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
	/*
	if(save_object_to_db(&s) < 0)
	  cout << "can not write s object to file" << endl;
	if(save_object_to_db(&p) < 0)
	  cout << "can not write p object to file" << endl;
	*/
	/*
	list<Staff> ls = get_staff_from_db();
	list<Staff>::iterator it = ls.begin();
	for(;it != ls.end(); it++)
	{
	  cout << it->get_obj_xml_str() << endl;
	}


	//Testing time
	struct tm t;
	t.tm_year = 2012 -1900;
	t.tm_mon = 6 -1;
	t.tm_mday = 17;
	t.tm_hour = 1;
	t.tm_min = 0;
	time_t tt = mktime(&t);
	cout << "Veckodag innan: " << t.tm_wday << endl;
	if(t.tm_wday == 0)
	  t.tm_mday = t.tm_mday - 6;
	else
	  t.tm_mday = 1 + t.tm_mday - t.tm_wday;
	mktime(&t);
	cout << "mon: " << t.tm_mon << endl;
	cout << "Mday: " << t.tm_mday << endl;
	cout << "Veckodag innan: " << t.tm_wday << endl;
	struct tm *ttm;
	ttm = localtime(&tt);
	cout << "Veckodag: " << ttm->tm_wday << endl;
	*/

	
	Project p = Project("PROJ-23917-NO", "The proj name", "This is what this project is all aboute and so on and so on and so on........", "Putte", "Karlsson", "PK", 2011, 3, 16, 2015, 1, 29);

	cout << "Total working days: " << p.get_total_working_days() << endl;
	cout << "Project as xml: " << endl << p.get_obj_xml_str() << endl << endl;

	/*save_object_to_db(&p);
	list<Project> projl = get_projects_from_db();
	cout << projl.front().get_obj_xml_str() << endl;
	*/

	Activity a = Activity(123456789, "activity name", "description bla, bla , bla", "NO-03-dh-09", "2011-12-03", "2012-02-12");//2010, 11, 5, 2011, 12, 13);//, 
	a.set_finished(true);
	cout << "name: " << a.get_name() << endl;
	cout << "id: " << a.get_id() << endl;
	cout << "number: " << a.get_number() << endl;
	cout << "desc: " << a.get_description() << endl;
	cout << "finished: " << a.is_finished() << endl;
	cout << "is milestone: " << a.is_milestone() << endl;
	cout << "is_late: " << a.is_late() << endl;
	cout << a.get_obj_xml_str();
	cout << endl << "New activity: " << endl;
	Activity b = Activity(a.get_obj_xml_str());
	cout << b.get_obj_xml_str() << endl;
}
