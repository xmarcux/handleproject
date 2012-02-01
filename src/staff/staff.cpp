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

#include "staff.h"
#include "../xmlstr.h"
#include <sstream>

Staff::Staff(std::string name, std::string surname, std::string profession, 
	     double week_hours)
  : name(name), surname(surname), profession(profession)
{
  if(week_hours > -1)
  {
    week_working_hours = week_hours;
  }
  else
  {
    week_working_hours = 40.0;
  }
  day_working_hours = 8.0;
  working_days_per_week = 5.0;
  time(&id);
  
  std::string in = "";
  if(name.size() >=1)
  {
    in = name.substr(0, 1);
  }
  if(surname.size() >= 1)
  {
    in += surname.substr(0, 1);
  }
  initials = in;
}

Staff::Staff(std::string name, std::string surname, std::string initials,
	     std::string profession, double day_hours, double days_per_week)
  : name(name), surname(surname), initials(initials), profession(profession)
{
  if(day_hours > -1)
  {
      day_working_hours = day_hours;
  }
  else
  {
    day_working_hours = 8.0;
  }

  if(days_per_week > -1)
  {
    working_days_per_week = days_per_week;
  }
  else
  {
    working_days_per_week = 5.0;
  }

  if(day_working_hours > 0 && working_days_per_week > 0)
  {
    week_working_hours = day_working_hours * working_days_per_week;
  }
  else
  {
    week_working_hours = 40.0;
  }
  time(&id);
}

Staff::Staff(std::string name, std::string surname, std::string initials, std::string profession)
  : name(name), surname(surname), initials(initials), profession(profession)
{
  week_working_hours = 40.0;
  day_working_hours = 8.0;
  working_days_per_week = 5.0;
  time(&id);
}

Staff::Staff(std::string name, std::string surname, std::string profession)
  : name(name), surname(surname), profession(profession)
{
  week_working_hours = 40.0;
  day_working_hours = 8.0;
  working_days_per_week = 5.0;
  time(&id);

  std::string in = "";
  if(name.size() >=1)
  {
    in = name.substr(0, 1);
  }
  if(surname.size() >= 1)
  {
    in += surname.substr(0, 1);
  }
  initials = in;
}

Staff::Staff(std::string name, std::string surname)
  : name(name), surname(surname)
{
  week_working_hours = 40.0;
  day_working_hours = 8.0;
  working_days_per_week = 5.0;
  profession = "";
  time(&id);

  std::string in = "";
  if(name.size() >=1)
  {
    in = name.substr(0, 1);
  }
  if(surname.size() >= 1)
  {
    in += surname.substr(0, 1);
  }
  initials = in;
}

Staff::Staff(std::string xmlstring)
{
  size_t found1, found2;
  found1 = xmlstring.find("<staff>");
  found2 = xmlstring.find("</staff>");
  if(found1 != std::string::npos && found2 != std::string::npos)
  {
    found1 = std::string::npos;
    found2 = std::string::npos;
    found1 = xmlstring.find("<id>");
    found2 = xmlstring.find("</id>");
    if(found1 != std::string::npos && found2 != std::string::npos)
    {
      std::string idstr  = xmlstring.substr(found1 + 4, found2 - found1 - 4);
      std::stringstream ss;
      ss << idstr;
      ss >> id;
      if(ss.fail())
      {
	time(&id);
      }
    }
    else
      time(&id);
  
    found1 = std::string::npos;
    found2 = std::string::npos;
    found1 = xmlstring.find("<name>");
    found2 = xmlstring.find("</name>");
    if(found1 != std::string::npos && found2 != std::string::npos)
    {
      name = xmlstring.substr(found1 + 6, found2 - found1 - 6);
    }
    else
      name = "";

    found1 = std::string::npos;
    found2 = std::string::npos;
    found1 = xmlstring.find("<surname>");
    found2 = xmlstring.find("</surname>");
    if(found1 != std::string::npos && found2 != std::string::npos)
    {
      surname = xmlstring.substr(found1 + 9, found2 - found1 - 9);
    }
    else
      surname = "";

    found1 = std::string::npos;
    found2 = std::string::npos;
    found1 = xmlstring.find("<initials>");
    found2 = xmlstring.find("</initials>");
    if(found1 != std::string::npos && found2 != std::string::npos)
    {
      initials = xmlstring.substr(found1 + 10, found2 - found1 - 10);
    }
    else
    {
      initials = "";
      if(name.size() >= 1)
      {
	initials = name.substr(0, 1);
      }
      if(surname.size() >= 1)
      {
	initials += surname.substr(0, 1);
      }
    } 

    found1 = std::string::npos;
    found2 = std::string::npos;
    found1 = xmlstring.find("<profession>");
    found2 = xmlstring.find("</profession>");
    if(found1 != std::string::npos && found2 != std::string::npos)
    {
      profession = xmlstring.substr(found1 + 12, found2 - found1 - 12);
    }
    else
      profession = "";

    found1 = std::string::npos;
    found2 = std::string::npos;
    found1 = xmlstring.find("<week_hours>");
    found2 = xmlstring.find("</week_hours>");
    if(found1 != std::string::npos && found2 != std::string::npos)
    {
      std::stringstream ss;
      ss << xmlstring.substr(found1 + 12, found2 - found1 - 12);
      ss >> week_working_hours;
      if(ss.fail())
      {
	week_working_hours = 40.0;
      }
    }
    else
      week_working_hours = 40.0;

    found1 = std::string::npos;
    found2 = std::string::npos;
    found1 = xmlstring.find("<day_hours>");
    found2 = xmlstring.find("</day_hours>");
    if(found1 != std::string::npos && found2 != std::string::npos)
    {
      std::stringstream ss;
      ss << xmlstring.substr(found1 + 11, found2 - found1 - 11);
      ss >> day_working_hours;
      if(ss.fail())
      {
	day_working_hours = 8.0;
      }
    }
    else
      day_working_hours = 8.0;

    found1 = std::string::npos;
    found2 = std::string::npos;
    found1 = xmlstring.find("<days_per_week>");
    found2 = xmlstring.find("</days_per_week>");
    if(found1 != std::string::npos && found2 != std::string::npos)
    {
      std::stringstream ss;
      ss << xmlstring.substr(found1 + 15, found2 - found1 - 15);
      ss >> working_days_per_week;
      if(ss.fail())
      {
	working_days_per_week = 5.0;
      }
    }
    else
      working_days_per_week = 5.0;
  }
  else
  {
    time(&id);
    name = "";
    surname = "";
    profession = "";
    week_working_hours = 40.0;
    day_working_hours = 8.0;
    working_days_per_week = 5.0;
  }
}

time_t Staff::get_id() const
{
  return id;
}

std::string Staff::get_name() const
{
  return name;
}

std::string Staff::get_surname() const
{
  return surname;
}

std::string Staff::get_initials() const
{
  return initials;
}

std::string Staff::get_profession() const
{
  return profession;
}

double Staff::get_week_working_hours() const
{
  return week_working_hours;
}

double Staff::get_day_working_hours() const
{
  return day_working_hours;
}

double Staff::get_working_days_per_week() const
{
  return working_days_per_week;
}

void Staff::set_id(time_t t)
{
  id = t;
}

void Staff::set_name(std::string n)
{
  name = n;
}

void Staff::set_surname(std::string sname)
{
  surname = sname;
}

void Staff::set_initials(std::string ini)
{
  initials = ini;
}

void Staff::set_profession(std::string prof)
{
  profession = prof;
}

void Staff::set_week_working_hours(double hours)
{
  if(hours > -1)
  {
    week_working_hours = hours;    
  }

  if(working_days_per_week > 0 && hours > 0)
  {
    day_working_hours = week_working_hours/working_days_per_week;
  }
}

void Staff::set_day_working_hours(double hours)
{
  if(hours > -1)
  {
    day_working_hours = hours;
  }

  if(working_days_per_week > 0 && hours > 0)
  {
    week_working_hours = working_days_per_week * day_working_hours;
  }
}

void Staff::set_working_days_per_week(double days)
{
  if(days > -1)
  {
    working_days_per_week = days;
  }

  if(day_working_hours > 0 && days > 0)
  {
    week_working_hours = day_working_hours * working_days_per_week;
  }
}

std::string Staff::get_obj_xml_str() const
{
  std::string xmlstr = get_xml_head();
  std::ostringstream sstream, sstream2, sstream3, sstream4;
  xmlstr += get_DTD_str();
  xmlstr += get_first_level_open_tag("staff");
  sstream << id;
  xmlstr += get_second_level_object("id",sstream.str());
  xmlstr += get_second_level_object("name",name);
  xmlstr += get_second_level_object("surname",surname);
  xmlstr += get_second_level_object("initials",initials);
  xmlstr += get_second_level_object("profession",profession);
  sstream2 << week_working_hours;
  xmlstr += get_second_level_object("week_hours",sstream2.str());
  sstream3 << day_working_hours;
  xmlstr += get_second_level_object("day_hours",sstream3.str());
  sstream4 << working_days_per_week;
  xmlstr += get_second_level_object("days_per_week",sstream4.str());
  xmlstr += get_first_level_close_tag("staff");
  return xmlstr;
}

std::string Staff::get_DTD_str() const
{
  std::string dtdstr = "<!DOCTYPE staff [";
  dtdstr += "\n\t<!ELEMENT staff (id, name, surname, initials, profession, week_hours, day_hours, days_per_week)>";
  dtdstr += "\n\t<!ELEMENT id\t\t(#PCDATA)>";
  dtdstr += "\n\t<!ELEMENT name\t\t(#PCDATA)>";
  dtdstr += "\n\t<!ELEMENT surname\t(#PCDATA)>";
  dtdstr += "\n\t<!ELEMENT initials\t(#PCDATA)>";
  dtdstr += "\n\t<!ELEMENT profession\t(#PCDATA)>";
  dtdstr += "\n\t<!ELEMENT week_hours\t(#PCDATA)>";
  dtdstr += "\n\t<!ELEMENT day_hours\t(#PCDATA)>";
  dtdstr += "\n\t<!ELEMENT days_per_week\t(#PCDATA)>";
  dtdstr += "\n]>\n";
  return dtdstr;
}
