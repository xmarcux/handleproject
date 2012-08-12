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

#ifndef DATE_H
#define DATE_H

#include <string>

/* Date class represent both
 * a start and an end date.
 * Date contains needed functionality
 * for changing, comparing and 
 * getting the values in different ways.
 */
class Date
{
 public:
  /* Constructors for Date.
   * Default values for start
   * and end date is today, 
   * when object is created,
   * if value is not given in constructor.
   * If any of date values given is invalid 
   * date will be initialized to today.
   * Invalid values is year < 1900,
   * month > 12 and < 1, day is 
   * not a valid day in specified month.
   */
  Date();

  Date(int start_year, int start_month, int start_day,
       int end_year, int end_month, int end_day);

  /* If start_date is true then the
   * start date will be set, else
   * end date will be set.
   */
  Date(bool start_date, int year, int month, int day);

  Date(std::string start_date, std::string end_date);

  /* If start_date is true then the
   * start date will be set, else
   * end date will be set.
   */
  Date(bool start_date, std::string date);
  
  /* Methods to get information
   * out of object.
   */
  int get_start_year() const;
  int get_start_month() const;
  int get_start_day() const;
  int get_end_year() const;
  int get_end_month() const;
  int get_end_day() const;

  /* Returns true if argument date
   * is between or equal to start and
   * end date.
   */
  bool between_dates(int y, int m, int d) const;

  /* Returns a string in format: YYYY-MM-DD */
  std::string get_start_date_str_eu() const;

  /* Returns a string in format: MM/DD/YYYY 
   * If month or day is smaller then 10,
   * format will be: M/D/YYYY
   */
  std::string get_start_date_str_us() const;

  /* Returns a string in format: YYYY-MM-DD */
  std::string get_end_date_str_eu() const;

  /* Returns a string in format: MM/DD/YYYY 
   * If month or day is smaller then 10,
   * format will be: M/D/YYYY
   */
  std::string get_end_date_str_us() const;

  /* Set variables in object.
   * Year must be equal or greater then 1900.
   * Month must be between 1 and 12, and
   * day must be between 1 and maximum
   * for the current month.
   * If values are invalid that property
   * will not be changed.
   * Returns 1 if changed and -1 if not changed.
   */
  int set_start_year(int year);
  int set_start_month(int month);
  int set_start_day(int day);
  int set_end_year(int year);
  int set_end_month(int month);
  int set_end_day(int day);
  void set_finished(bool fin);

  /* String attribute is a date formated string
   * and should have a format with the minimum year 1900.
   * Four formats are supported: 
   * YYYY-MM-DD
   * YY-MM-DD (where year is assumed to be equal or larger then 2000.)
   * MM/DD/YYYY
   * MM/DD/YY (where year is assumed to be equal or larger then 2000.)
   * If the format is not right date will not be changed. 
   * Returns 1 if changed and -1 if not changed.
   */
  int set_start_date(std::string start_date);
  int set_end_date(std::string end_date);

  /* Tells if activity is
   * finished or if there
   * is more job to do.
   */
  bool is_finished() const;

  /* Returns false if todays
   * date is smaller or equal
   * with end date, else 
   * true is returned.
   */
  bool is_late() const;

 private:
  int start_year;
  int start_month;
  int start_day;
  int end_year;
  int end_month;
  int end_day;
  bool finished;

  /* Privte initialization method
   * to initialize object and is
   * called from constructors.
   * To initialize start or end date
   * to today just set variables to zero,
   * i.e. an invalid value.
   */
  void init(int s_year, int s_month, int s_day,
	    int e_year, int e_month, int e_day);

  /* Returns 1 if date is valid
   * and -1 if not.
   * Invalid values is year < 1900,
   * month > 12 and < 1, day is 
   * not a valid day in specified month.
   */
  int valid_date(int year, int month, int day) const;

  /* Converts a date string to three integers,
   * where first pointer is the year, second
   * pointer is the month and third pointer
   * is the day of month.
   * If any value in string is invalid that
   * integer will be set to -1.
   */
  int *  date_str_to_int(std::string date_string) const;
  int *  date_str_to_int_us(std::string date_string) const;
};

#endif
