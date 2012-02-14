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

#ifndef ACTIVITY_H
#define ACTIVITY_H

#include "../saveobj.h"
#include "../date.h"
#include "../xmlstr.h"

#include <string>

class Activity : public Saveobj, public Date
{
 public:
  /* Constructors for Activity
   * Default activity id is time now in seconds
   * from the epoq.
   * Default values for strings is the empty string.
   */
  Activity();
  Activity(time_t id, std::string name, std::string description, std::string number);
  Activity(time_t id, std::string name, std::string description, std::string number,
	   int start_year, int start_month, int start_day,
	   int end_year, int end_month, int end_day);
  Activity(time_t id, std::string name, std::string description, std::string number, 
	   std::string start_date, std::string end_date);
  Activity(time_t id, std::string name, std::string description);
  Activity(time_t id, std::string name, std::string description,
	   int start_year, int start_month, int start_day,
	   int end_year, int end_month, int end_day);
  Activity(time_t id, std::string name, std::string description,
	   std::string start_date, std::string end_date);
  Activity(std::string name, std::string description, std::string number); 
  Activity(std::string name, std::string description, std::string number,
	   int start_year, int start_month, int start_day,
	   int end_year, int end_month, int end_day); 
  Activity(std::string name, std::string description, std::string number,
	   std::string start_date, std::string end_date); 
  Activity(std::string name, std::string description);
  Activity(std::string name, std::string description,
	   int start_year, int start_month, int start_day,
	   int end_year, int end_month, int end_day);
  Activity(std::string name, std::string description,
	   std::string start_date, std::string end_date);

  /* Creates an instance of Activity
   * with properies from xml string.
   * If assumed tags are missing
   * variables will be initiated
   * to default values.
   */
  Activity(std::string xmlstring);

  /* Methods to get values 
   * from object.
   */
  std::string get_number() const;
  std::string get_name() const;
  std::string get_description() const;

  /* Methods to change properties
   * of the object.
   */
  void set_id(time_t id);
  void set_number(std::string no);
  void set_name(std::string name);
  void set_description(std::string desc);

  /* Inhereted method from Saveobj. */
  std::string get_obj_xml_str() const;

  /* Inhereted method from Saveobj. */
  time_t get_id() const;

  /* If start and end date
   * is identical, equal,
   * then activity is a milestone.
   */
  bool is_milestone() const;

 private:
  time_t id;
  std::string name;
  std::string description;
  std::string number;

  /* Inhereted method from Saveobj. */
  std::string get_DTD_str() const;
};

#endif
