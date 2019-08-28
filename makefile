CPP=g++ -g 
all: cache-sim


cache-sim: Driver.o cache-sim.o
	$(CPP) Driver.o cache-sim.o -o cache-sim

cache-sim.o: cache-sim.cpp
	$(CPP)  -c  cache-sim.cpp

Driver.o: Driver.cpp
	$(CPP)  -c  Driver.cpp

# Specify the object files and executables that are generated
# and need to be removed to re-compile the whole thing

clean:
	rm -f *.o *~ cache-sim output.txt outputFile.txt

