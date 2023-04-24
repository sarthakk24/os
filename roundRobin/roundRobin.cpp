#include<iostream>
using namespace std;

void findWaitingTime(int processes[], int n, int bt[], int wt[], int quantum) {
    int rem_bt[n];
    for (int i = 0 ; i < n ; i++)
        rem_bt[i] = bt[i];
    int t = 0;
    while (1) {
        bool done = true;
        for (int i = 0 ; i < n; i++) {
            if (rem_bt[i] > 0) {
                done = false;
                if (rem_bt[i] > quantum) {
                    t += quantum;
                    rem_bt[i] -= quantum;
                } else {
                    t += rem_bt[i];
                    wt[i] = t - bt[i];
                    rem_bt[i] = 0;
                }
            }
        }
        if (done == true) break;
    }
}

void findTurnAroundTime(int processes[], int n, int bt[], int wt[], int tat[]) {
    for (int i = 0; i < n ; i++) {
        tat[i] = bt[i] + wt[i];
    }
}

void findavgTime(int processes[], int n, int bt[], int quantum) {
    int wt[n], tat[n], total_wt = 0, total_tat = 0;
    findWaitingTime(processes, n, bt, wt, quantum);
    findTurnAroundTime(processes, n, bt, wt, tat);
    cout << "PN\t" << " \tBT " << " WT " << " \tTAT\n";
    for (int i = 0; i < n; i++) {
        total_wt = total_wt + wt[i];
        total_tat = total_tat + tat[i];
        cout << " " << i+1 << "\t\t" << bt[i] << "\t " << wt[i] << "\t\t " << tat[i] << endl;
    }
    cout << "Average waiting time = " << (float)total_wt / (float)n;
    cout << "\nAverage turn around time = " << (float)total_tat / (float)n << endl;
}

int main() {
    int processes[] = { 1, 2, 3 };
    int n = sizeof processes / sizeof processes[0];
    int burst_time[] = { 10, 5, 8 };
    int quantum = 2;
    findavgTime(processes, n, burst_time, quantum);
    return 0;
}

// Algorithm:
// 1. Used for time sharing systems
// 2. Pre-emption is added which enables system to switch between processes.
// 3. A fixed time is allotted to each process, called quantum, for execution.
// 4. A process is executed for the given time period that process us pre-empted and another
// process executes for the given time period.
// 5. Context switching is used to save states of pre-empted processes.
// 6. Enter total number of processes, enter their arrival time and burst time.
// 7. Enter the time quantum for each process.
// 8. Print the burst time, waiting time for each process.
// 9. Calculate and print the total waiting time and total turnaround time.