#ifndef BANKERS_ALGORITHM_H
#define BANKERS_ALGORITHM_H

#include <vector>
#include <pthread.h>
#include "Process.h"
using namespace std;

class BankersAlgorithm {
private:
    int numResources;
    vector<int> available;      // Available resources
    vector<int> maxResources;   // Total resources in system
    vector<Process*> processes; // All processes
    vector<int> safeSequence;   // Last computed safe sequence
    vector<int> blockedProcesses; // Blocked process IDs
    
    pthread_mutex_t resourceMutex;
    
    // Helper functions
    bool isSafe(const vector<int>& tempAvailable);
    bool canAllocate(const Process& p, const vector<int>& tempAvailable);
    
public:
    BankersAlgorithm(int numResourceTypes, const vector<int>& totalResources);
    ~BankersAlgorithm();
    
    // Check if resource allocation is safe
    bool requestResources(Process* process);
    
    // Release resources when process completes
    void releaseResources(Process* process);
    
    // Display system state
    void displaySystemState();
    
    // Get safe sequence
    vector<int> getSafeSequence() const;
    
    // Get blocked processes
    vector<int> getBlockedProcesses() const;
    
    // Add process to system
    void addProcess(Process* process);
    
    // Remove process from system
    void removeProcess(Process* process);
};

#endif
