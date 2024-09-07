#include <iostream>
#include <vector>
#include <algorithm>  // For sorting
using namespace std;

// Structure to store process information
struct Process {
    int pid;      // Process ID
    int arrival;  // Arrival time
    int burst;    // Burst time (CPU execution time)
    int start;    // Start time (calculated)
    int finish;   // Finish time (calculated)
    int waiting;  // Waiting time (calculated)
    int turnaround;  // Turnaround time (calculated)
};

// Function to calculate and simulate FCFS scheduling
void simulateFCFS(vector<Process>& processes) {
    int currentTime = 0;  // Keeps track of the current time

    for (auto& p : processes) {
        // Start time of the process is either the current time or the arrival time, whichever is greater
        p.start = max(currentTime, p.arrival);

        // Finish time is start time + burst time
        p.finish = p.start + p.burst;

        // Turnaround time = Finish time - Arrival time
        p.turnaround = p.finish - p.arrival;

        // Waiting time = Turnaround time - Burst time
        p.waiting = p.turnaround - p.burst;

        // Update the current time for the next process
        currentTime = p.finish;
    }
}

// Function to display the process information
void displayProcesses(const vector<Process>& processes) {
    cout << "PID\tArrival\tBurst\tStart\tFinish\tWaiting\tTurnaround\n";
    for (const auto& p : processes) {
        cout << p.pid << "\t" << p.arrival << "\t" << p.burst << "\t" << p.start << "\t"
             << p.finish << "\t" << p.waiting << "\t" << p.turnaround << "\n";
    }
}


int main() {
    int n;  // Number of processes

    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> processes(n);

    // Input arrival and burst times for all processes
    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        cout << "Enter arrival time for process " << i + 1 << ": ";
        cin >> processes[i].arrival;
        cout << "Enter burst time for process " << i + 1 << ": ";
        cin >> processes[i].burst;
    }

    // Sort processes based on arrival time
    sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        return a.arrival < b.arrival;
    });

    // Simulate FCFS scheduling
    simulateFCFS(processes);

    // Display the process information
    displayProcesses(processes);

    return 0;
}
