OBJS = files.o main.o
CC = g++
CFLAGS = -Wall -c
LFLAGS = -Wall

handleproject : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o handleproject

files.o : files.h files.cpp
	$(CC) $(CFLAGS) files.cpp

main.o : files.h main.cpp
	$(CC) $(CFLAGS) main.cpp

clean :
	\rm *.o *~ handleproject