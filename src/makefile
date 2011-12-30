OBJS = files.o main.o xmlstr.o staff/staff.o
CC = g++
CFLAGS = -Wall -c
LFLAGS = -Wall

handleproject : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o handleproject

files.o : files.h files.cpp
	$(CC) $(CFLAGS) files.cpp

main.o : xmlstr.h files.h main.cpp
	$(CC) $(CFLAGS) main.cpp

xmlstr.o : xmlstr.h xmlstr.cpp
	$(CC) $(CFLAGS) xmlstr.cpp

staff/staff.o : saveobj.h staff/staff.h staff/staff.cpp
	$(CC) $(CFLAGS) staff/staff.cpp -o staff/staff.o

clean :
	\rm *.o *~ handleproject staff/*.o staff/*~