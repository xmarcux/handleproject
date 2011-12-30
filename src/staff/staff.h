/****************************************************************************
 *                                                                          *
 *    Handle Project, an application for managing projects and employees.   *
 *    Copyright (C) 2011  Marcus Pedersén marcux@handleproject.org          *
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

#ifndef STAFF_H
#define STAFF_H

#include "../saveobj.h"
#include <string>

class Staff : public Saveobj
{
 public:
  Staff(std::string name, std::string surname, std::string profession, 
	int week_working_hours);
  /*  Staff(std::string name, std::string surname, std::string profession);
  Staff(std::string name, std::string surname);
  Staff(std::string name, std::string profession);
  Staff(std::string name);

  get_name() const;
  get_surname() const;
  get_profession() const;
  get_week_working_hours() const;
  xml_str() const;

  set_name(std::string);
  set_surname(std::string);
  set_profession(std::string);
  set_week_working_hours(int hours);
  */
  std::string get_obj_xml_str();

 private:
  std::string name;
  std::string surname;
  std::string profession;
  int week_working_hours;

  std::string get_DTD_str();
};

#endif
