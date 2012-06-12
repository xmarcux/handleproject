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

#include <glibmm/i18n.h>
#include <glibmm/date.h>
#include "activitydialog.h"
#include <gtkmm/label.h>
#include <gtkmm/box.h>
#include <gtkmm/table.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/calendar.h>

ActivityDialog::ActivityDialog(ActivitiesWindow *parent, Activity *activity)
  : parent(parent), activity(activity)
{
  set_icon_from_file("images/HaPr_high_80x100_ver2.gif");
  if(activity)
  {
    Gtk::Dialog(_("Edit activity"), parent);
    set_title(_("Edit activity"));
  }
  else
  {
    Gtk::Dialog(_("Edit activity"), parent);
    set_title(_("New activity"));
  }
  set_transient_for(*parent);

  add_button(Gtk::Stock::CANCEL, 2);
  if(activity)
    add_button(Gtk::Stock::SAVE, Gtk::RESPONSE_OK);
  else
    add_button(_("Create activity"), Gtk::RESPONSE_OK);

  Gtk::Box *cont_area = get_vbox();
  Gtk::Table main_table(10, 3);
  main_table.set_row_spacings(10);
  cont_area->pack_start(main_table);

  Gtk::Label main_label;
  if(activity)
    main_label.set_text(_("Edit properties for activity:"));
  else
    main_label.set_text(_("Enter properties for new activity:"));
  main_table.attach(main_label, 0, 3, 0, 1);

  Gtk::Label no_label(_("Activity number:"), Gtk::ALIGN_LEFT, Gtk::ALIGN_CENTER);
  main_table.attach(no_label, 0, 3, 1, 2);
  main_table.attach(number_entry, 0, 3, 2, 3);

  Gtk::Label name_label(_("Activity name:"), Gtk::ALIGN_LEFT, Gtk::ALIGN_CENTER);
  main_table.attach(name_label, 0, 3, 3, 4);
  main_table.attach(name_entry, 0, 3, 4, 5);

  Gtk::Label desc_label(_("Description:"), Gtk::ALIGN_LEFT, Gtk::ALIGN_CENTER);
  main_table.attach(desc_label, 0, 3, 5, 6);
  Gtk::ScrolledWindow desc_scroll;
  desc_scroll.add(desc_area);
  desc_scroll.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
  main_table.attach(desc_scroll, 0, 3, 6, 7);

  Gtk::Label start_date_label(_("Start date:"), Gtk::ALIGN_RIGHT, Gtk::ALIGN_CENTER);
  start_date_entry.set_max_length(10);
  start_date_entry.set_width_chars(14);
  Gtk::Button start_cal_button(_("Calendar"));
  start_cal_button.signal_clicked().connect(sigc::mem_fun(*this, &ActivityDialog::on_click_start_calendar));
  main_table.attach(start_date_label, 0, 1, 7, 8);
  main_table.attach(start_date_entry, 1, 2, 7, 8);
  main_table.attach(start_cal_button, 2, 3, 7, 8, Gtk::SHRINK, Gtk::SHRINK);

  Gtk::Label end_date_label(_("End date:"), Gtk::ALIGN_RIGHT, Gtk::ALIGN_CENTER);
  end_date_entry.set_max_length(10);
  end_date_entry.set_width_chars(14);
  Gtk::Button end_cal_button(_("Calendar"));
  end_cal_button.signal_clicked().connect(sigc::mem_fun(*this, &ActivityDialog::on_click_end_calendar));
  main_table.attach(end_date_label, 0, 1, 8, 9);
  main_table.attach(end_date_entry, 1, 2, 8, 9);
  main_table.attach(end_cal_button, 2, 3, 8, 9, Gtk::SHRINK, Gtk::SHRINK);

  check_button_finished.set_label(_("Activity finished"));
  main_table.attach(check_button_finished, 1, 3, 9, 10);

  show_all_children();
  run();
}

void ActivityDialog::on_click_start_calendar()
{
  show_calendar();
}

void ActivityDialog::on_click_end_calendar()
{
  show_calendar(false);
}

void ActivityDialog::show_calendar(bool start_cal)
{
  Gtk::Dialog cal_dialog;
  if(start_cal)
    cal_dialog.set_title(_("Start date"));
  else
    cal_dialog.set_title(_("End date"));

  cal_dialog.set_icon_from_file("images/HaPr_high_80x100_ver2.gif");
  cal_dialog.add_button(Gtk::Stock::CANCEL, 0);
  cal_dialog.add_button(Gtk::Stock::OK, 1);

  Gtk::Calendar cal;
  Gtk::Box *cal_box = cal_dialog.get_vbox();
  cal_box->pack_start(cal);

  cal_dialog.show_all_children();

  int response = cal_dialog.run();
  if(response == 1)
  {
    Glib::Date sdate;
    cal.get_date(sdate);
    if(start_cal)
      start_date_entry.set_text(sdate.format_string("%F"));
    else
      end_date_entry.set_text(sdate.format_string("%F"));
  }
}

ActivityDialog::~ActivityDialog()
{

}
