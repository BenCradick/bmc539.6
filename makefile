CC = gcc
TARGET = sim_checkout
OBJS = sim_checkout.o
$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)
main.o: sim_checkout.c
	$(CC) -c sim_checkout.c


clean:
	/bin/rm -f *.o* $(TARGET)
