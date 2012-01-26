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

#include "project.h"
#include <ctime>

Project::Project(time_t project_id, std::string project_no, std::string project_name,
		 std::string description, std::string project_leader_name, 
		 std::string project_leader_surname, std::string project_leader_initials,
		 int start_year, int start_month, int start_day, 
		 int end_year, int end_month, int end_day)
  : Date(start_year, start_month, strat_day, end_year, end_month, end_day),
    project_id(project_id), project_no(project_no), project_name(project_name),
    description(description), project_leader_name(project_leader_name),
    project_leader_surname(project_leader_surname), project_leader_initials(project_leader_initials)
{}

Project::Project(std::string project_no, std::string project_name,
		 std::string description, std::string project_leader_name,
		 std::string project_leader_surname, std::string project_leader_initlials,
		 int start_year, int start_month, int start_day,
		 int end_year, int end_month, int end_day)
  : Date(start_year, start_month, start_day, end_year, end_month, end_day),
    project_no(project_no), project_name(project_name),
    description(description), project_leader_name(project_leader_name),
    project_leader_surname(project_leader_surname), project_leader_initials(project_leader_initials)
{
  time_t t;
  time(&t);
  project_id = t;
}

Project::Project(time_t project_id, std::string project_no, std::string project_name,
		 std::string description, std::string project_leader_name,
		 std::string project_leader_surname, std::string project
