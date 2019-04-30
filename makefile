CFLAGS = -O
CC = g++ -std=c++11

RunAll: Source.o EachLine.o OpTable.o
	$(CC) $(CFLAGS) -o RunAll Source.o EachLine.o OpTable.o

Source.o: Source.cpp
	$(CC) $(CFLAGS) -c Source.cpp

EachLine.o: EachLine.cpp
	$(CC) $(CFLAGS) -c EachLine.cpp

OpTable.o: OpTable.cpp
	$(CC) $(CFLAGS) -c OpTable.cpp

clean:
	rm -f core *.o 