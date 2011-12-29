OBJS = files.o main.o
CC = g++
CFLAGS = -Wall -c
LFLAGS = -Wall

handleproject : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o handleproject

files.o : files.h
	$(CC) $(CFLAGS) files.cpp

main.o : files.h
	$(CC) $(CFLAGS) main.cpp

clean :
	\rm *.o *~ handleproject