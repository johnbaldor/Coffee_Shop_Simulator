#include <iostream>
#include <iomanip>
#include <fstream>
#include "customer.h"
#include "shopQueue.h"
#include <vector>
#include<list>

using namespace std;

int main(int argc, char *argv[]) {
    // Check if the correct number of command-line arguments is provided
    if (argc != 7){ 
        cout << "Error: Wrong number of arguments!" << endl;
        cout << "Usage: ./run_simulation <seed> <total_min> <arrival_prob> <order_prob> <num_queues> <outputFile>" << endl;
        return 0;
        
    }
    else{
    // Convert command-line arguments to varibles
    int seed = atoi(argv[1]); // Seed for random number
    srand(seed);
    int total_min = atoi(argv[2]); // Total simulation time in minutes
    float arrival_Prob = atof(argv[3]); // Probability of a customer arriving each minute
    float order_Prob = atof(argv[4]); // Probability of a customer placing an order
    int queues = atoi(argv[5]); // Number of checkout queues
    ofstream outputFile(argv[6]); // Output file to store customer data

    cout << "Welcome to Gompei Coffee Shop!" << endl;
    cout << "-- # of Checkout Queues: " << queues << " --" << endl;

    vector<ShopQueue> Queues(queues); //checkout queues
    Queues[0].addNewCustomer(0, 0, 0, 0); //add first customer
    cout << "New customer at t = " << 0 << endl; 


    vector<shared_ptr<Customer>> checked_out; // vector of customers already checked out
    //initalize varibles 
    int IDcounter = 0;
    vector<int> registerNums;
    int numCustomersServed =0;
    int customersPerRegister = 0;

    //start of simulation
    for (int currentTime = 0; currentTime < total_min; ++currentTime) {
        // check for new costomer
        if (static_cast<float>(rand()) / RAND_MAX < arrival_Prob) {

            int shortestQueueLength = Queues[0].getLength(); 
            int shortestQueue = 0; // find index of shorest queue in list of queues

            //find shortest queue
            for (int i = 1; i < queues; ++i) { 
                if (Queues[i].getLength() < shortestQueueLength) {
                    shortestQueue = i;
                    shortestQueueLength = Queues[i].getLength();    
                }}
            IDcounter += 1; //increase id number for new customer
            // Add customer to the shortest queue
            Queues[shortestQueue].addNewCustomer(currentTime, currentTime, 0, IDcounter);
            
            cout << "New customer at t = " << currentTime << endl;
        }
        
        for (int i = 0; i < queues; ++i) { //cycel through queues 
            if (!Queues[i].isEmpty()) {

                if ((float) rand() / RAND_MAX < order_Prob) { 
                    registerNums.push_back(i); // record register number
                    numCustomersServed +=1; //record amount of customers served 
                    shared_ptr<Customer> completedCustomer = Queues[i].removeFrontCustomer(); //remove customer from queue
                    completedCustomer->completedTime = currentTime; //update customer completed time 
                    cout << "Customer #" << completedCustomer->ID << " was served from t = " << completedCustomer->startTime << " to " << currentTime << "." << endl;
                    checked_out.push_back(completedCustomer); // add customer to completed
                    
                     if (!Queues[i].isEmpty()) {
                        Queues[i].peekFrontCustomer()->startTime = completedCustomer->completedTime; //update next customers start time 
                    
                }}

        }}}

       
        
        outputFile << setw(8) << "ID" << setw(8) << "Arrive" << setw(8) << "Start" << setw(8) << "Leave" << endl; //header for output file 

        for (const auto& customer : checked_out) { //customer info to output file
            outputFile << setw(8) << customer->ID << setw(8) << customer->arrivalTime << setw(8) << customer->startTime << setw(8) << customer->completedTime << endl;
         }

    // Print how many customers remain in Queues
         for (int i = 0; i < queues; ++i) {
            cout << "After " << total_min << " minutes, " << Queues[i].getLength() << " customers remain in queue #" << i << endl;}

    // Print how many customers each cashier served
        for (int i = 0; i < queues; ++i) {
            customersPerRegister = 0;
            for(int j = 0; j< numCustomersServed; ++j){
                if(i == registerNums[j]){
                    customersPerRegister += 1;
                }

            }
            cout << "Cashier " << i << " served " << customersPerRegister << " customers." << endl;
         }
         
         return 0;
}}