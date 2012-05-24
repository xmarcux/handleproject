OBJS = files.o main.o xmlstr.o date.o staff/staff.o staff/job.o \
project/project.o project/activity.o ui/mainwindow.o ui/about.o \
ui/neweditdialog.o ui/projectwindow.o ui/splashwindow.o
CC = g++
CFLAGS = -Wall -c
LFLAGS = -Wall
GTKFLAGS = `pkg-config gtkmm-2.4 --cflags --libs`

handleproject : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o handleproject $(GTKFLAGS)

files.o : project/project.h project/activity.h staff/staff.h saveobj.h files.h files.cpp
	$(CC) $(CFLAGS) files.cpp

main.o : ui/mainwindow.h project/project.h staff/job.h staff/staff.h xmlstr.h files.h main.cpp
	$(CC) $(CFLAGS) main.cpp $(GTKFLAGS)

xmlstr.o : xmlstr.h xmlstr.cpp
	$(CC) $(CFLAGS) xmlstr.cpp

date.o : date.h date.cpp
	$(CC) $(CFLAGS) date.cpp

staff/staff.o : xmlstr.h saveobj.h staff/staff.h staff/staff.cpp
	$(CC) $(CFLAGS) staff/staff.cpp -o staff/staff.o

staff/job.o : xmlstr.h saveobj.h staff/job.h staff/job.cpp
	$(CC) $(CFLAGS) staff/job.cpp -o staff/job.o

project/project.o : xmlstr.h saveobj.h date.h files.h staff/staff.h project/activity.h project/project.h project/project.cpp
	$(CC) $(CFLAGS) project/project.cpp -o project/project.o

project/activity.o : xmlstr.h saveobj.h date.h project/activity.h project/activity.cpp
	$(CC) $(CFLAGS) project/activity.cpp -o project/activity.o

ui/mainwindow.o : files.h project/project.h ui/neweditdialog.h ui/about.h ui/projectwindow.h ui/mainwindow.h ui/mainwindow.cpp
	$(CC) $(CFLAGS) ui/mainwindow.cpp -o ui/mainwindow.o $(GTKFLAGS)

ui/about.o: ui/about.h ui/about.cpp
	$(CC) $(CFLAGS) ui/about.cpp -o ui/about.o $(GTKFLAGS)

ui/neweditdialog.o : ui/mainwindow.h ui/projectwindow.h files.h project/project.h ui/neweditdialog.h ui/neweditdialog.cpp
	$(CC) $(CFLAGS) ui/neweditdialog.cpp -o ui/neweditdialog.o $(GTKFLAGS)

ui/projectwindow.o : files.h project/project.h ui/projectwindow.h ui/about.h ui/neweditdialog.h ui/mainwindow.h ui/projectwindow.cpp
	$(CC) $(CFLAGS) ui/projectwindow.cpp -o ui/projectwindow.o $(GTKFLAGS)

ui/splashwindow.o : ui/splashwindow.h ui/splashwindow.cpp
	$(CC) $(CFLAGS) ui/splashwindow.cpp -o ui/splashwindow.o $(GTKFLAGS)

clean :
	\rm *.o *~ handleproject staff/*.o staff/*~ project/*.o project/*~ ui/*.o ui/*~