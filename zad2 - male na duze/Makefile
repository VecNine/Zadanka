CC = gcc
CFLAGS = -Wall
TARGET = program_litery

all: $(TARGET)

$(TARGET): mainLitery.o litery.o
	$(CC) $(CFLAGS) mainLitery.o litery.o -o $(TARGET)

mainLitery.o: mainLitery.c litery.h
	$(CC) $(CFLAGS) -c mainLitery.c

litery.o: litery.c litery.h
	$(CC) $(CFLAGS) -c litery.c

clean:
	rm -f *.o $(TARGET) text_cel.txt