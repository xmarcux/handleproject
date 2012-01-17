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

#include "job.h"
#include "../xmlstr.h"
#include <sstream>
#include <cmath>

Job::Job(time_t staff_id, std::string description, time_t project_id,
	 int start_year, int start_month, int start_day,
	 int end_year, int end_month, int end_day, int hours_per_day)
  : staff_id(staff_id), description(description), project_id(project_id),
    start_year(start_year), start_month(start_month), start_day(start_day),
    end_year(end_year), end_month(end_month), end_day(end_day), hours_per_day(hours_per_day)
{
  finished = false;
  time(&id);
}

Job::Job(time_t staff_id, std::string description, time_t project_id,
	 std::string start_date, std::string end_date)
  : staff_id(staff_id), description(description), project_id(project_id)
{
  set_start_date(start_date);
  set_end_date(end_date);
  hours_per_day = 8;
  finished = false;
  time(&id);
}

Job::Job(time_t staff_id, std::string description,
	 int start_year, int start_month, int start_day,
	 int end_year, int end_month, int end_day, int hours_per_day)
  : staff_id(staff_id), description(description), 
    start_year(start_year), start_month(start_month), start_day(start_day),
    end_year(end_year), end_month(end_month), end_day(end_day), hours_per_day(hours_per_day)
{
  project_id = -1;
  finished = false;
  time(&id);
}

Job::Job(time_t staff_id, std::string description,
	 std::string start_date, std::string end_date)
  : staff_id(staff_id), description(description)
{
  set_start_date(start_date);
  set_end_date(end_date);
  project_id = -1;
  hours_per_day = 8;
  finished = false;
  time(&id);
}

Job::Job(time_t staff_id, std::string description)
  : staff_id(staff_id), description(description)
{
  time_t t = time(NULL);
  struct tm *today;
  today = localtime(&t);
  start_year = today->tm_year + 1900;
  end_year = today->tm_year + 1900;
  start_month = today->tm_mon + 1;
  end_month = today->tm_mon + 1;
  start_day = today->tm_mday;
  end_day = today->tm_mday;
  project_id = -1;
  hours_per_day = 8;
  finished = false;
  time(&id);
}

Job::Job(std::string xmlstring)
{
  //change this
  time_t t;
  struct tm *tm_now;
  time(&t);
  tm_now = localtime(&t);

  size_t find1, find2;
  find1 = xmlstring.find("<job>");
  find2 = xmlstring.find("</job>");
  if(find1 != std::string::npos && find2 != std::string::npos)
  {
    find1 = xmlstring.find("<id>");
    find2 = xmlstring.find("</id>");
    if(find1 != std::string::npos && find2 != std::string::npos)
    {
      std::stringstream s1;
      s1 << xmlstring.substr(find1 + 4, find2 - find1 - 4);
      s1 >> id;
      if(s1.fail())
      {
	time(&id);
      }
    }
    else
      time(&id);
    
    find1 = xmlstring.find("<staff_id>");
    find2 = xmlstring.find("</staff_id>");
    if(find1 != std::string::npos && find2 != std::string::npos)
    {
      std::stringstream s2;
      s2 << xmlstring.substr(find1 + 10, find2 - find1 - 10);
      s2 >> staff_id;
      if(s2.fail())
      {
	staff_id = -1;
      }
    }
    else
      staff_id = -1;

    find1 = xmlstring.find("<project_id>");
    find2 = xmlstring.find("</project_id>");
    if(find1 != std::string::npos && find2 != std::string::npos)
    {
      std::stringstream s3;
      s3 << xmlstring.substr(find1 + 12, find2 - find1 - 12);
      s3 >> project_id;
      if(s3.fail())
      {
	project_id = -1;
      }
    }
    else
      project_id = -1;

    find1 = xmlstring.find("<start_year>");
    find2 = xmlstring.find("</start_year>");
    if(find1 != std::string::npos && find2 != std::string::npos)
    {
      std::stringstream s4;
      s4 << xmlstring.substr(find1 + 12, find2 - find1 - 12);
      s4 >> start_year;
      if(s4.fail())
      {
	start_year = tm_now->tm_year + 1900;
      }
    }
    else
      start_year = tm_now->tm_year + 1900;

    find1 = xmlstring.find("<start_month>");
    find2 = xmlstring.find("</start_month>");
    if(find1 != std::string::npos && find2 != std::string::npos)
    {
      std::stringstream s5;
      s5 << xmlstring.substr(find1 + 14, find2 - find1 - 14);
      s5 >> start_month;
      if(s5.fail())
      {
	start_month = tm_now->tm_mon + 1;
      }
    }
    else
      start_month = tm_now->tm_mon + 1;

    find1 = xmlstring.find("<start_day>");
    find2 = xmlstring.find("</start_day>");
    if(find1 != std::string::npos && find2 != std::string::npos)
    {
      std::stringstream s6;
      s6 << xmlstring.substr(find1 + 11, find2 - find1 - 11);
      s6 >> start_day;
      if(s6.fail())
      {
	start_day = tm_now->tm_mday;
      }
    }
    else
      start_day = tm_now->tm_mday;

    find1 = xmlstring.find("<end_year>");
    find2 = xmlstring.find("</end_year>");
    if(find1 != std::string::npos && find2 != std::string::npos)
    {
      std::stringstream s7;
      s7 << xmlstring.substr(find1 + 10, find2 - find1 - 10);
      s7 >> end_year;
      if(s7.fail())
      {
	end_year = tm_now->tm_year + 1900;
      }
    }
    else
      end_year = tm_now->tm_year + 1900;

    find1 = xmlstring.find("<end_month>");
    find2 = xmlstring.find("</end_month>");
    if(find1 != std::string::npos && find2 != std::string::npos)
    {
      std::stringstream s8;
      s8 << xmlstring.substr(find1 + 11, find2 - find1 - 11);
      s8 >> end_month;
      if(s8.fail())
      {
	end_month = tm_now->tm_mon + 1;
      }
    }
    else
      end_month = tm_now->tm_mon + 1;

    find1 = xmlstring.find("<end_day>");
    find2 = xmlstring.find("</end_day>");
    if(find1 != std::string::npos && find2 != std::string::npos)
    {
      std::stringstream s9;
      s9 << xmlstring.substr(find1 + 9, find2 - find1 - 9);
      s9 >> end_day;
      if(s9.fail())
      {
	end_day = tm_now->tm_mday;
      }
    }
    else
      end_day = tm_now->tm_mday;

    find1 = xmlstring.find("<description>");
    find2 = xmlstring.find("</description>");
    if(find1 != std::string::npos && find2 != std::string::npos)
    {
      description = xmlstring.substr(find1 + 13, find2 - find1 - 13);
    }
    else
      description = "";

    find1 = xmlstring.find("<hours_per_day>");
    find2 = xmlstring.find("</hours_per_day>");
    if(find1 != std::string::npos && find2 != std::string::npos)
    {
      std::stringstream s10;
      s10 << xmlstring.substr(find1 + 15, find2 - find1 - 15);
      s10 >> hours_per_day;
      if(s10.fail())
      {
	hours_per_day = 8;
      }
    }
    else
      hours_per_day = 8;

    find1 = xmlstring.find("<finished>");
    find2 = xmlstring.find("</finished>");
    if(find1 != std::string::npos && find2 != std::string::npos)
    {
      std::string str = xmlstring.substr(find1 + 10, find2 - find1 - 10);
      if(str == "1")
      {
	finished = true;
      }
      else
	finished = false;
    }
    else
      finished = false;
  }
  else
  {
    time(&id);
    staff_id = -1;
    project_id = -1;
    start_year = tm_now->tm_year + 1900;
    end_year = tm_now->tm_year + 1900;
    start_month = tm_now->tm_mon + 1;
    end_month = tm_now->tm_mon + 1;
    start_day = tm_now->tm_mday;
    end_day = tm_now->tm_mday;
    hours_per_day = 8;
    finished = false;
    description = "";
  }
  
}

time_t Job::get_staff_id() const
{
  return staff_id;
}

time_t Job::get_project_id() const
{
  return project_id;
}

std::string Job::get_description() const
{
  return description;
}

std::string Job::get_start_date_str_eu() const
{
  std::stringstream ss;
  ss << start_year << "-";
  if(start_month < 10)
  {
    ss << "0" << start_month;
  }
  else
  {
    ss << start_month;
  }
  ss << "-";
  
  if(start_day < 10)
  {
    ss << "0" << start_day;
  }
  else
  {
    ss << start_day;
  }

  return ss.str();
}

std::string Job::get_start_date_str_us() const
{
  std::stringstream ss;
  ss << start_month << "/" << start_day << "/" << start_year;
  return ss.str();
}

std::string Job::get_end_date_str_eu() const
{
  std::stringstream ss;
  ss << end_year << "-";
  if(end_month < 10)
  {
    ss << "0" << end_month;
  }
  else
  {
    ss << end_month;
  }
  ss << "-";

  if(end_day < 10)
  {
    ss << "0" << end_day;
  }
  else
  {
    ss << end_day;
  }

  return ss.str();
}

std::string Job::get_end_date_str_us() const
{
  std::stringstream ss;
  ss << end_month << "/" << end_day << "/" << end_year;
  return ss.str();
}

int Job::get_start_year() const
{
  return start_year;
}

int Job::get_end_year() const
{
  return end_year;
}

int Job::get_start_month() const
{
  return start_month;
}

int Job::get_end_month() const
{
  return end_month;
}

int Job::get_start_day() const
{
  return start_day;
}

int Job::get_end_day() const
{
  return end_day;
}

int Job::get_hours_per_day() const
{
  return hours_per_day;
}

bool Job::get_finished() const
{
  return finished;
}

void Job::set_staff_id(time_t staff_id)
{
  this->staff_id = staff_id;
}

void Job::set_project_id(time_t project_id)
{
  this->project_id = project_id;
}

void Job::set_description(std::string desc)
{
  description = desc;
}

void Job::set_start_date(std::string start_date)
{
  int *date;
  date = date_str_to_int(start_date);
  if(date[0] != -1 && date[1] != -1 && date[2] != -1)
  {
    start_year = date[0];
    start_month = date[1];
    start_day = date[2];
  }
  delete[] date;
}

void Job::set_end_date(std::string end_date)
{
  int *date;
  date = date_str_to_int(end_date);
  if(date[0] != -1 && date[1] != -1 && date[2] != -1)
  {
    end_year = date[0];
    end_month = date[1];
    end_day = date[2];
  }
  delete[] date;
}

void Job::set_start_year(int year)
{
  if(year >= 1900)
  {
    start_year = year;
  }
}

void Job::set_end_year(int year)
{
  if(year >= 1900)
  {
    end_year = year; 
  }
}

void Job::set_start_month(int month)
{
  if(month >= 1 && month <=12)
  {
    start_month = month;
  }
}

void Job::set_end_month(int month)
{
  if(month >=1 && month <=12)
  {
    end_month = month;
  }
}

void Job::set_start_day(int day)
{
  if(day >=1 && day <= 31)
  {
    if((start_month == 4 || start_month == 6 ||
       start_month == 9 || start_month == 11) &&
       day <= 30)
    {
      start_day = day;
    }
    else if(start_month == 2)
    {
      if(fmod(start_year, 4) == 0 && day <= 29)
      {
	start_day = day;
      }
      else if(day <= 28)
      {
	start_day = day;
      }
    }
    else
    {
      start_day = day;
    }
  }
}

void Job::set_end_day(int day)
{
  if(day >=1 && day <= 31)
  {
    if((end_month == 4 || end_month == 6 ||
       end_month == 9 || end_month == 11) &&
       day <= 30)
    {
      end_day = day;
    }
    else if(end_month == 2)
    {
      if(fmod(end_year, 4) == 0 && day <= 29)
      {
	end_day = day;
      }
      else if(day <= 28)
      {
	end_day = day;
      }
    }
    else
    {
      end_day = day;
    }
  }
}

void Job::set_hours_per_day(int hours)
{
  if(hours >= 0 && hours <= 24)
  {
    hours_per_day = hours;
  }
}

void Job::set_finished(bool f)
{
  finished = f;
}

void Job::set_id(time_t id)
{
  this->id = id;
}

int Job::total_working_hours(int days_per_week)
{
  int days = total_working_days(days_per_week);
  if(days != -1)
  {
    return hours_per_day * days;
  }
  return -1;
}

int Job::total_working_days(int days_per_week)
{
  if(days_per_week <= 7)
  {
    time_t t_start, t_end;
    struct tm *tm_start, *tm_end;
    time(&t_start);
    tm_start = localtime(&t_start);
    tm_start->tm_year = start_year - 1900;
    tm_start->tm_mon = start_month -1;
    tm_start->tm_mday = start_day;
    tm_start->tm_sec = 0;
    tm_start->tm_min = 0;
    tm_start->tm_hour = 0;
    t_start = mktime(tm_start);

    time(&t_end);
    tm_end = localtime(&t_end);
    tm_end->tm_year = end_year - 1900;
    tm_end->tm_mon = end_month - 1;
    tm_end->tm_mday = end_day;
    tm_end->tm_sec = 1;
    tm_end->tm_min = 0;
    tm_end->tm_hour = 0;
    t_end = mktime(tm_end);

    if(t_start != -1 && t_end != -1)
    {
      double diff, weeks, days, mod_days;
    
      diff = difftime(t_end, t_start);
      weeks = (diff/60/60/24)/7;
      days = floor(weeks) * days_per_week;
      mod_days = fmod(diff/60/60/24, 7);
      mod_days = floor(mod_days);
      if(mod_days < days_per_week)
      {
        days += mod_days + 1;
      }
      else
      {
        days += days_per_week;
      }
      return (int) days;
    }
  }
  return -1;
}

std::string Job::get_obj_xml_str() const
{
  std::stringstream ss, ss2, ss3, ss4, ss5, ss6, ss7, ss8, ss9, ss10, ss11;
  std::string xmlstr = get_xml_head();
  xmlstr +=  get_DTD_str();
  xmlstr += get_first_level_open_tag("job");
  ss << id;
  xmlstr += get_second_level_object("id", ss.str());
  ss2 << staff_id;
  xmlstr += get_second_level_object("staff_id", ss2.str());
  ss3 << project_id;
  xmlstr += get_second_level_object("project_id", ss3.str());
  ss4 << start_year;
  xmlstr += get_second_level_object("start_year", ss4.str());
  ss5 << start_month;
  xmlstr += get_second_level_object("start_month", ss5.str());
  ss6 << start_day;
  xmlstr += get_second_level_object("start_day", ss6.str());
  ss7 << end_year;
  xmlstr += get_second_level_object("end_year", ss7.str());
  ss8 << end_month;
  xmlstr += get_second_level_object("end_month", ss8.str());
  ss9 << end_day;
  xmlstr += get_second_level_object("end_day", ss9.str());
  xmlstr += get_second_level_object("description", description);
  ss10 << hours_per_day;
  xmlstr += get_second_level_object("hours_per_day", ss10.str());
  ss11 << finished;
  xmlstr += get_second_level_object("finished", ss11.str());
  xmlstr += get_first_level_close_tag("job");
  return xmlstr;
}

time_t Job::get_id() const
{
  return id;
}

int * Job::date_str_to_int(std::string date_string)
{
  int *int_date = new int[3];
  int_date[0] = -1;
  int_date[1] = -1;
  int_date[2] = -1;

  int no = -1;
  size_t found, found2;
  std::stringstream ss, ss2, ss3;
  if(date_string.size() == 10)
  {
    found = date_string.find("-");
    found2 = date_string.find("-", found + 1);
    if(found == 4 && found2 == 7)
    {
      ss << date_string.substr(0, 4);
      ss >> no;

      if(!ss.fail() && no >= 1900)
      {
	  int_date[0] = no;
	  ss2 << date_string.substr(5, 2);
	  ss2 >> no;

	  if(!ss2.fail() && no > 0 && no < 13)
          {
	    int_date[1] = no;
	    ss3 << date_string.substr(8, 2);
	    ss3 >> no;

	    if(!ss3.fail() && no > 0 && no < 32)
            {
	      if(int_date[1] == 4 || int_date[1] ==  6 ||
		 int_date[1] == 9 || int_date[1] ==  11)
	      {
		if(no < 31)
		{
		  int_date[2] = no;
		}
	      }
	      else if(int_date[1] == 2)
	      {
		if(fmod(int_date[0], 4) == 0)
		{
		  if(no < 30)
		  {
		    int_date[2] = no;
		  } 
		}
		else if(no < 29)
		{
		  int_date[2] = no;
		}
	      }
	      else
	      {
		int_date[2] = no;
	      }
	    }
          }
      }
    }
    else
    {
      return date_str_to_int_us(date_string);
    }
  }
  else
  {
    return date_str_to_int_us(date_string);
  }    
  return int_date;
}

int * Job::date_str_to_int_us(std::string date_string)
{
  int *int_date = new int[3];
  int_date[0] = -1;
  int_date[1] = -1;
  int_date[2] = -1;

  size_t found;
  size_t found2;
  std::stringstream ss, ss2, ss3;
  int no = -1;
  if(date_string.size() <= 10 && date_string.size() >= 6)
  {
    found = date_string.find("/");
    found2 = date_string.find("/", found + 1);
    if(found != std::string::npos && found2 != std::string::npos)
    {
      ss << date_string.substr(found2 + 1);
      ss >> no;

      if(!ss.fail())
      {
	if(no >= 1900)
	{
	  int_date[0] = no;
	}
	else if(no >= 0 && no < 100)
	{
	  int_date[0] = no + 2000;
	}
	ss2 << date_string.substr(0, found);
	ss2 >> no;
	if(!ss2.fail() && no > 0 && no < 13)
	{
	  int_date[1] = no;
	  ss3 << date_string.substr(found + 1, found2);
	  ss3 >> no;
	  if(!ss3.fail() && no > 0 && no < 32)
	  {
	    if((int_date[1] == 4 || int_date[1] ==  6 ||
		int_date[1] == 9 || int_date[1] ==  11) && no < 31)
	    {
	      int_date[2] = no;
	    }
	    else if(int_date[1] == 2)
	    {
	      if(fmod(int_date[0], 4) == 0 && no < 30)
	      {
		int_date[2] = no;
	      }
	      else if(no < 29)
	      {
		int_date[2] = no;
	      }
	    }
	    else
	    {
	      int_date[2] = no;
	    }
	  }
	}
      }
    }
  }
  return int_date;
}

std::string Job::get_DTD_str() const
{
  std::string dtdstr = "<!DOCTYPE job [";
  dtdstr += "\n\t<!ELEMENT job (id, staff_id, project_id,";
  dtdstr += "\n\tstart_year, start_month, start_day,";
  dtdstr += "\n\tend_year, end_month, end_day,";
  dtdstr += "\n\tdescription, hours_per_day, finished)>";
  dtdstr += "\n\t<!ELEMENT id\t\t(#PCDATA)>";
  dtdstr += "\n\t<!ELEMENT staff_id\t(#PCDATA)>";
  dtdstr += "\n\t<!ELEMENT project_id\t(#PCDATA)>";
  dtdstr += "\n\t<!ELEMENT start_year\t(#PCDATA)>";
  dtdstr += "\n\t<!ELEMENT start_month\t(#PCDATA)>";
  dtdstr += "\n\t<!ELEMENT start_day\t(#PCDATA)>";
  dtdstr += "\n\t<!ELEMENT end_year\t(#PCDATA)>";
  dtdstr += "\n\t<!ELEMENT end_month\t(#PCDATA)>";
  dtdstr += "\n\t<!ELEMENT end_day\t(#PCDATA)>";
  dtdstr += "\n\t<!ELEMENT description\t(#PCDATA)>";
  dtdstr += "\n\t<!ELEMENT hours_per_day\t(#PCDATA)>";
  dtdstr += "\n\t<!ELEMENT finished\t(#PCDATA)>";
  dtdstr += "\n]>\n";
  return dtdstr;
}
