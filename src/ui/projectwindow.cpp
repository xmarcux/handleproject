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

#include "projectwindow.h"
#include "../files.h"
#include "about.h"
#include "neweditdialog.h"
#include "activitieswindow.h"
#include <ctime>
#include <sstream>
#include <map>
#include <glibmm/i18n.h>
#include <gtkmm/stock.h>

#define COLOR_ON_TIME         "#00FF00"
#define COLOR_LATE            "#FF0000"
#define COLOR_WHITE           "#FFFFFF"
#define COLOR_HISTORY         "#CCCCCC"
#define COLOR_HISTORY_ON_TIME "#99CC99"

ProjectWindow::ProjectWindow(time_t project_id, MainWindow *mainwindow)
  : project("", "", ""), mainwindow(mainwindow), main_box(new Gtk::VBox(false, 0))
{
  project = get_project_from_db(project_id);
  set_title("Handle Project\t" + (_("Project number: ") + project.get_project_no()) +
	    _("\tProject name: ") + project.get_project_name());
  set_icon_from_file("images/HaPr_high_80x100_ver2.gif");
  set_position(Gtk::WIN_POS_CENTER);
  add(*Gtk::manage(main_box));
  create_menu();
  create_view();

  set_size_request(200, 200);
  set_default_size(500, 300);
  set_position(Gtk::WIN_POS_CENTER);
  maximize();
  /*
  int no_act = 0;
  int no_on_time = 0;
  int no_finished = 0;
  int no_late = 0;
  std::list<Activity> act_list = project->get_activities();
  for(std::list<Activity>::iterator it = act_list.begin(); it!=act_list.end(); it++)
  {
    no_act++;
    if(it->is_finished())
      no_finished++;
    else if(it->is_late())
      no_late++;
    else
      no_on_time++;
  }

  std::stringstream s1, s2, s3, s4;
  s1 << no_act;
  no_act_label = new Gtk::Label(_("No of activities: ") + s1.str());
  s2 << no_on_time;
  on_time_label = new Gtk::Label(_("Activities on time: ") + s2.str());
  s3 << no_late;
  late_label = new Gtk::Label(_("Late activites: ") + s3.str());
  s4 << no_finished;
  finished_label = new Gtk::Label(_("Finished activities: ") + s4.str());
  Gtk::manage(no_act_label);
  Gtk::manage(on_time_label);
  Gtk::manage(late_label);
  Gtk::manage(finished_label);
*/
}

void ProjectWindow::update_view()
{
  set_title("Handle Project\t" + (_("Project number: ") + project.get_project_no()) +
	    _("\tProject name: ") + project.get_project_name());
}

void ProjectWindow::create_menu()
{
  // Create actions for menu and toolbar.
  refActionGroup = Gtk::ActionGroup::create();

  // File menu
  refActionGroup->add(Gtk::Action::create("MenuFile", _("_File")));

  // File submenu
  refActionGroup->add(Gtk::Action::create("FileExit", Gtk::Stock::QUIT, _("_Quit")),
		      sigc::mem_fun(*this, &ProjectWindow::on_action_file_exit));

  // Project menu
  refActionGroup->add(Gtk::Action::create("MenuProject", _("P_roject")));

  // Project submenu
  refActionGroup->add(Gtk::Action::create("ProjectActivities", Gtk::Stock::EDIT, _("Edit _activities...")),
		      sigc::mem_fun(*this, &ProjectWindow::on_action_project_activities));
  refActionGroup->add(Gtk::Action::create("ProjectProperties", Gtk::Stock::PROPERTIES, _("Pr_operties...")),
		      sigc::mem_fun(*this, &ProjectWindow::on_action_project_properties));

  // Help menu
  refActionGroup->add(Gtk::Action::create("MenuHelp", _("_Help")));

  // Help submenu
  refActionGroup->add(Gtk::Action::create("HelpHelp", Gtk::Stock::HELP));
  refActionGroup->add(Gtk::Action::create("HelpAbout", Gtk::Stock::ABOUT, _("About Handle Project")),
		      sigc::mem_fun(*this, &ProjectWindow::on_action_help_about));

  refUIManager = Gtk::UIManager::create();
  refUIManager->insert_action_group(refActionGroup);

  add_accel_group(refUIManager->get_accel_group());

  Glib::ustring ui_info =
    "<ui>"
    "  <menubar name='MenuBar'>"
    "    <menu action='MenuFile'>"
    "      <menuitem action='FileExit'/>"
    "    </menu>"
    "    <menu action='MenuProject'>"
    "      <menuitem action='ProjectProperties'/>"
    "      <separator/>"
    "      <menuitem action='ProjectActivities'/>"
    "    </menu>"
    "    <menu action='MenuHelp'>"
    "      <menuitem action='HelpHelp'/>"
    "      <menuitem action='HelpAbout'/>"
    "    </menu>"
    "  </menubar>"
    "  <toolbar name='ToolBar'>"
    "    <toolitem action='ProjectProperties'/>"
    "    <toolitem action='ProjectActivities'/>"
    "  </toolbar>"
    "</ui>";

  try
  {
    refUIManager->add_ui_from_string(ui_info);
  }
  catch(const Glib::Error& err)
  {
    new_error("Can not create menu and toolbar." + err.what(), "projectwindow.cpp",
	      "ProjectWindow::create_menu()");
  }

  Gtk::Widget* pMenubar = refUIManager->get_widget("/MenuBar");
  if(pMenubar)
    main_box->pack_start(*pMenubar, Gtk::PACK_SHRINK);
  Gtk::Widget* pToolbar = refUIManager->get_widget("/ToolBar");
  if(pToolbar)
    main_box->pack_start(*pToolbar, Gtk::PACK_SHRINK);
}

void ProjectWindow::create_view()
{
  int start_month = project.get_start_month();
  int start_year = project.get_start_year();
  int end_month = project.get_end_month();
  int end_year = project.get_end_year();

  scrollview.add(main_table_box);
  scrollview.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
  table_box.pack_start(activity_box, Gtk::PACK_SHRINK);
  table_box.pack_start(scrollview);
  main_box->pack_start(table_box);

  //The table
  Gtk::TreeModel::ColumnRecord *col_record = new Gtk::TreeModel::ColumnRecord();
  Gtk::TreeModelColumn<time_t> *col_id = new Gtk::TreeModelColumn<time_t>();
  Gtk::TreeModelColumn<std::string> *col_name = new Gtk::TreeModelColumn<std::string>();

  while(!((start_month > end_month) && (start_year == end_year)))
  {
    std::stringstream ss;
    ss << start_year << " - ";
    Gtk::Label *label = new Gtk::Label();
    if(start_month == 1)
      label->set_text(ss.str() + _("January")); 
    else if(start_month == 2)
      label->set_text(ss.str() + _("February"));
    else if(start_month == 3)
      label->set_text(ss.str() + _("March"));
    else if(start_month == 4)
      label->set_text(ss.str() + _("April"));
    else if(start_month == 5)
      label->set_text(ss.str() + _("May"));
    else if(start_month == 6)
      label->set_text(ss.str() + _("June"));
    else if(start_month == 7)
      label->set_text(ss.str() + _("July"));
    else if(start_month == 8)
      label->set_text(ss.str() + _("August"));
    else if(start_month == 9)
      label->set_text(ss.str() + _("September"));
    else if(start_month == 10)
      label->set_text(ss.str() + _("October"));
    else if(start_month == 11)
      label->set_text(ss.str() + _("November"));
    else
      label->set_text(ss.str() + _("December"));

    Gtk::VBox *box = new Gtk::VBox();
    box->set_border_width(1);
    box->pack_start(*label, Gtk::PACK_SHRINK);

    if(start_month == project.get_start_month())
      box->pack_start(*create_month_view(project.get_start_day(), start_month, start_year));
    else
      box->pack_start(*create_month_view(1, start_month, start_year));

    Gtk::manage(box);
    Gtk::manage(label);
    main_table_box.pack_start(*box, Gtk::PACK_SHRINK);
    
    if(start_month == 12)
    {
      start_month = 1;
      start_year++;
    }
    else
      start_month++;
  }

  col_record->add(*col_id);
  col_record->add(*col_name);

  treeview = new Gtk::TreeView();
  Gtk::manage(treeview);

  ref_tree_model = Gtk::ListStore::create(*col_record);
  treeview->set_model(ref_tree_model);
  treeview->set_grid_lines(Gtk::TREE_VIEW_GRID_LINES_BOTH);
  treeview->append_column(_("Activity"), *col_name);

  activity_box.set_border_width(2);
  Gtk::Label *act_label = new Gtk::Label(_("Activities"));
  Gtk::manage(act_label);
  activity_box.pack_start(*act_label, Gtk::PACK_SHRINK);
  activity_box.pack_start(*treeview);

  std::list<Activity> act_list = project.get_activities();
  Gtk::TreeModel::Row row;
  for(std::list<Activity>::iterator iter = act_list.begin(); iter != act_list.end(); iter++)
  {
    row = *(ref_tree_model->append());
    row[*col_id] = iter->get_id();
    row[*col_name] = iter->get_name();
  }
}

Gtk::TreeView * ProjectWindow::create_month_view(int starting_day, int month, int year)
{
  int end_day = project.get_end_day();
  int end_month = project.get_end_month();
  int end_year = project.get_end_year();
  int days_per_week = project.get_working_days_per_week();

  time_t time_now = time(NULL);
  struct tm *date_now = localtime(&time_now);
  int now_day = date_now->tm_mday;
  int now_month = date_now->tm_mon + 1;
  int now_year = date_now->tm_year + 1900;

  struct tm *tm_wday;
  time_t rawtime;
  time(&rawtime);
  tm_wday = localtime(&rawtime);
  tm_wday->tm_mday = starting_day;
  tm_wday->tm_mon = month - 1;
  tm_wday->tm_year = year - 1900;
  rawtime = mktime(tm_wday);
  tm_wday = localtime(&rawtime);
  int wday;
  if(tm_wday->tm_wday == 0)
    wday = 7;
  else
    wday = tm_wday->tm_wday;

  Gtk::TreeView *treeview = new Gtk::TreeView();
  Gtk::TreeModel::ColumnRecord *col_record = new Gtk::TreeModel::ColumnRecord();
  Gtk::manage(treeview);
  
  Gtk::TreeModelColumn<std::string> *col;
  Gtk::TreeModelColumn<std::string> *color;
  std::map<int, Gtk::TreeModelColumn<std::string>* > m_column;
  std::map<int, Gtk::TreeModelColumn<std::string>* > m_color;
  if(!(month > end_month && year > end_year))
  {
    int month_stop;
    if(month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || 
       month == 10 || month == 12)
      month_stop = 31;
    else if(month == 2)
    {
      if(year % 4 == 0)
	month_stop = 29;
      else
	month_stop = 28;
    }
    else if(month == end_month && year == end_year)
      month_stop = end_day;
    else
      month_stop = 30;
    int j=0;
    for(int i = starting_day; i <= month_stop; i++)
    {
      if(wday <= days_per_week)
      {
	std::stringstream ss;
	ss << i;
	col = new Gtk::TreeModelColumn<std::string>();
	col_record->add(*col);
	m_column[j] = col;
	color = new Gtk::TreeModelColumn<std::string>();
	col_record->add(*color);
	m_color[j] = color;
	treeview->append_column(ss.str(), *col);
	j++;
      }
      wday++;
      if(wday > 7)
	wday = 1;
    }
  }

  Glib::RefPtr<Gtk::ListStore> ref_tree_model = Gtk::ListStore::create(*col_record);
  treeview->set_model(ref_tree_model);
  treeview->set_grid_lines(Gtk::TREE_VIEW_GRID_LINES_BOTH);  

  int no_of_activities = project.get_activities().size();
  int mday = starting_day;

  Gtk::TreeModel::Row row;
  for(int i=0; i<no_of_activities; i++)
  {
    row = *(ref_tree_model->append());
    for(uint k=0; k<m_column.size(); k++)
    {
      row[*(m_column[k])] = " ";
      if(now_year > year)
	row[*(m_color[k])] = COLOR_HISTORY;
      else if(now_year == year && now_month > month)
	row[*(m_color[k])] = COLOR_HISTORY;
      else if(now_year == year && now_month == month && now_day > mday)
	row[*(m_color[k])] = COLOR_HISTORY;
      else
	row[*(m_color[k])] = COLOR_WHITE;
      Gtk::TreeViewColumn *view_col = treeview->get_column(k);
      Gtk::CellRenderer *renderer = view_col->get_first_cell_renderer();
      view_col->add_attribute(renderer->property_cell_background(), *(m_color[k]));
      mday++;
    }
  }

  return treeview;
}

void ProjectWindow::on_action_file_exit()
{
  delete this;
}

void ProjectWindow::on_action_project_properties()
{
  NewEditDialog edit(mainwindow , this, &project);
}

void ProjectWindow::on_action_help_about()
{
  About a;
  a.run();
}

void ProjectWindow::on_action_project_activities()
{
  ActivitiesWindow *actw  = new ActivitiesWindow(&project, this);
  actw->show_all();
}

ProjectWindow::~ProjectWindow()
{

}
