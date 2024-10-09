all: simulation.o shopQueue.o
	g++ simulation.cpp shopQueue.cpp -o run_simulation

shopQueue.o: shopQueue.cpp shopQueue.h 
	g++ -c shopQueue.cpp -o shopQueue.o

simulation.o: shopQueue.cpp
	g++ -c simulation.cpp -o simulation.o

clean:
	rm *.o run_simulation