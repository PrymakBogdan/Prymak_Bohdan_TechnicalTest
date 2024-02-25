CC = g++
CFLAGS = -Wall

all: FindFile.o libFindFile.a FindFileProg

FindFileProg: main.cpp libFindFile.a
	$(CC) $(CFLAGS) main.cpp -L. -lFindFile -o FindFileProg

FindFile.o: FindFile.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

libFindFile.a: FindFile.o
	ar rcs $@ $^
	rm -f FindFile.o

clean:
	rm -f FindFile.o libFindFile.a FindFileProg
