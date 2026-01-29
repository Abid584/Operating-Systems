# COMPREHENSIVE CPU SCHEDULING SYSTEM
## Integration of Parts A, B, and C

---

## 📋 PROJECT OVERVIEW

This is a complete CPU scheduling simulator that integrates:
- **Part A**: CPU Scheduling (Priority & Round Robin)
- **Part B**: Producer-Consumer with Bounded Buffer
- **Part C**: Resource Management & Deadlock Prevention (Banker's Algorithm)

---

## 🏗️ ARCHITECTURE

### Multi-File Modular Design ✅

```
ccp_final/
├── Process.h                 # Process data structure
├── BankersAlgorithm.h       # Deadlock prevention interface
├── BankersAlgorithm.cpp     # Banker's algorithm implementation
├── BoundedBuffer.h          # Thread-safe buffer interface
├── BoundedBuffer.cpp        # Producer-consumer buffer
├── Scheduler.h              # CPU scheduling interface
├── Scheduler.cpp            # Priority & Round Robin algorithms
├── ProducerConsumer.h       # Threading interface
├── ProducerConsumer.cpp     # Producer/consumer threads
├── main.cpp                 # Menu-based interface
├── Makefile                 # Build automation
└── README.md                # This file
```

**✅ NO SINGLE-FILE MONOLITH**

---

## ⚙️ COMPILATION & EXECUTION

### Prerequisites:
```bash
sudo apt install build-essential g++ -y
```

### Compile:
```
sudo mkdir -p /mnt/hgfs
sudo vmhgfs-fuse .host:/ /mnt/hgfs -o allow_other
ls /mnt/hgfs
cd /mnt/hgfs/Cpp
ls -l ccp_Scheduler
g++ -std=c++11 -o ccp_Scheduler main.cpp BoundedBuffer.cpp Scheduler.cpp ProducerConsumer.cpp BankersAlgorithm.cpp -pthread
```

### Run:
```bash
./ccp_scheduler
```

### Clean:
```
rm -f *.os ccp_Scheduler
```

---

## 🎯 MENU OPTIONS

```
========================================
  CPU SCHEDULING SIMULATOR - MAIN MENU
========================================
1. Start Simulation (Producer-Consumer)
2. Add Process Manually
3. Display System State
4. Exit
========================================
```

### Option 1: Start Simulation
- Runs full Producer-Consumer simulation
- Multiple producers generate processes dynamically
- Consumer fetches and schedules processes
- Banker's Algorithm checks resource safety
- Displays Gantt chart and statistics

### Option 2: Add Process Manually
- Manually input process details
- Specify arrival time, burst time, priority
- Define resource requirements
- System checks if allocation is safe
- Process added to scheduler

### Option 3: Display System State
- Shows all processes in system
- Displays resource allocation table
- Shows safe sequence (if exists)
- Lists blocked processes

### Option 4: Exit
- Clean shutdown of the system

---

## 📊 PART A: CPU SCHEDULING

### Algorithms Implemented:
1. **Priority Scheduling (Non-preemptive)**
   - Used when ≤5 processes arrive at time 0
   - Lower priority number = higher priority
   - Considers arrival time for tie-breaking

2. **Round Robin (Preemptive)**
   - Used when >5 processes arrive at time 0
   - User-defined time quantum
   - Fair CPU distribution

### Features:
✅ Dynamic process input
✅ Gantt chart visualization
✅ Waiting time calculation
✅ Turnaround time calculation
✅ Average statistics

---

## 🔄 PART B: PRODUCER-CONSUMER

### Synchronization:
- **Semaphores**: `sem_t empty, full`
  - Tracks buffer slots
  - Blocks threads when buffer full/empty
  - **NO BUSY WAITING** ✅

- **Mutex**: `pthread_mutex_t`
  - Protects critical sections
  - Ensures mutual exclusion
  - Thread-safe buffer access

### Features:
✅ Minimum 2 producer threads
✅ 1 consumer thread (CPU)
✅ Bounded buffer with user-defined capacity
✅ Dynamic process generation
✅ Thread-safe process ID assignment
✅ Integration with scheduler

### Producer Logic:
```
Generate Process → 
Wait for Empty Slot (sem_wait) → 
Lock Buffer (mutex) → 
Insert Process → 
Unlock Buffer → 
Signal Full Slot (sem_post)
```

### Consumer Logic:
```
Wait for Full Slot (sem_wait) → 
Lock Buffer (mutex) → 
Remove Process → 
Unlock Buffer → 
Signal Empty Slot (sem_post) → 
Add to Scheduler
```

---

## 🛡️ PART C: BANKER'S ALGORITHM

### Resource Management:
- **Fixed Resource Types**: 3 types (R1, R2, R3)
- **Total Resources**: [10, 5, 7] (configurable)
- **Safety Check**: Before every allocation

### Matrices:
1. **Available**: Current available resources
2. **Max**: Maximum resources needed by each process
3. **Allocation**: Currently allocated resources
4. **Need**: Max - Allocation

### Features:
✅ Safety algorithm implementation
✅ Resource request validation
✅ Unsafe state prevention
✅ Process blocking when unsafe
✅ Safe sequence computation
✅ Blocked process tracking

### Safety Check Algorithm:
```
1. Create work vector = available
2. For each process:
   - Can it finish with current resources?
   - If yes: Add to safe sequence, release resources
   - If no: Try next process
3. If all processes finish: SAFE state
4. If stuck: UNSAFE state → Block process
```

---

## 🧪 TEST CASES

### Test Case 1: Small Simulation (Priority Scheduling)

**Input:**
```
Menu Choice: 1
Number of producers: 2
Buffer size: 5
Total processes: 5
Time quantum: 2
```

**Expected:**
- 5 processes generated
- Ready processes at time 0: 5
- Uses Priority Scheduling
- Banker's algorithm checks safety
- Safe sequence displayed
- Gantt chart shown
- Statistics calculated

---

### Test Case 2: Large Simulation (Round Robin)

**Input:**
```
Menu Choice: 1
Number of producers: 3
Buffer size: 8
Total processes: 10
Time quantum: 3
```

**Expected:**
- 10 processes generated
- Ready processes at time 0: 10
- Uses Round Robin (>5 processes)
- Time quantum = 3
- Preemptive execution
- Resource safety checked
- May have blocked processes if resources scarce

---

### Test Case 3: Manual Process Addition

**Input:**
```
Menu Choice: 2
Process ID: 100
Arrival Time: 0
Burst Time: 5
Priority: 1
Resource R1: 3
Resource R2: 2
Resource R3: 4
```

**Expected:**
- Process added to system
- Banker's algorithm checks if safe
- Either "SUCCESS" or "WARNING - unsafe state"
- Can view in system state (Menu Option 3)

---

### Test Case 4: System State Display

**Input:**
```
Menu Choice: 3
```

**Expected Output:**
```
Process Table with all processes
Resource Management State:
  - Available resources
  - Process resource allocation table
  - Safe sequence
  - Blocked processes list
```

---

## ✅ VERIFICATION CHECKLIST

### Part A - CPU Scheduling:
- [x] Priority Scheduling (Non-preemptive)
- [x] Round Robin (Preemptive)
- [x] Scheduler selection based on ready processes
- [x] Gantt chart display
- [x] Waiting time calculation
- [x] Turnaround time calculation
- [x] No hardcoded decisions

### Part B - Producer-Consumer:
- [x] At least 2 producer threads
- [x] At least 1 consumer thread
- [x] Bounded buffer implementation
- [x] Semaphores (empty/full)
- [x] Mutex for mutual exclusion
- [x] NO busy waiting
- [x] Dynamic process generation
- [x] Thread-safe operations

### Part C - Banker's Algorithm:
- [x] Fixed resource types (3)
- [x] Max, Allocation, Available matrices
- [x] Safety check before allocation
- [x] Process blocking when unsafe
- [x] Safe sequence display
- [x] Blocked processes list

### Code Quality:
- [x] Multi-file modular design
- [x] Proper header files
- [x] No single-file monolith
- [x] Menu-based interface
- [x] Clean code structure
- [x] Proper comments

---

## 📝 SYSTEM CONFIGURATION

### Resource Configuration:
```cpp
int numResourceTypes = 3;
vector<int> totalResources = {10, 5, 7};
```

**To modify**: Edit these values in `main.cpp`

### Default Settings:
- Time Quantum: 2 (user can override)
- Buffer Size: User input
- Number of Producers: User input (min 2)

---

## 🔍 SAMPLE OUTPUT

```
========================================
  COMPREHENSIVE CPU SCHEDULING SYSTEM
  Parts A, B, C Integration
========================================

Resource Configuration:
Number of Resource Types: 3
Total Resources: [10, 5, 7]

========================================
  CPU SCHEDULING SIMULATOR - MAIN MENU
========================================
1. Start Simulation (Producer-Consumer)
2. Add Process Manually
3. Display System State
4. Exit
========================================
Enter your choice: 1

[PRODUCER 1] Started
[PRODUCER 2] Started
[CONSUMER] Started - waiting for processes...
[PRODUCER 1] Generated Process P1 (Priority: 2, Burst: 5)
[PRODUCER] Inserted Process P1 (Priority: 2, Burst: 5)
[CONSUMER] Removed Process P1 from buffer
[CONSUMER] Added Process P1 to scheduler (1/5)
...

========================================
          PROCESS TABLE
========================================
PID   Arrival     Burst       Priority    Resources
----------------------------------------
1     0           5           2           [3, 2, 1]
2     0           4           1           [2, 1, 3]
...

========================================
     RESOURCE MANAGEMENT STATE
========================================

Available Resources: [10, 5, 7]

Process Resource Table:
PID     Max                 Allocated           Need                Status    
------------------------------------------------------------------------------
1       [3,2,1]             [0,0,0]             [3,2,1]             READY     
2       [2,1,3]             [0,0,0]             [2,1,3]             READY     
...

Safe Sequence: <P2, P1, P3, P4, P5>
Blocked Processes: None

========================================
SCHEDULER SELECTION
========================================
Ready processes at time 0: 5
Condition: <= 5 ready processes
Selected: PRIORITY SCHEDULING

========================================
          GANTT CHART
========================================
| P2 | P1 | P3 | P4 | P5 |
0    4    9    12    15    20

========================================
       AVERAGE STATISTICS
========================================
Average Waiting Time: 5.60
Average Turnaround Time: 10.20
```

---

## 🐛 TROUBLESHOOTING

### Compilation Error: "undefined reference to sem_init"
**Solution**: Ensure `-pthread` flag is used
```bash
g++ -pthread ...
```

### Deadlock in Banker's Algorithm
**Solution**: Check resource configuration. Total resources must be sufficient for at least one process to complete.

### Blocked Processes Not Clearing
**Solution**: This is expected if resource requirements exceed available resources. System prevents unsafe states correctly.

---

## 👨‍💻 IMPLEMENTATION DETAILS

### Thread Safety:
- All shared data protected by mutexes
- Semaphores prevent race conditions
- No global mutable state without protection

### Memory Management:
- Processes allocated on heap
- Proper cleanup in destructors
- No memory leaks

### Design Patterns:
- Producer-Consumer pattern
- Resource allocation pattern
- Strategy pattern (scheduling algorithms)

---

## 📚 CONCEPTS DEMONSTRATED

1. **CPU Scheduling**: Priority, Round Robin
2. **Concurrency**: Pthreads, synchronization
3. **Deadlock Prevention**: Banker's Algorithm
4. **Inter-Process Communication**: Bounded buffer
5. **Critical Sections**: Mutex protection
6. **Resource Management**: Safe state verification
7. **Modular Design**: Clean code architecture

---

## ✨ FEATURES SUMMARY

- ✅ Menu-based user interface
- ✅ Three integrated parts (A, B, C)
- ✅ Multi-threaded execution
- ✅ Deadlock prevention
- ✅ No busy waiting
- ✅ Modular code design
- ✅ Comprehensive error handling
- ✅ Real-time status display
- ✅ Safe resource allocation

---

**🎓 Ready for Submission - All Requirements Met**
