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

#include "xmlstr.h"

std::string get_xml_head()
{
  return "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
}

std::string get_first_level_open_tag(std::string head)
{
  return "<" + head + ">\n";
}

std::string get_first_level_close_tag(std::string tail)
{
  return "</" + tail + ">\n";
}

std::string get_second_level_object(std::string tag, std::string content)
{
  return "\t<" + tag + ">" + content + "</" + tag + ">\n";
}
