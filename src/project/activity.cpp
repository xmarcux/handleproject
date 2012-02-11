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

Activity::Activity(time_t id, std::string name, std::string description)
  : id(id), name(name), description(description)
{
  number = "";
}

Activity::Activity(std::string name, std::string description, std::string number)
  : name(name), description(description), number(number)
{
  time(&id);
}

Activity::Activity(std::string name, std::string description)
  : name(name), description(description)
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
  return "";
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

//fix method
std::string Activity::get_DTD_str() const
{
  return "";
}
