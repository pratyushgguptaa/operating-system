#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

//function to swap two values
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

//function  to swap values of two entire processes
void swap_process(int* pro, int* arrival,
                  int* burst, int* rt, int a, int b);

//one function for each of the required algorithm
void first_come_first_serve(int n, int* pro, int* arrival, int* burst);
void shortest_job_first(int n, int* pro, int* arrival, int* burst);
void shortest_remaining_time_first(int n, int* pro, int* arrival, int* burst);
void round_robin(int n, int* pro, int* arrival, int* burst);
void non_preemptive_priority(int n, int* pro, int* arrival, int* burst, int* pri);
void preemptive_priority(int n, int* pro, int* arrival, int* burst, int* pri);

//function to print entire processes and calculate average TAT, WT
void print(int n, int* pro, int* tat, int* wt, int* rt);

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int pro[n],      // to store process IDs
        arrival[n],  // to store arrival time of each process
        burst[n],    // to store burst time of each process
        pri[n];      // to store priority of each process

    printf("Enter the data of each process, space-separated, as shown:\n");
    printf("Process-ID. Arrival-time Burst-time Priority\n");
    printf("PID A B Pri\n");

    for (int i = 0; i < n; i++)
        scanf("%d %d %d %d", &pro[i], &arrival[i], &burst[i], &pri[i]);

    printf("Select any one scheduling algorithm:\n");
    printf("1) First Come First Serve\n");
    printf("2) Shortest Job First\n");
    printf("3) Shortest Remaining Time First\n");
    printf("4) Round Robin\n");
    printf("5) Non Preemptive priority\n");
    printf("6) Prememptive priority\n");
    printf("Enter you choice: ");

    int ch = 0;
    scanf("%d", &ch);
    switch (ch) {
        case 1:
            first_come_first_serve(n, pro, arrival, burst);
            break;
        case 2:
            shortest_job_first(n, pro, arrival, burst);
            break;
        case 3:
            shortest_remaining_time_first(n, pro, arrival, burst);
            break;
        case 4:
            round_robin(n, pro, arrival, burst);
            break;
        case 5:
            non_preemptive_priority(n, pro, arrival, burst, pri);
            break;
        case 6:
            preemptive_priority(n, pro, arrival, burst, pri);
            break;
        default:
            printf("Invalid choice exiting program now...");
    }
}

void swap_process(int* pro, int* arrival, int* burst,
                  int* rt, int a, int b) {
    swap(&pro[a], &pro[b]);
    swap(&arrival[a], &arrival[b]);
    swap(&burst[a], &burst[b]);
    swap(&rt[a], &rt[b]);
}

void print(int n, int* pro, int* tat, int* wt, int* rt) {
    printf("\n");
#ifdef _WIN32
    printf("+---------------+---------------+---------------+---------------+\n");
    printf("|    Process    |  Turnaround   |    Waiting    |   Response    |\n");
    printf("|      ID       |     time      |     time      |     time      |\n");
    printf("+---------------+---------------+---------------+---------------+\n");
#else
    printf("┌───────────────┬───────────────┬───────────────┬───────────────┐\n");
    printf("│    Process    │  Turnaround   │    Waiting    │   Response    │\n");
    printf("│      ID       │     time      │     time      │     time      │\n");
    printf("├───────────────┼───────────────┼───────────────┼───────────────┤\n");
#endif
    float sumtat = 0, sumwt = 0, sumrt = 0;
    for (int i = 0; i < n; i++) {
#ifdef _WIN32
        printf("|\t%d\t|\t%d\t|\t%d\t|\t%d\t|\n", pro[i], tat[i], wt[i], rt[i]);
#else
        printf("│\t%d\t│\t%d\t│\t%d\t│\t%d\t│\n", pro[i], tat[i], wt[i], rt[i]);
#endif
        sumtat += tat[i];
        sumwt += wt[i];
        sumrt += rt[i];
    }
#ifdef _WIN32
    printf("+---------------+---------------+---------------+---------------+\n");
    printf("|    Average    |\t%.2f\t|\t%.2f\t|\t%.2f\t|\n", sumtat / n, sumwt / n, sumrt / n);
    printf("+---------------+---------------+---------------+---------------+\n");
#else
    printf("├───────────────┼───────────────┼───────────────┼───────────────┤\n");
    printf("│    Average    │\t%.2f\t│\t%.2f\t│\t%.2f\t│\n", sumtat / n, sumwt / n, sumrt / n);
    printf("└───────────────┴───────────────┴───────────────┴───────────────┘\n");
#endif
}

void first_come_first_serve(int n, int* pro, int* arrival, int* burst) {
    int tat[n],  // to store turnaround time of each process
        wt[n],   // to store waiting time of each process
        rt[n];   // to store response time of each process
    rt[0] = arrival[0];
    wt[0] = 0;
    tat[0] = burst[0];

    for (int i = 1; i < n; i++) {
        rt[i] = tat[i - 1] + arrival[i - 1] - arrival[i];
        if (rt[i] < 0) rt[i] = 0;
        //first_come_first_serve same response time as waiting time
        wt[i] = rt[i];
        tat[i] = burst[i] + wt[i];
    }
    print(n, pro, tat, wt, rt);
}

void shortest_job_first(int n, int* pro, int* arrival, int* burst) {
    int tat[n],  // to store turnaround time of each process
        wt[n],   // to store waiting time of each process
        rt[n];   // to store response time of each process
    int time = 0, count = 0, i;
    while (count - n) {
        i = count;
        for (int j = i + 1; j < n && arrival[j] <= time; j++)
            if (burst[j] < burst[i])
                i = j;
        if (arrival[i] > time) {
            time++;
            continue;
        }
        rt[i] = time - arrival[i];
        swap_process(pro, arrival, burst, rt, i, count);
        time += burst[count];
        wt[count] = rt[count];
        tat[count] = wt[count] + burst[count];
        count++;
    }
    print(n, pro, tat, wt, rt);
}

void shortest_remaining_time_first(int n, int* pro, int* arrival, int* burst) {
    int tat[n],  // to store turnaround time of each process
        wt[n],   // to store waiting time of each process
        rt[n];   // to store response time of each process
    int rem[n];  // to store remaining time of each process

    for (int i = 0; i < n; i++)
        rem[i] = burst[i];

    int time = 0, count = 0, curr = 0, i;

    //iterating for currently arrived process
    //for each unit of time
    while (count - n) {
        i = count;
        for (int j = i + 1; j < n && arrival[j] <= time; j++)
            if (rem[j] < rem[i])
                i = j;

        //if no process found (feeling of emptiness)
        if (arrival[i] > time) {
            time++;
            continue;
        }

        if (rem[i] == burst[i])
            rt[i] = time - arrival[i];

        rem[i] -= 1;
        time++;

        if (rem[i] == 0) {
            swap_process(pro, arrival, burst, rt, count, i);
            swap(&rem[i], &rem[count]);
            tat[count] = time - arrival[count];
            wt[count] = tat[count] - burst[count];
            count++;
        }
    }
    print(n, pro, tat, wt, rt);
}

struct queue {
    int i;
    struct queue* next;
} typedef queue;

queue *head = NULL, *tail = NULL;

void enqueue(int n) {
    if (head) {
        tail->next = (queue*)malloc(sizeof(queue));
        tail = tail->next;
    } else {
        head = (queue*)malloc(sizeof(queue));
        tail = head;
    }
    tail->i = n;
    tail->next = NULL;
}

void dequeue() {
    if (head == NULL) return;
    queue* p = head;
    head = head->next;
    free(p);
}

void round_robin(int n, int* pro, int* arrival, int* burst) {
    int tat[n],  // to store turnaround time of each process
        wt[n],   // to store waiting time of each process
        rt[n];   // to store response time of each process
    int rem[n];  // to store remaining time of each process

    for (int i = 0; i < n; i++)
        rem[i] = burst[i];

    int time = arrival[0], count = 0, i = 0, total = 1, q;

    printf("Enter the time quantum: ");
    scanf("%d", &q);

    enqueue(0);
    bool add_back;

    while (count - n) {
        i = head->i;
        dequeue();
        add_back = true;

        if (rem[i] == burst[i])
            rt[i] = time - arrival[i];

        if (rem[i] <= q) {
            //process finished here
            time += rem[i];
            rem[i] = 0;
            tat[i] = time - arrival[i];
            wt[i] = tat[i] - burst[i];
            count++;
            add_back = false;
        } else {
            rem[i] -= q;
            time += q;
        }

        for (int j = total; j < n && arrival[j] <= time; j++)
            enqueue(j), total++;

        if (add_back)
            enqueue(i);
    }
    print(n, pro, tat, wt, rt);
}

void non_preemptive_priority(int n, int* pro, int* arrival, int* burst, int* pri) {
    int tat[n],  // to store turnaround time of each process
        wt[n],   // to store waiting time of each process
        rt[n];   // to store response time of each process

    printf("Taking lower number as higher priority.\n");
    int time = 0, count = 0, i;

    while (count - n) {
        i = count;
        for (int j = i + 1; j, n && arrival[j] <= time; j++)
            if (pri[j] < pri[i])
                i = j;

        if (arrival[i] > time) {
            time++;
            continue;
        }
        rt[i] = time - arrival[i];
        swap_process(pro, arrival, burst, rt, i, count);
        swap(&pri[i], &pri[count]);
        wt[count] = rt[count];  //non preemptive
        time += burst[count];
        tat[count] = time - arrival[count];
        count++;
    }
    print(n, pro, tat, wt, rt);
}

void preemptive_priority(int n, int* pro, int* arrival, int* burst, int* pri) {
    int tat[n],  // to store turnaround time of each process
        wt[n],   // to store waiting time of each process
        rt[n];   // to store response time of each process
    int rem[n];  // to store remaining time of each process

    for (int i = 0; i < n; i++)
        rem[i] = burst[i];

    int time = 0, count = 0, i;

    while (count - n) {
        i = count;

        for (int j = i + 1; j < n && arrival[j] <= time; j++)
            if (pri[j] < pri[i])
                i = j;

        if (arrival[i] > time) {
            time++;
            continue;
        }

        if (rem[i] == burst[i])
            rt[i] = time - arrival[i];

        rem[i]--;
        time++;

        if (rem[i] == 0) {
            swap_process(pro, arrival, burst, rt, i, count);
            swap(&rem[i], &rem[count]);
            swap(&pri[i], &pri[count]);
            tat[count] = time - arrival[count];
            wt[count] = tat[count] - burst[count];
            count++;
        }
    }
    print(n, pro, tat, wt, rt);
}