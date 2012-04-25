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

#ifndef PROJECT_H
#define PROJECT_H

#include "../saveobj.h"
#include "../date.h"
#include "../staff/staff.h"
#include "activity.h"
#include <string>
#include <list>

/* Project class contains the main
 * information about the project, 
 * such as description, projectname
 * projectnumber aso.
 * Lists with all activities and
 * milestones is included in object.
 */
class Project : public Saveobj, public Date
{
 public:
  /* Sort order for activities, to use with sort_activities method. */
  enum sort_order {start_date_sort, end_date_sort, alpha_name_sort, alpha_name_reverse_sort};
  /* Constructors for Project.
   * Default project id is time now in seconds
   * from the epoq.
   * Defalut values for strings it the empty string.
   */
  Project(time_t project_id, std::string project_no, std::string project_name,
	  std::string description, std::string project_leader_name, 
	  std::string project_leader_surname, std::string project_leader_initials, 
	  int start_year, int start_month, int start_day,
	  int end_year, int end_month, int end_day);

  Project(time_t project_id, std::string project_no, std::string project_name,
	  std::string description, Staff project_leader, 
	  int start_year, int start_month, int start_day,
	  int end_year, int end_month, int end_day);

  Project(std::string project_no, std::string project_name,
	  std::string description, std::string project_leader_name, 
	  std::string project_leader_surname, std::string project_leader_initials, 
	  int start_year, int start_month, int start_day,
	  int end_year, int end_month, int end_day);

  Project(std::string project_no, std::string project_name,
	  std::string description, Staff project_leader,
	  int start_year, int start_month, int start_day,
	  int end_year, int end_month, int end_day);

  Project(time_t project_id, std::string project_no, std::string project_name,
	  std::string description, std::string project_leader_name, 
	  std::string project_leader_surname, std::string project_leader_initials, 
	  std::string start_date, std::string end_date);

  Project(time_t project_id, std::string project_no, std::string project_name,
	  std::string description, Staff project_leader,
	  std::string start_date, std::string end_date);

  Project(std::string project_no, std::string project_name,
	  std::string description, std::string project_leader_name, 
	  std::string project_leader_surname, std::string project_leader_initials, 
	  std::string end_date);

  Project(std::string project_no, std::string project_name,
	  std::string description, Staff project_leader,
	  std::string end_date);

  Project(std::string project_no, std::string project_name, std::string description,
	  int start_year, int start_month, int start_day,
	  int end_year, int end_month, int end_day);

  Project(std::string project_no, std::string project_name, std::string description,
	  std::string start_date, std::string end_date);

  Project(std::string project_no, std::string project_name, std::string description,
	  Staff project_leader, std::string start_date, std::string end_date);

  Project(std::string project_no, std::string project_name, std::string description,
	  Staff project_leader, int working_days_per_week, int working_hours_per_day,
	  std::string start_date, std::string end_date);

  Project(std::string project_no, std::string project_name,
	  std::string description, std::string project_leader_name, 
	  std::string project_leader_surname, std::string project_leader_initials);

  Project(std::string project_no, std::string project_name,
	  std::string description, Staff project_leader);

  Project(std::string project_no, std::string project_name, std::string description);

  /* Creates an instance of Project
   * with properies from xml string.
   * If assumed tags are missing
   * variables will be initiated
   * to default values.
   */
  Project(std::string xmlstring);

  /* Methods to get values
   * from object.
   */
  std::string get_project_no() const;
  std::string get_project_name() const;
  std::string get_description() const;
  Staff get_project_leader() const;
  std::string get_project_leader_name() const;
  std::string get_project_leader_surname() const;
  std::string get_project_leader_initials() const;
  int get_working_days_per_week() const;
  int get_working_hours_per_day() const;
  int get_total_working_days() const;
  int get_total_working_hours() const;
  std::list<Activity> get_activities() const;

  /* Generates and sets a new id
   * for project.
   * Use when another project
   * has the same id.
   * New id is returned.
   */
  time_t generate_new_id();

  /* Returns Activity with specified id number.
   * If Activity is not found a new activity
   * is returned with a different id.
   */
  Activity get_activity(time_t activity_id);

  /* Methods to change properties
   * of the object.
   */
  void set_project_id(time_t proj);
  void set_project_no(std::string no);
  void set_project_name(std::string name);
  void set_description(std::string desc);
  void set_project_leader(Staff leader);
  void set_project_leader_name(std::string name);
  void set_project_leader_surname(std::string surname);
  void set_project_leader_initials(std::string init);
  void set_working_days_per_week(int days);
  void set_working_hours_per_day(int hours);

  /* Replacing all existing activities
   * with attribute list.
   */
  void set_activities(std::list<Activity> acts, bool save_to_db=true);
  void add_activity(Activity act, bool save_to_db=true);

  /* Returns 1 if Activity removed, else -1 */
  int remove_activity(time_t activity_id);

  /* Use enum type defined in class. */
  void sort_order_activities(Project::sort_order s);

  /* Inhereted method from Saveobj. */
  std::string get_obj_xml_str() const;

  /* Inhereted method from Saveobj. */
  time_t get_id() const;

 private:
  /* Sort activities acording 
   * to variable sort_activities
   */
  void sort();

  time_t project_id;
  std::string project_no;
  std::string project_name;
  std::string description;
  Staff project_leader;
  int working_days_per_week;
  int working_hours_per_day;
  std::list<Activity> activities;
  Project::sort_order sort_activities;

  /* Inhereted method from Saveobj. */
  std::string get_DTD_str() const;
};

/* For sorting activity list in Project.
 * Returns true if a>=b.
 */
bool activities_sort_start_date_order(Activity a, Activity b);
bool activities_sort_end_date_order(Activity a, Activity b);
bool activities_sort_name_order(Activity a, Activity b);
bool activities_sort_reverse_name_order(Activity a, Activity b);

#endif
