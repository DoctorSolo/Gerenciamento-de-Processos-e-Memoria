#include <stdio.h>
#include <stdlib.h>


typedef struct {
    int id;
    int burst_time;
    int waiting_time;
    int turnaround_time;
} Process;

void sort_by_burst_time(Process p[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].burst_time > p[j + 1].burst_time) {
                Process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
}

void calculate_times(Process p[], int n) {
    p[0].waiting_time = 0;
    p[0].turnaround_time = p[0].burst_time;

    for (int i = 1; i < n; i++) {
        p[i].waiting_time = p[i - 1].waiting_time + p[i - 1].burst_time;
        p[i].turnaround_time = p[i].waiting_time + p[i].burst_time;
    }
}

void print_results(Process p[], int n) {
    float total_waiting = 0, total_turnaround = 0;

    printf("\nID\tBurst\tWaiting\tTurnaround\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\n", p[i].id, p[i].burst_time, p[i].waiting_time, p[i].turnaround_time);
        total_waiting += p[i].waiting_time;
        total_turnaround += p[i].turnaround_time;
    }

    printf("\nMédia de Waiting Time = %.2f\n", total_waiting / n);
    printf("Média de Turnaround Time = %.2f\n", total_turnaround / n);
}


/*
int main() {
    int n;
    printf("Digite o número de processos: ");
    scanf("%d", &n);

    Process p[n];
    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("Burst time do processo %d: ", p[i].id);
        scanf("%d", &p[i].burst_time);
    }

    sort_by_burst_time(p, n);
    calculate_times(p, n);
    print_results(p, n);

    return 0;
}
*/
