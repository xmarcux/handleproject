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

#ifndef XMLSTR_H
#define XMLSTR_H

#include <string>

/* Returns the xml header 
 * with version tag, ends 
 * with newline.
 */
std::string get_xml_head();

/* Returns the open tag for the main object.
 * All other tags should be put inside of this tag.
 * When all other tags are written function
 * get_first_level_close_tag returns the closing tag
 * that "closes" this opening tag.
 * Ends with newline.
 */
std::string get_first_level_open_tag(std::string head);

/* Returns the closing tag and should be called after
 * get_first_level_open_tag and all other objects tags.
 * "Closes" the tag returned form function
 * get_first_level_open_tag.
 * Ends with newline.
 */
std::string get_first_level_close_tag(std::string tail);

/* Returns a string with both an opening and closing tag with
 * content inside.
 * Is moved in with a tab.
 * Ends with a newline.
 */
std::string get_second_level_object(std::string tag, std::string content);

#endif
