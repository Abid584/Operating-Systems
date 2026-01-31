#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <vector>
#include "Process.h"
#include "BankersAlgorithm.h"
using namespace std;

class Scheduler {
private:
    vector<Process*> processes;
    vector<GanttEntry> ganttChart;
    int timeQuantum;
    BankersAlgorithm* banker;
    
    vector<int> getReadyProcesses(int currentTime, vector<bool>& completed);
    void priorityScheduling();
    void roundRobinScheduling();
    
public:
    Scheduler();
    ~Scheduler();
    
    void addProcess(Process* process);
    void setBanker(BankersAlgorithm* bankerAlgo);
    void executeScheduling();
    void setTimeQuantum(int quantum);
    
    void displayProcessTable();
    void displayGanttChart();
    void displayStatistics();
    
    int getProcessCount();
    vector<Process*>& getProcesses();
};

#endif
