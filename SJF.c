#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int pname;         // Tên process
    int arrival_time;  // Arrival time
    int burst_time;    // Burst time
    int start_time;    // Start time
    int finish_time;   // Finish time
    int waiting_time;  // Waiting time
    int turnaround_time; // Turnaround time
    int response_time; // Response time
} Process;

int compareArrivalTime(const void *a, const void *b) {
    return ((Process*)a)->arrival_time - ((Process*)b)->arrival_time;
}

int compareBurstTime(const void *a, const void *b) {
    return ((Process*)a)->burst_time - ((Process*)b)->burst_time;
}

void calculateTimes(Process *processes, int n) {
    int current_time = 0;
    int completed = 0;
    int total_waiting_time = 0, total_turnaround_time = 0, total_response_time = 0;
    
    while (completed < n) {
        // Tìm process chưa hoàn thành với burst time nhỏ nhất
        int min_burst_time = -1;
        int idx = -1;
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= current_time && processes[i].finish_time == 0) {
                if (min_burst_time == -1 || processes[i].burst_time < processes[min_burst_time].burst_time) {
                    min_burst_time = i;
                    idx = i;
                }
            }
        }

        if (idx == -1) {
            current_time++;
        } else {
            processes[idx].start_time = current_time;
            processes[idx].finish_time = current_time + processes[idx].burst_time;
            processes[idx].waiting_time = processes[idx].start_time - processes[idx].arrival_time;
            processes[idx].turnaround_time = processes[idx].waiting_time + processes[idx].burst_time;
            processes[idx].response_time = processes[idx].start_time - processes[idx].arrival_time;
            
            total_waiting_time += processes[idx].waiting_time;
            total_turnaround_time += processes[idx].turnaround_time;
            total_response_time += processes[idx].response_time;

            current_time = processes[idx].finish_time;
            completed++;
        }
    }

    // In kết quả
    printf("\nPName\tArrival\tBurst\tStart\tFinish\tWaiting\tTurnaround\tResponse\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\t\t%d\n", 
               processes[i].pname, 
               processes[i].arrival_time, 
               processes[i].burst_time, 
               processes[i].start_time, 
               processes[i].finish_time, 
               processes[i].waiting_time, 
               processes[i].turnaround_time, 
               processes[i].response_time);
    }

    printf("\nAverage Waiting Time: %.2f", (float)total_waiting_time / n);
    printf("\nAverage Turnaround Time: %.2f", (float)total_turnaround_time / n);
    printf("\nAverage Response Time: %.2f\n", (float)total_response_time / n);
}

int main() {
    int n;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    Process processes[n];

    for (int i = 0; i < n; i++) {
        printf("Enter Process Name, Arrival Time, Burst Time for process %d: ", i + 1);
        scanf("%d %d %d", &processes[i].pname, &processes[i].arrival_time, &processes[i].burst_time);
        processes[i].finish_time = 0;  // Chưa hoàn thành
    }

    // Sắp xếp các process theo arrival time (tăng dần)
    qsort(processes, n, sizeof(Process), compareArrivalTime);

    // Tính toán các thời gian
    calculateTimes(processes, n);

    return 0;
}
