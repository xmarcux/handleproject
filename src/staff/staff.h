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

#ifndef STAFF_H
#define STAFF_H

#include "../saveobj.h"
#include <string>
#include <ctime>

/* Staff class represent an employee
 * with properties like name, surname annd profession.
 * Objects of this class is supposed to be 
 * included in projects where they are asigned time
 * to be processed in the project.
 * Functionality to be able to see if an
 * employee has the right working hours per week
 * or if the person has to much time ie. overtime.
 */
class Staff : public Saveobj
{
 public:
  /* Constructors for Staff
   * with differient number of
   * variables.
   * Default  working hours per week is 40 hours.
   * Default days to work per week is 5.
   * Default working hours per day is 8 hours.
   */
  Staff(std::string name, std::string surname, std::string profession, 
	double week_hours);

  /* If day_hours and days_per_week
   * is greater then zero week_working_hours
   * will be calculated.
   */
  Staff(std::string name, std::string surname, std::string profession,
	double day_hours, double days_per_week);
  Staff(std::string name, std::string surname, std::string profession);
  Staff(std::string name, std::string surname);

  /* Creates an instance of Staff
   * with properies from xml string.
   * If assumed tags are missing
   * variables will be initiated
   * to default values.
   */
  Staff(std::string xmlstring);
  
  /* Methods to get information
   * out of object.
   */
  time_t get_id() const;
  std::string get_name() const;
  std::string get_surname() const;
  std::string get_profession() const;
  double get_week_working_hours() const;
  double get_day_working_hours() const;
  double get_working_days_per_week() const;

  /* Set values in object */
  void set_id(time_t t);
  void set_name(std::string n);
  void set_surname(std::string sname);
  void set_profession(std::string prof);

  /* hours must be a positiv value.
   * If number of working days per week
   * is larger then zero working hours per
   * day will be updated.
   */
  void set_week_working_hours(double hours);

  /* hours must be a positiv value.
   * If number of working days per week
   * is larger then zero working hours per
   * week will be updated.
   */
  void set_day_working_hours(double hours);

  /* days must be a positiv value.
   * If number of working hours per day
   * is larger then zero working hours per
   * week will be updated.
   */
  void set_working_days_per_week(double days);


  std::string get_obj_xml_str() const;

 private:
  time_t id;
  std::string name;
  std::string surname;
  std::string profession;
  double week_working_hours;
  double day_working_hours;
  double working_days_per_week;

  std::string get_DTD_str() const;
};

#endif
