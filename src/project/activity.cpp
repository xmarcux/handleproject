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

#include "activity.h"

#include <ctime>
#include <sstream>

Activity::Activity()
{
  time(&id);
  number = "";
  name = "";
  description = "";
}

Activity::Activity(time_t id, std::string name, std::string description, std::string number)
  : id(id), name(name), description(description), number(number)
{}

Activity::Activity(time_t id, std::string name, std::string description, std::string number,
		   int start_year, int start_month, int start_day,
		   int end_year, int end_month, int end_day)
  : Date(start_year, start_month, start_day, end_year, end_month, end_day),
    id(id), name(name), description(description), number(number)
{}

Activity::Activity(time_t id, std::string name, std::string description, std::string number,
		   std::string start_date, std::string end_date)
  : Date(start_date, end_date), id(id), name(name), description(description), number(number)
{}

Activity::Activity(time_t id, std::string name, std::string description)
  : id(id), name(name), description(description)
{
  number = "";
}

Activity::Activity(time_t id, std::string name, std::string description,
		   int start_year, int start_month, int start_day,
		   int end_year, int end_month, int end_day)
  : Date(start_year, start_month, start_day, end_year, end_month, end_day), 
    id(id), name(name), description(description)
{
  number = "";
}

Activity::Activity(time_t id, std::string name, std::string description, 
		   std::string start_date, std::string  end_date)
  : Date(start_date, end_date), id(id), name(name), description(description)
{
  number = "";
}

Activity::Activity(std::string name, std::string description, std::string number)
  : name(name), description(description), number(number)
{
  time(&id);
}

Activity::Activity(std::string name, std::string description, std::string number,
		   int start_year, int start_month, int start_day,
		   int end_year, int end_month, int end_day)
  : Date(start_year, start_month, start_day, end_year, end_month, end_day),
    name(name), description(description), number(number)
{
  time(&id);
}

Activity::Activity(std::string name, std::string description, std::string number,
		   std::string start_date, std::string end_date)
  : Date(start_date, end_date), name(name), description(description), number(number)
{
  time(&id);
}

Activity::Activity(std::string name, std::string description)
  : name(name), description(description)
{
  time(&id);
  number = "";
}

Activity::Activity(std::string name, std::string description, 
		   int start_year, int start_month, int start_day,
		   int end_year, int end_month, int end_day)
  : Date(start_year, start_month, start_day, end_year, end_month, end_day), 
    name(name), description(description)
{
  time(&id);
  number = "";
}

Activity::Activity(std::string name, std::string description,
		   std::string start_date, std::string end_date)
  : Date(start_date, end_date), name(name), description(description)
{
  time(&id);
  number = "";
}

//fix constructor
Activity::Activity(std::string xmlstring)
{

}

std::string Activity::get_number() const
{
  return number;
}

std::string Activity::get_name() const
{
  return name;
}

std::string Activity::get_description() const
{
  return description;
}

void Activity::set_id(time_t id)
{
  this->id = id;
}

void Activity::set_number(std::string no)
{
  number = no;
}

void Activity::set_name(std::string name)
{
  this->name = name;
}

void Activity::set_description(std::string desc)
{
  description = desc;
}

//fix method
std::string Activity::get_obj_xml_str() const
{
  std::stringstream s1, s2, s3, s4, s5, s6, s7;
  std::string xmlstr = get_xml_head();
  xmlstr += get_DTD_str();
  xmlstr += get_first_level_open_tag("activity");
  s1 << id;
  xmlstr += get_second_level_object("id", s1.str());
  xmlstr += get_second_level_object("name", name);
  xmlstr += get_second_level_object("description", description);
  xmlstr += get_second_level_object("number", number);
  if(is_finished())
    xmlstr += get_second_level_object("finished", "1");
  else
    xmlstr += get_second_level_object("finished", "0");
  s2 << get_start_year();
  xmlstr += get_second_level_object("start_year", s2.str());
  s3 << get_start_month();
  xmlstr += get_second_level_object("start_month", s3.str());
  s4 << get_start_day();
  xmlstr += get_second_level_object("start_day", s4.str());
  s5 << get_end_year();
  xmlstr += get_second_level_object("end_year", s5.str());
  s6 << get_end_month();
  xmlstr += get_second_level_object("end_month", s6.str());
  s7 << get_end_day();
  xmlstr += get_second_level_object("end_day", s7.str());
  xmlstr += get_first_level_close_tag("activity");
  return xmlstr;
}

time_t Activity::get_id() const
{
  return id;
}

bool Activity::is_milestone() const
{
  if((get_start_year() == get_end_year()) &&
     (get_start_month() == get_end_month()) &&
     (get_start_day() == get_end_day()))
    return true;
  else
    return false;
}

std::string Activity::get_DTD_str() const
{
  std::string xmlstr = "<!DOCTYPE activity [";
  xmlstr += "\n\t<!ELEMENT activity (id, name, description, number, finished, start_year, start_month, start_day, end_year, end_month, end_day)>";
  xmlstr += "\n\t<!ELEMENT id\t\t(#PCDATA)>";
  xmlstr += "\n\t<!ELEMENT name\t\t(#PCDATA)>";
  xmlstr += "\n\t<!ELEMENT description\t(#PCDATA)>";
  xmlstr += "\n\t<!ELEMENT number\t(#PCDATA)>";
  xmlstr += "\n\t<!ELEMENT finished\t(#PCDATA)>";
  xmlstr += "\n\t<!ELEMENT start_year\t(#PCDATA)>";
  xmlstr += "\n\t<!ELEMENT start_month\t(#PCDATA)>";
  xmlstr += "\n\t<!ELEMENT start_day\t(#PCDATA)>";
  xmlstr += "\n\t<!ELEMENT end_year\t(#PCDATA)>";
  xmlstr += "\n\t<!ELEMENT end_month\t(#PCDATA)>";
  xmlstr += "\n\t<!ELEMENT end_day\t(#PCDATA)>";
  xmlstr += "\n]>\n";
  return xmlstr;
}
