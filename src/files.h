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
#include "saveobj.h"
#include <string>
#include <list>

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
 */
int save_object_to_db(Saveobj *obj);

/* Function gets all staff objects saved 
 * to databse.
 * A list containing all staff obejcts in database
 * is returned.
 */
std::list<Staff> get_staff_from_db();

/* Function gets all project objects saved 
 * to databse.
 * A list containing all project obejcts in database
 * is returned.
 */
std::list<Project> get_projects_from_db();

#endif

