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

#ifndef JOB_H
#define JOB_H

#include "../saveobj.h"
#include <string>
#include <ctime>

/* Job class represent a job connected
 * to a Staff object where the job
 * is a specific task with a start and
 * end date and a specific hour of 
 * work per day.
 * Job is also connected with a 
 * specific project.
 */
class Job : public Saveobj
{
 public:

  /* Constructors for Job
   * with different number of
   * variables.
   * Default working hours per day 
   * is 8 hours.
   * Default start and end date
   * is today, the day the object was created.
   * Default project id is -1, invalid project,
   * which means it does not belong to a project.
   */
  Job(time_t staff_id, std::string description, time_t project_id,
      int start_year, int start_month, int start_day, 
      int end_year, int end_month, int end_day, int hours_per_day);
  
  /* Start and end date is string attributes
   * and should have a format with the minimum year 1900.
   * Four formats are supported: 
   * YYYY-MM-DD
   * YY-MM-DD (where year is assumed to be equal or larger then 2000.)
   * MM/DD/YYYY
   * MM/DD/YY (where year is assumed to be equal or larger then 2000.)
   * If the format is not right start and stop date 
   * will be initialized to today.
   */
  Job(time_t staff_id, std::string description, time_t project_id,
      std::string start_date, std::string end_date);

  /* Usable when job should not be connected to a project.
   * Project id initialized to -1.
   */
  Job(time_t staff_id, std::string description, 
      int start_year, int start_month, int start_day, 
      int end_year, int end_month, int end_day, int hours_per_day);

  /* Usable when job should not be connected to a project.
   * Project id initialized to -1.
   * Start and end date is string attributes
   * and should have a format with the minimum year 1900.
   * Four formats are supported: 
   * YYYY-MM-DD
   * YY-MM-DD (where year is assumed to be equal or larger then 2000.)
   * MM/DD/YYYY
   * MM/DD/YY (where year is assumed to be equal or larger then 2000.)
   * If the format is not right start and stop date 
   * will be initialized to today.
   */
  Job(time_t staff_id, std::string description,
      std::string start_date, std::string end_date);

  /* Start and end time will be initialized to today.*/
  Job(time_t staff_id, std::string desription);

  /* Creates an instance of Job
   * with properies from xml string.
   * If assumed tags are missing
   * variables will be initiated
   * to default values.
   */
  Job(std::string xmlstring);

  /* Methods to get information
   * out of object.
   */
  time_t get_staff_id() const;
  time_t get_project_id() const;
  std::string get_description() const;

  /* Returns a string in format: YYYY-MM-DD */
  std::string get_start_date_str_eu() const;

  /* Returns a string in format: MM/DD/YYYY */
  std::string get_start_date_str_us() const;

  /* Returns a string in format: YYYY-MM-DD */
  std::string get_end_date_str_eu() const;

  /* Returns a string in format: MM/DD/YYYY */
  std::string get_end_date_str_us() const;
  int get_start_year() const;
  int get_end_year() const;
  int get_start_month() const;
  int get_end_month() const;
  int get_start_day() const;
  int get_end_day() const;
  int get_hours_per_day() const;
  bool get_finished() const;
  

  /*Set variables in object */
  void set_staff_id(time_t staff_id);
  void set_project_id(time_t project_id);
  void set_description(std::string desc);
  void set_start_date(std::string start_date);
  void set_end_date(std::string end_date);
  void set_start_year(int year);
  void set_end_year(int year);
  void set_start_month(int month);
  void set_end_month(int month);
  void set_start_day(int day);
  void set_end_day(int day);
  void set_hours_per_day(int hours);
  void set_finished(bool f);
  void set_id(time_t id);

  /* Depending on how many working days
   * per week that the Staff has the
   * total working hours can be calculated.
   * If invalid value in attribute or
   * if value can not be calculated -1 is returned.
   */
  int total_working_hours(int days_per_week);

  /* Depending on how many working days
   * per week that the Staff has the
   * total working days can be calculated.
   * If invalid value in attribute or
   * if value can not be calculated -1 is returned.
   */
  int total_working_days(int days_per_week);

  /* Inherited methods */
  std::string get_obj_xml_str() const;
  time_t get_id() const;

 private:
  time_t staff_id;
  std::string description;
  time_t project_id;
  int start_year;
  int start_month;
  int start_day;
  int end_year;
  int end_month;
  int end_day;
  int hours_per_day;
  bool finished;
  time_t id;

  /* Converts a date string to three integers,
   * where first pointer is the year, second
   * pointer is the month and third pointer
   * is the day of month.
   * If any value in string is invalid that
   * integer will be set to -1.
   */

  int *  date_str_to_int(std::string date_string);
  int *  date_str_to_int_us(std::string date_string);

  /* Inherited method */
  std::string get_DTD_str() const;
};

#endif
