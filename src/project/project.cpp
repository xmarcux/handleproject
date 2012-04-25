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
#include "../files.h"
#include <ctime>
#include <cctype>
#include <sstream>


Project::Project(time_t project_id, std::string project_no, std::string project_name,
		 std::string description, std::string project_leader_name, 
		 std::string project_leader_surname, std::string project_leader_initials,
		 int start_year, int start_month, int start_day, 
		 int end_year, int end_month, int end_day)
  : Date(start_year, start_month, start_day, end_year, end_month, end_day),
    project_id(project_id), project_no(project_no), project_name(project_name),
    description(description),
    project_leader(Staff(project_leader_name, project_leader_surname, project_leader_initials, "")),
    sort_activities(start_date_sort)
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
    description(description), project_leader(project_leader), sort_activities(start_date_sort)
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
    project_leader(Staff(project_leader_name, project_leader_surname, project_leader_initials, "")),
    sort_activities(start_date_sort)
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
    description(description), project_leader(project_leader), sort_activities(start_date_sort)
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
    project_leader(Staff(project_leader_name, project_leader_surname, project_leader_initials, "")),
    sort_activities(start_date_sort)
{
  working_days_per_week = 5;
  working_hours_per_day = 8;
}

Project::Project(time_t project_id, std::string project_no, std::string project_name,
		 std::string description, Staff project_leader,
		 std::string start_date, std::string end_date)
  : Date(start_date, end_date), project_id(project_id), project_no(project_no),
    project_name(project_name), description(description),
    project_leader(project_leader), sort_activities(start_date_sort)
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
    project_leader(Staff(project_leader_name, project_leader_surname, project_leader_initials, "")),
    sort_activities(start_date_sort)
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
    description(description), project_leader(project_leader), sort_activities(start_date_sort)
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
    project_leader(Staff("", "")), sort_activities(start_date_sort)
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
    description(description), project_leader(Staff(start_date, end_date)), sort_activities(start_date_sort)
{
  time_t t;
  time(&t);
  project_id = t;
  working_days_per_week = 5;
  working_hours_per_day = 8;
}

Project::Project(std::string project_no, std::string project_name, std::string description,
	Staff project_leader, std::string start_date, std::string end_date)
  : Date(start_date, end_date), project_no(project_no), description(description),
    project_leader(project_leader), sort_activities(start_date_sort)
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
    description(description), project_leader(Staff("", "")), sort_activities(start_date_sort)
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
    project_leader(Staff(project_leader_name, project_leader_surname, project_leader_initials, "")),
   sort_activities(start_date_sort)
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
    description(description), project_leader(project_leader), sort_activities(start_date_sort)
{
  time_t t;
  time(&t);
  project_id = t;
  working_days_per_week = 5;
  working_hours_per_day = 8;
}

Project::Project(std::string project_no, std::string project_name, std::string description)
  : Date(true, ""), project_no(project_no), project_name(project_name), 
    description(description), project_leader(Staff("", "")), sort_activities(start_date_sort)
{
  time_t t;
  time(&t);
  project_id = t;
  working_days_per_week = 5;
  working_hours_per_day = 8;
}

Project::Project(std::string xmlstring)
  : Date(true, ""), project_leader(Staff("", ""))
{
  std::string str;
  size_t find1, find2;
  find1 = xmlstring.find("<staff>");
  find2 = xmlstring.find("</staff>");
  if(find1 != std::string::npos && find2 != std::string::npos)
    project_leader = Staff(xmlstring.substr(find1, find2 + 8 - find1));
  find1 = std::string::npos;
  find2 = std::string::npos;
  find1 = xmlstring.find("<id>");
  find2 = xmlstring.find("</id>");
  if(find1 != std::string::npos && find2 != std::string::npos)
  {
    std::stringstream ss;
    ss << xmlstring.substr(find1 + 4, find2 - find1 - 4);
    ss >> project_id;
    if(ss.fail())
      time(&project_id);
  }
  else
    time(&project_id);

  find1 = std::string::npos;
  find2 = std::string::npos;
  find1 = xmlstring.find("<number>");
  find2 = xmlstring.find("</number>");
  if(find1 != std::string::npos && find2 != std::string::npos)
  {
    project_no = xmlstring.substr(find1 + 8, find2 - find1 - 8);
  }

  find1 = std::string::npos;
  find2 = std::string::npos;
  find1 = xmlstring.find("<name>");
  find2 = xmlstring.find("</name>");
  if(find1 != std::string::npos && find2 != std::string::npos)
  {
    project_name = xmlstring.substr(find1 + 6, find2 - find1 - 6);
  }
  else
    project_name = "";

  find1 = std::string::npos;
  find2 = std::string::npos;
  find1 = xmlstring.find("<description>");
  find2 = xmlstring.find("</description>");
  if(find1 != std::string::npos && find2 != std::string::npos)
  {
    description = xmlstring.substr(find1 + 13, find2 - find1 - 13);
  }
  else
    description = "";

  find1 = std::string::npos;
  find2 = std::string::npos;
  find1 = xmlstring.find("<staff>");
  find2 = xmlstring.find("</staff>");
  if(find1 != std::string::npos && find2 != std::string::npos)
  {
    project_leader = Staff(xmlstring.substr(find1, find2 - find1 + 8));
  }
  else
    project_leader = Staff("", "");

  find1 = std::string::npos;
  find2 = std::string::npos;
  find1 = xmlstring.find("<activities_sort>");
  find2 = xmlstring.find("</activities_sort>");
  if(find1 != std::string::npos && find2 != std::string::npos)
  {
    std::string ssort = xmlstring.substr(find1 + 17, find2 - find1 - 17);
    if(ssort == "end_date_sort")
      sort_activities = end_date_sort;
    else if(ssort == "alpha_name_sort")
      sort_activities = alpha_name_sort;
    else if(ssort == "alpha_name_reverse_sort")
      sort_activities = alpha_name_reverse_sort;
    else
      sort_activities = start_date_sort;
  }
  else
    sort_activities = start_date_sort;

  find1 = std::string::npos;
  find2 = std::string::npos;
  find1 = xmlstring.find("<days_per_week>");
  find2 = xmlstring.find("</days_per_week>");
  if(find1 != std::string::npos && find2 != std::string::npos)
  {
    std::stringstream ss;
    ss << xmlstring.substr(find1 + 15, find2 - find1 - 15);
    ss >> working_days_per_week;
    if(ss.fail())
    {
      working_days_per_week = 5;
    }
  }
  else
    working_days_per_week = 5;

  find1 = std::string::npos;
  find2 = std::string::npos;
  find1 = xmlstring.find("<hours_per_day>");
  find2 = xmlstring.find("</hours_per_day>");
  if(find1 != std::string::npos && find2 != std::string::npos)
  {
    std::stringstream ss;
    ss << xmlstring.substr(find1 + 15, find2 - find1 - 15);
    ss >> working_hours_per_day;
    if(ss.fail())
    {
      working_hours_per_day = 8;
    }
  }
  else
    working_hours_per_day = 8;

  find1 = std::string::npos;
  find2 = std::string::npos;
  find1 = xmlstring.find("<finished>");
  find2 = xmlstring.find("</finished>");
  if(find1 != std::string::npos && find2 != std::string::npos)
  {
    if(xmlstring.substr(find1 + 10, find2 - find1 - 10) == "1")
      set_finished(true);
    else
      set_finished(false);
  }
  else
    set_finished(false);
  
  find1 = std::string::npos;
  find2 = std::string::npos;
  find1 = xmlstring.find("<start_year>");
  find2 = xmlstring.find("</start_year>");
  if(find1 != std::string::npos && find2 != std::string::npos)
  {
    std::stringstream ss;
    int year;
    ss << xmlstring.substr(find1 + 12, find2 - find1 -12);
    ss >> year;
    if(!ss.fail())
      set_start_year(year);
  }

  find1 = std::string::npos;
  find2 = std::string::npos;
  find1 = xmlstring.find("<start_month>");
  find2 = xmlstring.find("</start_month>");
  if(find1 != std::string::npos && find2 != std::string::npos)
  {
    std::stringstream ss;
    int month;
    ss << xmlstring.substr(find1 + 13, find2 - find1 - 13);
    ss >> month;
    if(!ss.fail())
      set_start_month(month);
  }

  find1 = std::string::npos;
  find2 = std::string::npos;
  find1 = xmlstring.find("<start_day>");
  find2 = xmlstring.find("</start_day>");
  if(find1 != std::string::npos && find2 != std::string::npos)
  {
    std::stringstream ss;
    int day;
    ss << xmlstring.substr(find1 + 11, find2 - find1 - 11);
    ss >> day;
    if(!ss.fail())
      set_start_day(day);
  }

  find1 = std::string::npos;
  find2 = std::string::npos;
  find1 = xmlstring.find("<end_year>");
  find2 = xmlstring.find("</end_year>");
  if(find1 != std::string::npos && find2 != std::string::npos)
  {
    std::stringstream ss;
    int year;
    ss << xmlstring.substr(find1 + 10, find2 - find1 -10);
    ss >> year;
    if(!ss.fail())
      set_end_year(year);
  }

  find1 = std::string::npos;
  find2 = std::string::npos;
  find1 = xmlstring.find("<end_month>");
  find2 = xmlstring.find("</end_month>");
  if(find1 != std::string::npos && find2 != std::string::npos)
  {
    std::stringstream ss;
    int month;
    ss << xmlstring.substr(find1 + 11, find2 - find1 - 11);
    ss >> month;
    if(!ss.fail())
      set_end_month(month);
  }

  find1 = std::string::npos;
  find2 = std::string::npos;
  find1 = xmlstring.find("<end_day>");
  find2 = xmlstring.find("</end_day>");
  if(find1 != std::string::npos && find2 != std::string::npos)
  {
    std::stringstream ss;
    int day;
    ss << xmlstring.substr(find1 + 9, find2 - find1 - 9);
    ss >> day;
    if(!ss.fail())
      set_end_day(day);
  }
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

std::list<Activity> Project::get_activities() const
{
  return activities;
}

time_t Project::generate_new_id()
{
  time_t t;
  time(&t);
  project_id = t;
  return project_id;
}

Activity Project::get_activity(time_t activity_id)
{
  std::list<Activity>::iterator it;
  for( it = activities.begin(); it != activities.end(); it++)
  {
    if(it->get_id() == activity_id)
      return *it;
  }
  return Activity();
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

void Project::set_activities(std::list<Activity> acts, bool save_to_db)
{
  activities = acts;
  sort();
  if(save_to_db)
  {
    for(std::list<Activity>::iterator it=acts.begin(); it != acts.end(); it++)
      save_activity_to_db(&(*it), project_id);
  }
}

void Project::add_activity(Activity act, bool save_to_db)
{
  remove_activity(act.get_id());
  activities.push_back(act);
  sort();
  if(save_to_db)
    save_activity_to_db(&act, project_id);
}

int Project::remove_activity(time_t activity_id)
{
  std::list<Activity>::iterator it;
  for(it = activities.begin(); it != activities.end(); it++)
  {
    if(it->get_id() == activity_id)
    {
      delete_activity_from_db(&(*it), project_id);
      activities.erase(it);
      return 1;
    }
  }
  return -1;
}

void Project::sort_order_activities(Project::sort_order s)
{
  sort_activities = s;
  sort();
}

std::string Project::get_obj_xml_str() const
{
  std::stringstream ss, ss2, ss3, ss4, ss5, ss6, ss7, ss8, ss9;
  std::string xml_str = get_xml_head();
  std::string xml_staff;
  size_t find;
  xml_str += get_DTD_str();
  xml_str += get_first_level_open_tag("project");
  ss << project_id;
  xml_str += get_second_level_object("id", ss.str());
  xml_str += get_second_level_object("number", project_no);
  xml_str += get_second_level_object("name", project_name);
  xml_str += get_second_level_object("description", description);
  xml_staff = project_leader.get_obj_xml_str();
  find = xml_staff.find("<staff>");
  xml_staff = xml_staff.substr(find);
  find = xml_staff.find("\n");
  xml_staff = xml_staff.insert(find + 1, "\t\t");
  find = xml_staff.find("\n", find + 1);
  xml_staff = xml_staff.insert(find + 1, "\t\t");
  find = xml_staff.find("\n", find + 1);
  xml_staff = xml_staff.insert(find + 1, "\t\t");
  find = xml_staff.find("\n", find + 1);
  xml_staff = xml_staff.insert(find + 1, "\t\t");
  find = xml_staff.find("\n", find + 1);
  xml_staff = xml_staff.insert(find + 1, "\t\t");
  find = xml_staff.find("\n", find + 1);
  xml_staff = xml_staff.insert(find + 1, "\t\t");
  find = xml_staff.find("\n", find + 1);
  xml_staff = xml_staff.insert(find + 1, "\t\t");
  find = xml_staff.find("\n", find + 1);
  xml_staff = xml_staff.insert(find + 1, "\t\t");
  find = xml_staff.find("\n", find + 1);
  xml_staff = xml_staff.insert(find + 1, "\t\t");
  xml_staff = "\n\t\t" + xml_staff + "\t";
  xml_str += get_second_level_object("projectleader", xml_staff);
  if(sort_activities == end_date_sort)
    xml_str += get_second_level_object("activities_sort", "end_date_sort");
  else if(sort_activities == alpha_name_sort)
    xml_str += get_second_level_object("activities_sort", "alpha_name_sort");
  else if(sort_activities == alpha_name_reverse_sort)
    xml_str += get_second_level_object("activities_sort", "alpha_name_reverse_sort");
  else
    xml_str += get_second_level_object("activities_sort", "start_date_sort");
  if(is_finished())
    xml_str += get_second_level_object("finished", "1");
  else
    xml_str += get_second_level_object("finished", "0");
  ss2 << working_days_per_week;
  xml_str += get_second_level_object("days_per_week", ss2.str());
  ss3 << working_hours_per_day;
  xml_str += get_second_level_object("hours_per_day", ss3.str());
  ss4 << get_start_year();
  xml_str += get_second_level_object("start_year", ss4.str());
  ss5 << get_start_month();
  xml_str += get_second_level_object("start_month", ss5.str());
  ss6 << get_start_day();
  xml_str += get_second_level_object("start_day", ss6.str());
  ss7 << get_end_year(); 
  xml_str += get_second_level_object("end_year", ss7.str());
  ss8 << get_end_month();
  xml_str += get_second_level_object("end_month", ss8.str());
  ss9 << get_end_day();
  xml_str += get_second_level_object("end_day", ss9.str());
  xml_str += get_first_level_close_tag("project");
  return xml_str;
}

time_t Project::get_id() const
{
  return project_id;
}

void Project::sort()
{
  if(sort_activities == end_date_sort)
    activities.sort(activities_sort_end_date_order);
  else if(sort_activities == alpha_name_sort)
    activities.sort(activities_sort_name_order);
  else if(sort_activities == alpha_name_reverse_sort)
    activities.sort(activities_sort_reverse_name_order);
  else
    activities.sort(activities_sort_start_date_order);
}

std::string Project::get_DTD_str() const
{
  std::string str = "<!DOCTYPE project [";
  str += "\n\t<!ELEMENT project (id, number,  name, description, projectleader, activities_sort, finished, days_per_week, hours_per_day, start_year, start_month, start_day, end_year, end_month, end_day)>";
  str += "\n\t<!ELEMENT id\t\t(#PCDATA)>";
  str += "\n\t<!ELEMENT number\t(#PCDATA)>";
  str += "\n\t<!ELEMENT name\t\t(#PCDATA)>";
  str += "\n\t<!ELEMENT description\t(#PCDATA)>";
  str += "\n\t<!ELEMENT projectleader\t(staff)>";
  str += "\n\t<!ELEMENT activities_sort\t(#PCDATA)>";
  str += "\n\t<!ELEMENT finished\t(#PCDATA)>";
  str += "\n\t<!ELEMENT days_per_week\t(#PCDATA)>";
  str += "\n\t<!ELEMENT hours_per_day\t(#PCDATA)>";
  str += "\n\t<!ELEMENT week_hours\t(#PCDATA)>";
  str += "\n\t<!ELEMENT day_hours\t(#PCDATA)>";
  str += "\n\t<!ELEMENT start_year\t(#PCDATA)>";
  str += "\n\t<!ELEMENT start_month\t(#PCDATA)>";
  str += "\n\t<!ELEMENT start_day\t(#PCDATA)>";
  str += "\n\t<!ELEMENT end_year\t(#PCDATA)>";
  str += "\n\t<!ELEMENT end_month\t(#PCDATA)>";
  str += "\n\t<!ELEMENT end_day\t(#PCDATA)>";
  str += "\n\t<!ELEMENT staff (id, name, surname, initials, profession, week_hours, day_hours, days_per_week)>";
  str += "\n]>\n";
  return str;
}

bool activities_sort_start_date_order(Activity a, Activity b)
{
  if(a.get_start_year() <= b.get_start_year())
  {
    if(a.get_start_month() <= b.get_start_month())
    {
      if(a.get_start_day() <= b.get_start_day())
	return true;
      else
	return false;
    }
    else
      return false;
  }
  else
    return false;
}

bool activities_sort_end_date_order(Activity a, Activity b)
{
  if(a.get_end_year() <= b.get_end_year())
  {
    if(a.get_end_month() <= b.get_end_month())
    {
      if(a.get_end_day() <= b.get_end_day())
	return true;
      else
	return false;
    }
    else
      return false;
  }
  else
    return false;
}

bool activities_sort_name_order(Activity a, Activity b)
{
  size_t length = 0;
  std::string str_a, str_b;
  str_a = a.get_name();
  str_b = b.get_name();

  for(size_t i = 0; i < str_a.length(); i++)
    str_a[i] = tolower(str_a[i]);

  for(size_t j = 0; j < str_b.length(); j++)
    str_b[j] = tolower(str_b[j]);

  if(str_a.length() <= str_b.length())
    length = str_a.length();
  else
    length = str_b.length();

  for(size_t k = 0; k < length; k++)
  {
    if(str_a[k] >= 232 && str_a[k] <= 235)
      str_a[k] = 'e';
    if(str_b[k] >= 232 && str_b[k] <= 235)
      str_b[k] = 'e';
    if(str_a[k] >= 236 && str_a[k] <= 239)
      str_a[k] = 'i';
    if(str_b[k] >= 236 && str_b[k] <= 239)
      str_b[k] = 'i';
    if(str_a[k] >= 242 && str_a[k] <= 243)
      str_a[k] = 'o';
    if(str_b[k] >= 242 && str_b[k] <= 243)
      str_b[k] = 'o';
    if(str_a[k] >= 249 && str_a[k] <= 250)
      str_a[k] = 'u';
    if(str_b[k] >= 249 && str_b[k] <= 250)
      str_b[k] = 'u';
    if(str_a[k] == 228)
      str_a[k] = 230;
    if(str_b[k] == 228)
      str_b[k] = 230;
    if(str_a[k] > str_b[k])
    {
      return false;
    }
    if(str_a[k] < str_b[k])
    {
      return true;
    }
  }
  return true;
}

bool activities_sort_reverse_name_order(Activity a, Activity b)
{
  return !activities_sort_name_order(a, b);
}
