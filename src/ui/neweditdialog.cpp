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

#include "neweditdialog.h"
#include "../files.h"
#include <sstream>
#include <glibmm/i18n.h>
#include <gtkmm/box.h>
#include <gtkmm/frame.h>
#include <gtkmm/label.h>
#include <gtkmm/box.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/button.h>
#include <gtkmm/calendar.h>
#include <gtkmm/stock.h>
#include <gtkmm/table.h>
#include <gtkmm/messagedialog.h>
#include <gtkmm/textbuffer.h>
#include <glibmm/date.h>
#include <glibmm/ustring.h>



NewEditDialog::NewEditDialog(MainWindow *parent, ProjectWindow *new_parent, Project *proj)
  : parent_window(parent), new_parent_window(new_parent)
{

  if(proj)
  {
    Gtk::Dialog(_("Edit project properties"), new_parent);
    set_title(_("Edit project properties"));
    set_transient_for(*new_parent);
  }
  else
  {
    Gtk::Dialog(_("New project"), parent);
    set_title(_("New project"));
    set_transient_for(*parent);
  }
  set_icon_from_file("images/HaPr_high_80x100_ver2.gif");

  add_button(Gtk::Stock::CANCEL, 2);
  if(proj)
    add_button(Gtk::Stock::SAVE, Gtk::RESPONSE_OK);
  else
    add_button(_("Create project"), Gtk::RESPONSE_OK);
  Gtk::Box *cont_area = get_vbox();
  Gtk::Table main_table(16, 3);
  main_table.set_row_spacings(10);
  cont_area->pack_start(main_table);
  Gtk::Label main_label;
  if(proj)
    main_label.set_text(_("Edit properties for project:"));
  else
    main_label.set_text(_("Enter properties for new project:"));

  main_table.attach(main_label,0, 3, 0, 1);

  Gtk::Label number_label(_("Project number:"), Gtk::ALIGN_LEFT, Gtk::ALIGN_CENTER);
  main_table.attach(number_label, 0, 3, 1, 2);
  main_table.attach(number_entry, 0, 3, 2, 3);
  if(proj)
    number_entry.set_text(proj->get_project_no());

  Gtk::Label name_label(_("Project name:"), Gtk::ALIGN_LEFT, Gtk::ALIGN_CENTER);
  main_table.attach(name_label, 0, 3, 3, 4);
  main_table.attach(name_entry, 0, 3, 4, 5);
  if(proj)
    name_entry.set_text(proj->get_project_name());

  Gtk::Label desc_label(_("Description:"), Gtk::ALIGN_LEFT, Gtk::ALIGN_CENTER);
  main_table.attach(desc_label, 0, 3, 5, 6);
  Gtk::ScrolledWindow desc_scroll;
  desc_view.set_wrap_mode(Gtk::WRAP_WORD);
  desc_scroll.add(desc_view);
  desc_scroll.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
  main_table.attach(desc_scroll, 0, 3, 6, 7);
  if(proj)
    desc_view.get_buffer()->set_text(proj->get_description());

  Gtk::Label leader_name_label(_("Project leader name:"), Gtk::ALIGN_LEFT, Gtk::ALIGN_CENTER);
  main_table.attach(leader_name_label, 0, 3, 7, 8);
  main_table.attach(leader_name_entry, 0, 3, 8, 9);
  if(proj)
    leader_name_entry.set_text(proj->get_project_leader_name());

  Gtk::Label leader_surname_label(_("Project leader surname:"), Gtk::ALIGN_LEFT, Gtk::ALIGN_CENTER);
  main_table.attach(leader_surname_label, 0, 3, 9, 10);
  main_table.attach(leader_surname_entry, 0, 3, 10, 11);
  if(proj)
    leader_surname_entry.set_text(proj->get_project_leader_surname());

  Gtk::Label initials_label(_("Project leader initials:"), Gtk::ALIGN_RIGHT, Gtk::ALIGN_CENTER);
  main_table.attach(initials_label, 0, 1, 11, 12);
  leader_initials_entry.set_max_length(6);
  leader_initials_entry.set_width_chars(10);
  main_table.attach(leader_initials_entry, 1, 2, 11, 12);
  if(proj)
    leader_initials_entry.set_text(proj->get_project_leader_initials());

  Gtk::Label start_label(_("Start date:"), Gtk::ALIGN_RIGHT, Gtk::ALIGN_CENTER);
  main_table.attach(start_label, 0, 1, 12, 13);
  start_date_entry.set_max_length(10);
  start_date_entry.set_width_chars(14);
  main_table.attach(start_date_entry, 1, 2, 12, 13);
  Gtk::Button start_cal_button(_("Calendar"));
  start_cal_button.signal_clicked().connect(sigc::mem_fun(*this, &NewEditDialog::on_click_start_calendar));
  main_table.attach(start_cal_button, 2, 3, 12, 13, Gtk::SHRINK, Gtk::SHRINK);
  if(proj)
    start_date_entry.set_text(proj->get_start_date_str_eu());

  Gtk::Label end_label(_("End date:"), Gtk::ALIGN_RIGHT, Gtk::ALIGN_CENTER);
  main_table.attach(end_label, 0, 1, 13, 14);
  end_date_entry.set_max_length(10);
  end_date_entry.set_width_chars(14);
  main_table.attach(end_date_entry, 1, 2, 13, 14);
  Gtk::Button end_cal_button(_("Calendar"));
  end_cal_button.signal_clicked().connect(sigc::mem_fun(*this, &NewEditDialog::on_click_end_calendar));
  main_table.attach(end_cal_button, 2, 3, 13, 14, Gtk::SHRINK, Gtk::SHRINK);
  if(proj)
    end_date_entry.set_text(proj->get_end_date_str_eu());

  Gtk::Label hour_day_label(_("Working hours per day:"), Gtk::ALIGN_RIGHT, Gtk::ALIGN_CENTER);
  main_table.attach(hour_day_label, 0, 1, 14, 15);
  hour_per_day_entry.set_max_length(2);
  hour_per_day_entry.set_width_chars(4);
  hour_per_day_entry.set_text("8");
  main_table.attach(hour_per_day_entry, 1, 2, 14, 15);
  if(proj)
  {
    std::stringstream ss;
    ss << proj->get_working_hours_per_day();
    if(!ss.fail())
      hour_per_day_entry.set_text(ss.str());
  }

  Gtk::Label day_week_label(_("Working days per week:"), Gtk::ALIGN_RIGHT, Gtk::ALIGN_CENTER);
  main_table.attach(day_week_label, 0, 1, 15, 16);
  days_per_week_entry.set_max_length(2);
  days_per_week_entry.set_width_chars(4);
  days_per_week_entry.set_text("5");
  main_table.attach(days_per_week_entry, 1, 2, 15, 16);
  if(proj)
  {
    std::stringstream ss;
    ss << proj->get_working_days_per_week();
    if(!ss.fail())
      days_per_week_entry.set_text(ss.str());
  }

  show_all_children();
  while(true)
  {
  int result = run();
  if(result == Gtk::RESPONSE_OK)
  {
    Glib::ustring error_msg;
    if(name_entry.get_text().size() == 0)
      error_msg = _("Project must have a name.\n");
    if(start_date_entry.get_text().size() == 0)
      error_msg += _("Project must have a start date.\n");
    if(end_date_entry.get_text().size() == 0)
      error_msg += _("Project must have an end date.");
    if(error_msg.size() > 0)
    {
      Gtk::MessageDialog message(error_msg, false, Gtk::MESSAGE_ERROR);
      message.set_icon_from_file("images/HaPr_high_80x100_ver2.gif");
      message.run();
    }
    else
    {
      Glib::RefPtr<Gtk::TextBuffer> desc_buff = desc_view.get_buffer();
      Project newp(number_entry.get_text(), name_entry.get_text(), desc_buff->get_text());
      if(leader_name_entry.get_text().size() > 0)
	newp.set_project_leader_name(leader_name_entry.get_text());
      if(leader_surname_entry.get_text().size() > 0)
	newp.set_project_leader_surname(leader_surname_entry.get_text());
      if(leader_initials_entry.get_text().size() > 0)
	newp.set_project_leader_initials(leader_initials_entry.get_text());
      if(days_per_week_entry.get_text().size() > 0)
      {
	std::stringstream ss1;
	ss1 << days_per_week_entry.get_text();
	int days;
	ss1 >> days;
	if(!ss1.fail())
	  newp.set_working_days_per_week(days);
      }
      if(hour_per_day_entry.get_text().size() > 0)
      {
	std::stringstream ss2;
	ss2 << hour_per_day_entry.get_text();
	int hours;
	ss2 >> hours;
	if(!ss2.fail())
	  newp.set_working_hours_per_day(hours);
      }
      if(start_date_entry.get_text().size() > 0)
	newp.set_start_date(start_date_entry.get_text());
      if(end_date_entry.get_text().size() > 0)
	newp.set_end_date(end_date_entry.get_text());
      if(proj)
      {
	newp.set_project_id(proj->get_id());
	proj->set_project_no(newp.get_project_no());
	proj->set_project_name(newp.get_project_name());
	proj->set_description(newp.get_description());
	proj->set_project_leader(newp.get_project_leader());
	proj->set_start_date(newp.get_start_date_str_eu());
	proj->set_end_date(newp.get_end_date_str_eu());
	proj->set_working_days_per_week(newp.get_working_days_per_week());
	proj->set_working_hours_per_day(newp.get_working_hours_per_day());
	
	new_parent->update_view();
	parent_window->update_project_view(proj);
      }
      else
	parent_window->add_new_project(newp);

      save_object_to_db(&newp);

      break;
    }
  }
  else
    break;
  }
}

void NewEditDialog::on_click_start_calendar()
{
  show_calendar();
}

void NewEditDialog::on_click_end_calendar()
{
  show_calendar(false);
}

void NewEditDialog::show_calendar(bool start_date_cal)
{
  Gtk::Dialog cal_dialog;
  if(start_date_cal)
    cal_dialog.set_title(_("Start date"));
  else
    cal_dialog.set_title(_("End date"));
  Gtk::Calendar cal;
  cal_dialog.set_icon_from_file("images/HaPr_high_80x100_ver2.gif");
  cal_dialog.add_button(Gtk::Stock::CANCEL, 0);
  cal_dialog.add_button(Gtk::Stock::OK, 1);
  Gtk::Box *cal_box = cal_dialog.get_vbox();
  cal_box->pack_start(cal);
  cal_dialog.show_all_children();
  int response = cal_dialog.run();
  if(response == 1)
  {
    Glib::Date sdate;
    cal.get_date(sdate);
    if(start_date_cal)
      start_date_entry.set_text(sdate.format_string("%F"));
    else
      end_date_entry.set_text(sdate.format_string("%F"));
  }
}

NewEditDialog::~NewEditDialog()
{

}
