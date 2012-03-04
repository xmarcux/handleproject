
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

#include "files.h"

#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <fstream>
#include <cstdio>
#include <cerrno>
#include <ctime>
#include <cstring>
#include <typeinfo>
#include <string>
#include <sstream>

using namespace std;

const char *dbpath = "haprdb";
const char *projpath = "haprdb/projects";
const char *staffpath = "haprdb/staff";
const char *errfile = "error";

void initdb()
{
  struct stat state_db;
  mode_t dir_mode = S_IRWXU | S_IRWXG | S_IRWXO;

  if(stat(dbpath, &state_db) == -1)
  {
    if(mkdir(dbpath, dir_mode) != 0)
    {
      new_error(string("Could not create dir: ").append(dbpath), "files.cpp", "initdb()");
    }
    else
    {
      if(mkdir(projpath, dir_mode) != 0)
      {
	new_error(string("Could not create dir: ").append(projpath), "files.cpp", "initdb()");
      }
      if(mkdir(staffpath, dir_mode) != 0)
      {
	new_error(string("Could not create dir: ").append(staffpath), "files.cpp", "initdb()");
      }
    }
  }
  else
  {
    if(stat(projpath, &state_db) == -1)
    {
      if(mkdir(projpath, dir_mode) != 0)
      {
	new_error(string("Could not create dir: ").append(projpath), "files.cpp", "initdb()");
      }
    }

    if(stat(staffpath, &state_db) == -1)
    {
      if(mkdir(staffpath, dir_mode) != 0)
      {
	new_error(string("Could not create dir: ").append(staffpath), "files.cpp", "initdb()");
      }
    }
  }
}


void new_error(string err_text, string in_file, string in_function)
{
  time_t rawtime;
  struct tm *timeinfo;

  time(&rawtime);
  timeinfo = localtime(&rawtime);

  string err_msg = asctime(timeinfo);
  err_msg = err_msg +  "\t" + in_file + " - " + in_function + "\t" + err_text; 

  fstream errstream;
  errstream.open(errfile, fstream::out | fstream::app);
  errstream << err_msg << endl << endl;
  errstream.close();
}


int save_object_to_db(Saveobj *obj)
{
  string filepath;
  fstream filestream;
  if(typeid(*obj) == typeid(Staff))
  {
    stringstream ss;
    ss << obj->get_id();
    filepath = staffpath;
    filepath += "/" + ss.str() + ".staff";
    filestream.open(filepath.c_str(), fstream::out);
    filestream << obj->get_obj_xml_str();
  }
  if(typeid(*obj) == typeid(Project))
  {
    stringstream ss;
    ss << obj->get_id();
    filepath = projpath;
    filepath += "/" + ss.str() + ".project";
    filestream.open(filepath.c_str(), fstream::out);
    filestream << obj->get_obj_xml_str();
  }
  filestream.flush();
  filestream.close();
  if(filestream.fail())
  {
    return -1;
  }
  return 1;
}

int delete_object_from_db(Saveobj *obj)
{
  string filepath;
  ifstream ifilestream;
  if(typeid(*obj) == typeid(Staff))
  {
    stringstream ss, serr;
    ss << obj->get_id();
    filepath = staffpath;
    filepath += "/" + ss.str() + ".staff";
    ifilestream.open(filepath.c_str());
    if(ifilestream.is_open())
    {
      ifilestream.close();
      if(remove(filepath.c_str()) != 0)
      {
	serr << errno;
	new_error("Errorno: " + serr.str() + " ,Can not delete Staff object.", 
		  "files.cpp", "delete_object_from_db");
	return -1;
      }
      else
	return 1;
    }
    else
      return 0;
  }
  if(typeid(&obj) == typeid(Project))
  {
    stringstream ss, serr;
    ss << obj->get_id();
    filepath = projpath;
    filepath += "/" + ss.str() + ".project";
    ifilestream.open(filepath.c_str());
    if(ifilestream.is_open())
    {
      ifilestream.close();
      if(remove(filepath.c_str()) != 0)
      {
	serr << errno;
	new_error("Errorno: " + serr.str() + " , Can not delete Project object", 
		  "files.cpp", "delete_object_from_db");
	return -1;
      }
      else
	return 1;
    }
    else
      return 0;
  }
  return 0;
}

int save_activity_to_db(Activity *act, size_t project_no)
{
  fstream filestream;
  stringstream ss, ss2;
  string filepath;
  filepath = projpath;
  ss << project_no;
  ss2 << act->get_id();
  filepath += "/" + ss2.str() + "_" + ss.str() + ".activity";
  filestream.open(filepath.c_str(), fstream::out);
  filestream << act->get_obj_xml_str();
  filestream.flush();
  filestream.close();
  if(filestream.fail())
    return -1;
  return 1;
}

int delete_activity_from_db(Activity *act, size_t project_no)
{
  ifstream ifile;
  string filepath;
  stringstream ss, ss2, serr;
  filepath = projpath;
  ss << act->get_id();
  ss2 << project_no;
  filepath += "/" + ss.str() + "_" + ss2.str() + ".activity";
  ifile.open(filepath.c_str(), ifstream::in);
  if(ifile.is_open())
  {
    ifile.close();
    if(remove(filepath.c_str()) != 0)
    {
      serr << errno;
      new_error("Error no: " + serr.str() + "Can not delete Activity object file",
		"files.cpp", "delete_activity_from_db");
      return -1;
    }
    else
      return 1;
  }
  return 0;
}

list<Activity> get_activities_from_db(size_t project_no)
{
  list<Activity> lact;
  string filename;
  fstream filestream;
  DIR *dp;
  struct dirent *dirp;
  stringstream ss;
  ss << project_no;
  filename = ss.str() + ".activity";

  if((dp = opendir(projpath)) == NULL)
  {
    new_error("Could not open dir: " + string(projpath), "files.cpp",
	      "list<Activity> get_activities_from_db()");
  }
  else
  {
    while((dirp = readdir(dp)) != NULL)
    {
      if(strstr(dirp->d_name, filename.c_str()) != NULL)
      {
	int length;
	char *buffer;
	string filepath = string(projpath) + "/" + string(dirp->d_name);
	filestream.open(filepath.c_str(), fstream::in);
	filestream.seekg(0, ios::end);
	length = filestream.tellg();
	filestream.seekg(0, ios::beg);
	buffer = new char[length];
	filestream.read(buffer, length);
	filestream.close();
	lact.push_back(Activity(string(buffer)));
      }
    }
    closedir(dp); 
  }
  return lact;
}

list<Staff> get_staff_from_db()
{
  list<Staff> staffl;
  fstream filestream;
  DIR *dp;
  struct dirent *dirp;

  if((dp = opendir(staffpath)) == NULL)
  {
    new_error("Could not open dir:" + string(staffpath), "files.cpp", 
	      "list<Staff> get_staff_from_db()");
  }
  else
  {
    while((dirp = readdir(dp)) != NULL)
    {
      if(strcmp(".", dirp->d_name) != 0 && strcmp("..", dirp->d_name) != 0)
      {
        int length;
        char *buffer;
        string filepath = string(staffpath) + "/" + string(dirp->d_name);
        filestream.open(filepath.c_str(), fstream::in);
        filestream.seekg(0, ios::end);
        length = filestream.tellg();
        filestream.seekg(0, ios::beg);
        buffer = new char[length];
        filestream.read(buffer, length);
        filestream.close();
        staffl.push_back(Staff(string(buffer)));
      }
    }
    closedir(dp);
  }
  return staffl;
}

Project get_project_from_db(size_t project_no)
{
  Project proj("");
  fstream filestream;
  int length;
  char *buffer;
  stringstream ss;
  string filepath = projpath;
  ss << project_no;
  filepath += "/" + ss.str() + ".project";
  filestream.open(filepath.c_str(), fstream::in);
  if(filestream.is_open())
  {
    filestream.seekg(0, ios::end);
    length = filestream.tellg();
    filestream.seekg(0, ios::beg);
    buffer = new char[length];
    filestream.read(buffer, length);
    filestream.close();
    proj = Project(string(buffer));
    proj.set_activities(get_activities_from_db(project_no));
  }
  return proj;
}

list<Project> get_projects_from_db()
{
  list<Project> projl;
  fstream filestream;
  DIR *dp;
  struct dirent *dirp;

  if((dp = opendir(projpath)) == NULL)
  {
    new_error("Could not open dir:" + string(projpath), "files.cpp", 
	      "list<Project> get_projects_from_db()");
  }
  else
  {
    while((dirp = readdir(dp)) != NULL)
    {
      if(strcmp(".", dirp->d_name) != 0 && strcmp("..", dirp->d_name) != 0)
      {
        int length;
        char *buffer;
        string filepath = string(projpath) + "/" + string(dirp->d_name);
        filestream.open(filepath.c_str(), fstream::in);
        filestream.seekg(0, ios::end);
        length = filestream.tellg();
        filestream.seekg(0, ios::beg);
        buffer = new char[length];
        filestream.read(buffer, length);
        filestream.close();
        projl.push_back(Project(string(buffer)));
      }
    }
    closedir(dp);
  }
  return projl;
}
