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

#include "date.h"
#include <ctime>
#include <cmath>
#include <sstream>

Date::Date()
{
  init(0, 0, 0, 0, 0, 0);
}

Date::Date(int start_year, int start_month, int start_day,
	   int end_year, int end_month, int end_day)
{
  init(start_year, start_month, start_day,
       end_year, end_month, end_day);
}

Date::Date(bool start_date, int year, int month, int day)
{
  if(start_date)
    init(year, month, day, 0, 0, 0);
  else
    init(0, 0, 0, year, month, day);
}

Date::Date(std::string start_date, std::string end_date)
{
  int *pstart, *pend;
  pstart = date_str_to_int(start_date);
  pend = date_str_to_int(end_date);
  init(pstart[0], pstart[1], pstart[2], pend[0], pend[1], pend[2]);
}

Date::Date(bool start_date, std::string date)
{
  int *pdate;
  pdate = date_str_to_int(date);
  if(start_date)
    init(pdate[0], pdate[1], pdate[2], 0, 0, 0);
  else
    init(0, 0, 0, pdate[0], pdate[1], pdate[2]);
}

int Date::get_start_year() const
{
  return start_year;
}

int Date::get_start_month() const
{
  return start_month;
}

int Date::get_start_day() const
{
  return start_day;
}

int Date::get_end_year() const
{
  return end_year;
}

int Date::get_end_month() const
{
  return end_month;
}

int Date::get_end_day() const
{
  return end_day;
}

std::string Date::get_start_date_str_eu() const
{
  std::stringstream ss;
  ss << start_year << "-";

  if(start_month < 10)
    ss << "0" << start_month;
  else
    ss << start_month;
  ss << "-";

  if(start_day < 10)
    ss << "0" << start_day;
  else
    ss << start_day;

  return ss.str();
}

std::string Date::get_start_date_str_us() const
{
  std::stringstream ss;
  ss << start_month << "/";
  ss << start_day << "/";
  ss << start_year;
  return ss.str();
}

std::string Date::get_end_date_str_eu() const
{
  std::stringstream ss;
  ss << end_year << "-";
  
  if(end_month < 10)
    ss << "0" << end_month;
  else
    ss << end_month;
  ss << "-";

  if(end_day < 10)
    ss << "0" << end_day;
  else
    ss << end_day;

  return ss.str();
}

std::string Date::get_end_date_str_us() const
{
  std::stringstream ss;
  ss << end_month << "/";
  ss << end_day << "/";
  ss << end_year;

  return ss.str();
}

int Date::set_start_year(int year)
{
  if(year < 1900)
    return -1;

  start_year = year;
  return 1;
}

int Date::set_start_month(int month)
{
  if(month < 1 || month > 12)
    return -1;

  start_month = month;
  return 1;
}

int Date::set_start_day(int day)
{
  if(day < 1 || day > 31)
    return -1;

  if((start_month == 4 || start_month == 6 || start_month == 9 || start_month == 11) && day > 30)
    return -1;

  if(start_month == 2 && fmod(start_year, 4) == 0 && day > 29)
    return -1;

  if(start_month == 2 && day > 28)
    return -1;

  start_day = day;
  return 1;
}

int Date::set_end_year(int year)
{
  if(year < 1900)
    return -1;

  end_year = year;
  return 1;
}

int Date::set_end_month(int month)
{
  if(month < 1 || month > 12)
    return -1;

  end_month = month;
  return 1;
}

int Date::set_end_day(int day)
{
  if(day < 1 || day > 31)
    return -1;

  if((end_month == 4 || end_month == 6 || end_month == 9 || end_month == 11) && day > 30)
    return -1;

  if(end_month == 2 && fmod(end_year, 4) == 0 && day > 29)
    return -1;

  if(end_month == 2 && day > 28)
    return -1;

  end_day = day;
  return 1;
}

void Date::set_finished(bool fin)
{
  finished = fin;
}

int Date::set_start_date(std::string start_date)
{
  int *pdate;
  pdate = date_str_to_int(start_date);
  if(pdate[0] == -1 || pdate[1] == -1 || pdate[2] == -1)
    return -1;

  start_year = pdate[0];
  start_month = pdate[1];
  start_day = pdate[2];
  return 1;
}

int Date::set_end_date(std::string end_date)
{
  int *pdate;
  pdate = date_str_to_int(end_date);
  if(pdate[0] == -1 || pdate[1] == -1 || pdate[2] == -1)
    return -1;

  end_year = pdate[0];
  end_month = pdate[1];
  end_day = pdate[2];
  return 1;
}

int * Date::date_str_to_int(std::string date_string) const
{
  int *int_date = new int[3];
  int_date[0] = -1;
  int_date[1] = -1;
  int_date[2] = -1;

  int no = -1;
  size_t found, found2;
  std::stringstream ss, ss2, ss3;
  if(date_string.size() == 10 || date_string.size() == 8)
  {
    found = date_string.find("-");
    found2 = date_string.find("-", found + 1);
    if((found == 4 && found2 == 7) || (found == 2 && found2 == 5))
    {
      ss << date_string.substr(0, 4);
      ss >> no;

      if(!ss.fail() && no >= 1900)
      {
	  if(no >= 1900)
	  {
	    int_date[0] = no;
	  }
	  else if(no >= 0 && no <= 99)
	  {
	    int_date[0] = no + 2000;
	  }
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

int * Date::date_str_to_int_us(std::string date_string) const
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

bool Date::is_finished() const
{
  return finished;
}

bool Date::is_late() const
{
  if(finished)
    return false;
  else
  {
    time_t today;
    struct tm *tm_today;
    time(&today);
    tm_today = localtime(&today);
    if(tm_today->tm_year + 1900 < get_end_year())
      return false;
    else if((tm_today->tm_year + 1900 == get_end_year()) &&
	    (tm_today->tm_mon + 1 < get_end_month()))
      return false;
    else if((tm_today->tm_year + 1900 == get_end_year()) &&
	    (tm_today->tm_mon + 1 == get_end_month()) &&
	    (tm_today->tm_mday <= get_end_day()))
      return false;
    else
      return true;  
  }
}

void Date::init(int s_year, int s_month, int s_day,
		int e_year, int e_month, int e_day)
{
  finished = false;
  time_t t;
  struct tm *tm_date;
  time(&t);
  tm_date = localtime(&t);

  if(valid_date(s_year, s_month, s_day) == 1)
  {
    start_year = s_year;
    start_month = s_month;
    start_day = s_day;
  }
  else
  {    
    start_year = tm_date->tm_year + 1900;
    start_month = tm_date->tm_mon + 1;
    start_day = tm_date->tm_mday;
  }

  if(valid_date(e_year, e_month, e_day) == 1)
  {
    end_year = e_year;
    end_month = e_month;
    end_day = e_day;
  }
  else
  {    
    end_year = tm_date->tm_year + 1900;
    end_month = tm_date->tm_mon + 1;
    end_day = tm_date->tm_mday;
  }
}

int Date::valid_date(int year, int month, int day) const
{
  if(year < 1900)
    return -1;

  if(month < 1 || month > 12)
    return -1;

  if(day < 1 || day > 31)
    return -1;

  if((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
    return -1;

  if(month == 2)
  {
    if(fmod(year, 4) == 0 && day > 29)
      return -1;
    else if(day > 28)
      return -1;
  }
  return 1;
}
