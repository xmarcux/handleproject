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

#ifndef SAVEOBJ_H
#define SAVEOBJ_H

#include <string>

/* Saveobj should be subclassed
 * by classes that is going to be saved.
 * Will force classes to implement functions
 * needed for saving.
 */

class Saveobj
{
 public:
  /* All classes should create a complete
   * xml string containing all variables
   * in the object. This string will be
   * used for saving object to file.
   */
  virtual std::string get_obj_xml_str() const  = 0;

 private:
  /* All classes should create a 
   * unique DTD string to be used 
   * when the xml string is created.
   * Example DTD:
   * <!DOCTYPE obj [
   *   <!ELEMENT obj (child1, child2)>
   *   <!ELEMENT child1    (#CDATA)>
   *   <!ELEMENT child2    (#CDATA)>
   * ]>
   */
  virtual std::string get_DTD_str() const = 0;
};

#endif
