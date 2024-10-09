John Baldor 
2/29/2024


This program models a coffee shop with 1 or more checkout lines and cashiers. At random intervals, customers will enter the store and join the checkout lines. As time goes on, customers will reach the front of the queue and make their purchase before leaving the queue. In command line arguments input a random number seed, time for the simulation to run, arrival probability, customer finishing probability, the number of queues, and an output file, the program will output the data of the customers and checkout lines.


To compile the program, run the command: 
g++ simulation.cpp shopQueue.cpp -o run_simulation.o


To run the program, run the command:
./run_simulation seed total_min arrive_prob order_prob queues outputFile




Sources: I worked alone on this assignment
