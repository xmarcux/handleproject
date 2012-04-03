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

#ifndef FILES_H
#define FILES_H

#include "staff/staff.h"
#include "project/project.h"
#include "project/activity.h"
#include "saveobj.h"
#include <string>
#include <list>

/* Enumeration to decide if to look in 
 * active projects or projects that are 
 * finished and moved to history.
 */
enum project_state {ACTIVE_PROJECT, HISTORY_PROJECT};

/* Functon initializes database if it does not
 * already exists. 
 * It creates directories needed for Handle Project.
 */
void initdb();

/* Writes errortext to error file.
 * Variable in_file is supposed to specify in 
 * which file that the function is called from
 * and in_function is supposed to specify in which
 * function or object the function is called from.
 * Current date and timestamp is added to file as well.
 */
void new_error(std::string err_text, std::string in_file, std::string in_function);

/* Function saves object as an xml-file to database.
 * All objects subclassing Saveobj will be able to be saved
 * to file, by using method get_obj_xml_str().
 * Returns a positive value on success and a negative value
 * on falure.
 * Only object itself is saved no subobjects.
 * Subobject saves need to be handled separately.
 */
int save_object_to_db(Saveobj *obj);

/* Function deletes saved object file
 * from database.
 * Returns a positive value on success,
 * a negative value on falure and zero
 * if file does not exist.
 */
int delete_object_from_db(Saveobj *obj, project_state state = ACTIVE_PROJECT);

/* Function saves activity as an xml-file to database.
 * project_no is the number of the project
 * that the activity belongs to.
 * Returns a positive value on success and a negative value
 * on falure.
 */
int save_activity_to_db(Activity *act, time_t project_no);

/* Function deletes saved activity file
 * from database.
 * project_no is the number of the project
 * that the activity belongs to.
 * Returns a positive value on success,
 * a negative value on falure and zero
 * if file does not exist.
 */
int delete_activity_from_db(Activity *act, time_t project_no, project_state state = ACTIVE_PROJECT);

/* Function takes project id as an argument.
 * A list containing all activities that
 * belongs to project is returned.
 */
std::list<Activity> get_activities_from_db(time_t project_no, project_state state = ACTIVE_PROJECT);

/* Function gets all staff objects saved 
 * to databse.
 * A list containing all staff obejcts in database
 * is returned.
 */
std::list<Staff> get_staff_from_db();

/* Function takes project id as an argument.
 * The complete project is read from file
 * including activities and is returned.
 */
Project get_project_from_db(size_t project_no, project_state state = ACTIVE_PROJECT);

/* Function gets all project objects saved 
 * to databse.
 * A list containing all project obejcts in database
 * is returned.
 */
std::list<Project> get_projects_from_db(project_state state = ACTIVE_PROJECT);

/* Function moves a project from active database
 * to history if state is an active project. 
 * This should be done when project is finished.
 * If state is history project then the project
 * will be moved back to active again.
 * Returns 1 on success or -1 on falure.
 */
int move_project_to_history(Project *proj, project_state state = ACTIVE_PROJECT);

#endif

