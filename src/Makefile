CC=g++
CFLAGS=-c -w
SOURCES=./src/main.cpp ./src/algo1.cpp ./src/algo2.cpp ./src/algo3.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=RAMmachine

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) 
    $(CC) $(OBJECTS) -o $@
    
.cpp.o:
    $(CC) $(CFLAGS) $< -o $@

#main.o:		./src/main.cpp
#				$(CC) $(CFLAGS) ./src/main.cpp -o ../bin/main.o -std=c++11


#algo1.o:  ./src/algo1.cpp
#				$(CC) $(CFLAGS) ./src/algo1.cpp -o ../bin/algo1.o -std=c++11
				
#algo2.o:  ./src/algo2.cpp
#				$(CC) $(CFLAGS) ./src/algo2.cpp -o ../bin/algo2.o -std=c++11
				
#algo3.o:  ./src/algo3.cpp
#				$(CC) $(CFLAGS) ./src/algo3.cpp -o ../bin/algo3.o -std=c++11

#RAMmachine: ../bin/main.o ../bin/algo1.o ../bin/algo2.o ../bin/algo3.o
#				$(CC) ../bin/main.o ../bin/algo1.o ../bin/algo2.o ../bin/algo3.o -o ./src/compiled/RAMmachine -std=c++11

clean:		  
				rm -rf ../bin/*.o RAMmachine