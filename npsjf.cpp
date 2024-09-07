#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>  // For INT_MAX

using namespace std;

// Structure to store process information
struct Process {
    int pid;        // Process ID
    int arrival;    // Arrival time
    int burst;      // Burst time (CPU execution time)
    int start;      // Start time (calculated)
    int finish;     // Finish time (calculated)
    int waiting;    // Waiting time (calculated)
    int turnaround; // Turnaround time (calculated)
    bool completed; // Flag to check if the process is completed
};

// Function to simulate Non-Preemptive SJF scheduling
void simulateSJF(vector<Process>& processes) {
    int n = processes.size();
    int currentTime = 0;
    int completed = 0;

    // Initialize all processes as not completed
    for (int i = 0; i < n; i++) {
        processes[i].completed = false;
    }

    while (completed != n) {
        // Find the process with the minimum burst time among the arrived processes
        int idx = -1;
        int minBurst = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (processes[i].arrival <= currentTime && !processes[i].completed) {
                if (processes[i].burst < minBurst) {
                    minBurst = processes[i].burst;
                    idx = i;
                }
                // If burst times are equal, use arrival time to break the tie
                else if (processes[i].burst == minBurst) {
                    if (processes[i].arrival < processes[idx].arrival) {
                        idx = i;
                    }
                }
            }
        }

        if (idx != -1) {
            // Process found
            processes[idx].start = currentTime;
            processes[idx].finish = processes[idx].start + processes[idx].burst;
            processes[idx].turnaround = processes[idx].finish - processes[idx].arrival;
            processes[idx].waiting = processes[idx].start - processes[idx].arrival;
            processes[idx].completed = true;
            completed++;
            currentTime = processes[idx].finish;
        } else {
            // No process is available at current time, increment time
            currentTime++;
        }
    }
}

// Function to display the process information
void displayProcesses(const vector<Process>& processes) {
    cout << "\nPID\tArrival\tBurst\tStart\tFinish\tWaiting\tTurnaround\n";
    for (const auto& p : processes) {
        cout << p.pid << "\t" << p.arrival << "\t" << p.burst << "\t" << p.start << "\t"
             << p.finish << "\t" << p.waiting << "\t" << p.turnaround << "\n";
    }
}

// Main function
int main() {
    int n;  // Number of processes

    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> processes(n);

    // Input arrival and burst times for all processes
    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        cout << "\nEnter arrival time for process " << i + 1 << ": ";
        cin >> processes[i].arrival;
        cout << "Enter burst time for process " << i + 1 << ": ";
        cin >> processes[i].burst;
    }

    // Sort processes based on arrival time (optional for SJF but helpful for consistent output)
    sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        return a.arrival < b.arrival;
    });

    // Simulate Non-Preemptive SJF scheduling
    simulateSJF(processes);

    // Display the process information
    displayProcesses(processes);

    return 0;
}
