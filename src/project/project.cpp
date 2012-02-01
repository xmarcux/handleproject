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

#include "project.h"
#include "../xmlstr.h"
#include <ctime>
#include <sstream>

Project::Project(time_t project_id, std::string project_no, std::string project_name,
		 std::string description, std::string project_leader_name, 
		 std::string project_leader_surname, std::string project_leader_initials,
		 int start_year, int start_month, int start_day, 
		 int end_year, int end_month, int end_day)
  : Date(start_year, start_month, start_day, end_year, end_month, end_day),
    project_id(project_id), project_no(project_no), project_name(project_name),
    description(description), 
    project_leader(Staff(project_leader_name, project_leader_surname, project_leader_initials, ""))
{
  working_days_per_week = 5;
  working_hours_per_day = 8;
}

Project::Project(time_t project_id, std::string project_no, std::string project_name,
		 std::string description, Staff project_leader,
		 int start_year, int start_month, int start_day, 
		 int end_year, int end_month, int end_day)
  : Date(start_year, start_month, start_day, end_year, end_month, end_day),
    project_id(project_id), project_no(project_no), project_name(project_name),
    description(description), project_leader(project_leader)
{
  working_days_per_week = 5;
  working_hours_per_day = 8;

}


Project::Project(std::string project_no, std::string project_name,
		 std::string description, std::string project_leader_name,
		 std::string project_leader_surname, std::string project_leader_initials,
		 int start_year, int start_month, int start_day,
		 int end_year, int end_month, int end_day)
  : Date(start_year, start_month, start_day, end_year, end_month, end_day),
    project_no(project_no), project_name(project_name),
    description(description),
    project_leader(Staff(project_leader_name, project_leader_surname, project_leader_initials, ""))
{
  time_t t;
  time(&t);
  project_id = t;
  working_days_per_week = 5;
  working_hours_per_day = 8;
}

Project::Project(std::string project_no, std::string project_name,
		 std::string description, Staff project_leader,
		 int start_year, int start_month, int start_day,
		 int end_year, int end_month, int end_day)
  : Date(start_year, start_month, start_day, end_year, end_month, end_day),
    project_no(project_no), project_name(project_name),
    description(description), project_leader(project_leader)
{
  time_t t;
  time(&t);
  project_id = t;
  working_days_per_week = 5;
  working_hours_per_day = 8;
}


Project::Project(time_t project_id, std::string project_no, std::string project_name,
		 std::string description, std::string project_leader_name,
		 std::string project_leader_surname, std::string project_leader_initials,
		 std::string start_date, std::string end_date)
  : Date(start_date, end_date), project_id(project_id), project_no(project_no),
    project_name(project_name), description(description),
    project_leader(Staff(project_leader_name, project_leader_surname, project_leader_initials, ""))
{
  working_days_per_week = 5;
  working_hours_per_day = 8;
}

Project::Project(time_t project_id, std::string project_no, std::string project_name,
		 std::string description, Staff project_leader,
		 std::string start_date, std::string end_date)
  : Date(start_date, end_date), project_id(project_id), project_no(project_no),
    project_name(project_name), description(description), project_leader(project_leader)
{
  working_days_per_week = 5;
  working_hours_per_day = 8;
}

Project::Project(std::string project_no, std::string project_name, 
		 std::string description, std::string project_leader_name,
		 std::string project_leader_surname, std::string project_leader_initials,
		 std::string end_date)
  : Date(false, end_date), project_no(project_no), project_name(project_name),
    description(description),
    project_leader(Staff(project_leader_name, project_leader_surname, project_leader_initials, ""))
{
  time_t t;
  time(&t);
  project_id = t;
  working_days_per_week = 5;
  working_hours_per_day = 8;
}

Project::Project(std::string project_no, std::string project_name, 
		 std::string description, Staff project_leader, 
		 std::string end_date)
  : Date(false, end_date), project_no(project_no), project_name(project_name),
    description(description), project_leader(project_leader)
{
  time_t t;
  time(&t);
  project_id = t;
  working_days_per_week = 5;
  working_hours_per_day = 8;
}

Project::Project(std::string project_no, std::string project_name, std::string description,
		 int start_year, int start_month, int start_day,
		 int end_year, int end_month, int end_day)
  : Date(start_year, start_month, start_day, end_year, end_month, end_day),
    project_no(project_no), project_name(project_name), description(description),
    project_leader(Staff("", ""))
{
  time_t t;
  time(&t);
  project_id = t;
  working_days_per_week = 5;
  working_hours_per_day = 8;
}

Project::Project(std::string project_no, std::string project_name, std::string description,
		 std::string start_date, std::string end_date)
  : Date(start_date, end_date), project_no(project_no), project_name(project_name),
    description(description), project_leader(Staff(start_date, end_date))
{
  time_t t;
  time(&t);
  project_id = t;
  //  project_leader = Staff("", "");
  working_days_per_week = 5;
  working_hours_per_day = 8;
}

Project::Project(std::string project_no, std::string project_name, std::string description,
	Staff project_leader, std::string start_date, std::string end_date)
  : Date(start_date, end_date), project_no(project_no), description(description),
    project_leader(project_leader)
{
  time_t t;
  time(&t);
  project_id = t;
  working_days_per_week = 5;
  working_hours_per_day = 8;
}

Project::Project(std::string project_no, std::string project_name, std::string description,
	Staff project_leader, int working_days_per_week, int working_hours_per_day,
	std::string start_date, std::string end_date)
  : Date(start_date, end_date), project_no(project_no), project_name(project_name),
    description(description), project_leader(Staff("", ""))
{
  time_t t;
  time(&t);
  project_id = t;
  set_working_days_per_week(working_days_per_week);
  set_working_hours_per_day(working_hours_per_day);
}

Project::Project(std::string project_no, std::string project_name,
		 std::string description, std::string project_leader_name,
		 std::string project_leader_surname, std::string project_leader_initials)
  : Date(true, ""), project_no(project_no), project_name(project_name),
    description(description),
    project_leader(Staff(project_leader_name, project_leader_surname, project_leader_initials, ""))
{
  time_t t;
  time(&t);
  project_id = t;
  working_days_per_week = 5;
  working_hours_per_day = 8;
}

Project::Project(std::string project_no, std::string project_name,
		 std::string description, Staff project_leader)
  : Date(true, ""), project_no(project_no), project_name(project_name),
    description(description), project_leader(project_leader)
{
  time_t t;
  time(&t);
  project_id = t;
  working_days_per_week = 5;
  working_hours_per_day = 8;
}

Project::Project(std::string project_no, std::string project_name, std::string description)
  : Date(true, ""), project_no(project_no), project_name(project_name), description(description),
    project_leader(Staff("", ""))
{
  time_t t;
  time(&t);
  project_id = t;
  working_days_per_week = 5;
  working_hours_per_day = 8;
}

std::string Project::get_project_no() const
{
  return project_no;
}

std::string Project::get_project_name() const
{
  return project_name;
}

std::string Project::get_description() const
{
  return description;
}

Staff Project::get_project_leader() const
{
  return project_leader;
}

std::string Project::get_project_leader_name() const
{
  return project_leader.get_name();
}

std::string Project::get_project_leader_surname() const
{
  return project_leader.get_surname();
}

std::string Project::get_project_leader_initials() const
{
  return project_leader.get_initials();
}

int Project::get_working_days_per_week() const
{
  return working_days_per_week;
}

int Project::get_working_hours_per_day() const
{
  return working_hours_per_day;
}

int Project::get_total_working_days() const
{
  struct tm tm_start, tm_end;
  int start_day, end_day;
  double datediff;
  tm_start.tm_year = get_start_year() - 1900;
  tm_start.tm_mon = get_start_month() -1;
  tm_start.tm_mday = get_start_day();
  tm_start.tm_hour = 1;
  tm_start.tm_min = 0;
  tm_start.tm_sec = 0;
  mktime(&tm_start);
  start_day = tm_start.tm_wday;
  if(tm_start.tm_wday == 0)
    tm_start.tm_mday = tm_start.tm_mday - 6;
  else
    tm_start.tm_mday = 1 + tm_start.tm_mday - tm_start.tm_wday;
  mktime(&tm_start);
  
  tm_end.tm_year = get_end_year() - 1900;
  tm_end.tm_mon = get_end_month() -1;
  tm_end.tm_mday = get_end_day();
  tm_end.tm_hour = 1;
  tm_end.tm_min = 0;
  tm_end.tm_sec = 0;
  mktime(&tm_end);
  end_day = tm_end.tm_wday;
  if(tm_end.tm_wday == 0)
    tm_end.tm_mday = tm_end.tm_mday - 6;
  else
    tm_end.tm_mday = 1 + tm_end.tm_mday - tm_end.tm_wday;
  mktime(&tm_end);

  datediff = difftime(mktime(&tm_end), mktime(&tm_start));
  datediff = ((((datediff/60)/60)/24)/7);
  datediff = datediff * working_days_per_week;

  if(start_day >= working_days_per_week || start_day == 0)
    datediff = datediff - working_days_per_week;
  else
    datediff = datediff - start_day + 1;
  if(end_day >= working_days_per_week || end_day == 0)
    datediff = datediff + working_days_per_week;
  else
    datediff = datediff + end_day;

  return datediff;
}

int Project::get_total_working_hours() const
{
  return get_total_working_days() * working_hours_per_day;
}

void Project::set_project_id(time_t proj)
{
  project_id = proj;
}

void Project::set_project_no(std::string no)
{
  project_no = no;
}

void Project::set_project_name(std::string name)
{
  project_name = name;
}

void Project::set_description(std::string desc)
{
  description = desc;
}

void Project::set_project_leader(Staff leader)
{
  project_leader =leader;
}

void Project::set_project_leader_name(std::string name)
{
  project_leader.set_name(name);
}

void Project::set_project_leader_surname(std::string surname)
{
  project_leader.set_surname(surname);
}

void Project::set_project_leader_initials(std::string init)
{
  project_leader.set_initials(init);
}

void Project::set_working_days_per_week(int days)
{
  if(days >= 0 && days <= 7)
    working_days_per_week = days;
}

void Project::set_working_hours_per_day(int hours)
{
  if(hours >= 0 && hours <= 24)
    working_hours_per_day = hours;
}

std::string Project::get_obj_xml_str() const
{
  std::stringstream ss, ss2, ss3;
  std::string xml_str = get_xml_head();
  xml_str += get_DTD_str();
  xml_str += get_first_level_open_tag("project");
  ss << project_id;
  xml_str += get_second_level_object("id", ss.str());
  xml_str += get_second_level_object("name", project_name);
  xml_str += get_second_level_object("description", description);
  xml_str += get_second_level_object("projectleader", project_leader.get_obj_xml_str());
  ss2 << working_days_per_week;
  xml_str += get_second_level_object("days_per_week", ss2.str());
  ss3 << working_hours_per_day;
  xml_str += get_second_level_object("hours_per_day", ss3.str());
  xml_str += get_first_level_close_tag("project");
  return xml_str;
}

time_t Project::get_id() const
{
  return project_id;
}

std::string Project::get_DTD_str() const
{
  std::string str = "<!DOCTYPE project [";
  str += "\n\t<!ELEMENT project (id, name, description, projectleader, days_per_week, hours_per_day)>";
  str += "\n\t<!ELEMENT id\t\t(#PCDATA)>";
  str += "\n\t<!ELEMENT name\t\t(#PCDATA)>";
  str += "\n\t<!ELEMENT description\t(#PCDATA)>";
  str += "\n\t<!ELEMENT projectleader\t(#PCDATA)>";
  str += "\n\t<!ELEMENT days_per_week\t(#PCDATA)>";
  str += "\n\t<!ELEMENT hours_per_day\t(#PCDATA)>";
  str += "\n]>\n";
  return str;
}
