# Makefile for Separate Compilation Example

# *****************************************************
# Parameters to control Makefile operation

CXX = g++
CXXFLAGS = -pthread

# ****************************************************
# Entries to bring the executable up to date

main: main.o configuration.o communication.o cli.o
	$(CXX) $(CXXFLAGS) -o main main.o configuration.o  communication.o cli.o

main.o: main.cpp def.h
	$(CXX)  -c main.cpp 

configuration.o: configuration.cpp def.h
	$(CXX) -c configuration.cpp 

# executer.o: executer.cpp def.h
# 	$(CXX) $(CXXFLAGS) -c executer.cpp 

communication.o: communication.cpp def.h
	$(CXX) $(CXXFLAGS) -c communication.cpp 

cli.o: cli.cpp def.h
	$(CXX) -c cli.cpp 


clean:
	rm ./*.o main

debug: main_debug configuration_debug communication_debug cli_debug
	$(CXX) $(CXXFLAGS) -o main main.o configuration.o  communication.o cli.o -g
	gdb ./main

main_debug: main.cpp def.h
	$(CXX)  -c main.cpp -g

configuration_debug: configuration.cpp def.h
	$(CXX) -c configuration.cpp -g

communication_debug: communication.cpp def.h
	$(CXX) $(CXXFLAGS) -c communication.cpp -g


cli_debug: cli.cpp def.h
	$(CXX) -c cli.cpp -g