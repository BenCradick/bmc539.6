CC = gcc
TARGET = generate_customers
OBJS = generate_customers.o
CFLAGS = -std=c11
$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)
main.o: generate_customers.c
	$(CC) -c generate_customers.c

debug:
	$(CC)  generate_customers.c -DDEBUG -std=c11 -o $(TARGET)

clean:
	/bin/rm -f *.o* $(TARGET)