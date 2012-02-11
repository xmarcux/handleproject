OBJS = files.o main.o xmlstr.o date.o staff/staff.o staff/job.o project/project.o project/activity.o
CC = g++
CFLAGS = -Wall -c
LFLAGS = -Wall

handleproject : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o handleproject

files.o : project/project.h staff/staff.h saveobj.h files.h files.cpp
	$(CC) $(CFLAGS) files.cpp

main.o : project/project.h staff/job.h staff/staff.h xmlstr.h files.h main.cpp
	$(CC) $(CFLAGS) main.cpp

xmlstr.o : xmlstr.h xmlstr.cpp
	$(CC) $(CFLAGS) xmlstr.cpp

date.o : date.h date.cpp
	$(CC) $(CFLAGS) date.cpp

staff/staff.o : xmlstr.h saveobj.h staff/staff.h staff/staff.cpp
	$(CC) $(CFLAGS) staff/staff.cpp -o staff/staff.o

staff/job.o : xmlstr.h saveobj.h staff/job.h staff/job.cpp
	$(CC) $(CFLAGS) staff/job.cpp -o staff/job.o

project/project.o : xmlstr.h saveobj.h date.h staff/staff.h project/project.h project/project.cpp
	$(CC) $(CFLAGS) project/project.cpp -o project/project.o

project/activity.o : xmlstr.h saveobj.h date.h project/activity.h project/activity.cpp
	$(CC) $(CFLAGS) project/activity.cpp -o project/activity.o

clean :
	\rm *.o *~ handleproject staff/*.o staff/*~ project/*.o project/*~