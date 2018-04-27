CC = gcc
TARGET = rbp
OBJS = rbp.o
CFLAGS = -std=c11
$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)
main.o: rbp.c
	$(CC) -c rbp.c

debug:
	$(CC)  rbp.c -DDEBUG -std=c11 -o $(TARGET)

clean:
	/bin/rm -f *.o* $(TARGET)