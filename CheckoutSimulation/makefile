CC = gcc
CFLAGS = -std=c99
TARGET = sim_checkout
OBJS = sim_checkout.o generate_customers.o
$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)
sim_checkout.o: sim_checkout.c
	$(CC) -c sim_checkout.c
generate_customers.o: GenerateCustomers/generate_customers.c
	$(CC) $(CFLAGS) -c GenerateCustomers/generate_customers.c
debug:
	$(CC)  sim_checkout.c -DDEBUG -std=c99 -o $(TARGET)

clean:
	/bin/rm -f *.o $(TARGET)
