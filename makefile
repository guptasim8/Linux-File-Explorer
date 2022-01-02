INCLUDE = header.h
CC = g++
CFLAG = -std=c++2a -Wall
OBJS = DirectoryOperations.o CommandMode.o FileOperations.o main.o
%.o: %.cpp $(INCLUDE)
	$(CC) $(CFLAG) -c -o $@ $<
main: $(OBJS)
	$(CC) $(CFLAG) -o $@ $^
clean:
	-rm -rf *.o main
