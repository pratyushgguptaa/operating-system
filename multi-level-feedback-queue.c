#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct process {
    int PID;
    int arrival_time,
        burst_time,
        remaining,
        response,
        turnaround,
        waiting;
    struct process* next;
} typedef process;

process *head1 = NULL, *tail1;  //queue 1
process *head2 = NULL, *tail2;  //queue 2
process *head3 = NULL, *tail3;  //queue 3
process *head4 = NULL, *tail4;  // complete list

process* create(int PID, int bur);
void enqueue(process** head, process** tail, process* proc);
process* dequeue(process** head);

void multilevel_feedback_queue(int n, int q1, int q2, int q3, int rr1, int rr2);
void print(process* head);

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter the data of each process, space-separated, as shown:\n");
    printf("Process-ID. Burst-time\n");
    printf("PID B\n");
    int pid, arr, burst_time;
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &pid, &burst_time);
        enqueue(&head1, &tail1, create(pid, burst_time));
    }
    
    int q1quanta = 8, q2quanta = 16, q3quanta = 32;
    int rr1quanta = 2, rr2quanta = 4;
    multilevel_feedback_queue(n, q1quanta, q2quanta, q3quanta, rr1quanta, rr2quanta);
    print(head4);
}

process* create(int PID, int burst_time) {
    process* proc = (process*)malloc(sizeof(process));
    proc->PID = PID;
    proc->arrival_time = 0;
    proc->burst_time = proc->remaining = burst_time;
    return proc;
}

void enqueue(process** head, process** tail, process* proc) {
    if (*head) {
        (*tail)->next = proc;
        *tail = (*tail)->next;
    } else {
        *head = proc;
        *tail = *head;
    }
    (*tail)->next = NULL;
}

process* dequeue(process** head) {
    if (*head == NULL) return NULL;
    process* p = *head;
    *head = (*head)->next;
    return p;
}

void multilevel_feedback_queue(int n, int q1, int q2, int q3, int rr1, int rr2) {
    //creating multilevel feedback queues
    int time = 0, count = 0, t = 0;
    process* p;
    while (count - n) {
        t = 0;
        //rr2
        while (t < q1 && head1) {
            p = dequeue(&head1);
            if (p->remaining == p->burst_time)
                p->response = time + t - p->arrival_time;
            if (p->remaining <= rr1) {
                //process finsihed send to complete list
                t += p->remaining;
                p->remaining = 0;
                p->turnaround = time + t - p->arrival_time;
                p->waiting = p->turnaround - p->burst_time;
                enqueue(&head4, &tail4, p);
                count++;
            } else {
                p->remaining -= t + rr1 <= q1 ? rr1 : q1 - t;
                t = t + rr1 <= q1 ? t + rr1 : q1;
                enqueue(&head2, &tail2, p);
            }
        }
        while (head1) {
            enqueue(&head2, &tail2, dequeue(&head1));
        }
        time += t;
        //rr4
        t = 0;
        while (t < q2 && head2) {
            p = dequeue(&head2);
            if (p->remaining == p->burst_time)
                p->response = time + t - p->arrival_time;
            if (p->remaining <= rr2) {
                //process finsihed send to complete list
                t += p->remaining;
                p->remaining = 0;
                p->turnaround = time + t - p->arrival_time;
                p->waiting = p->turnaround - p->burst_time;
                enqueue(&head4, &tail4, p);
                count++;
            } else {
                p->remaining -= t + rr2 <= q2 ? rr2 : q2 - t;
                t = t + rr2 <= q2 ? t + rr2 : q2;
                enqueue(&head3, &tail3, p);
            }
        }
        while (head2) {
            enqueue(&head3, &tail3, dequeue(&head2));
        }
        time += t;
        //fcfs
        t = 0;
        while (t < q3 && head3) {
            p = dequeue(&head3);
            if (p->remaining == p->burst_time)
                p->response = time + t - p->arrival_time;
            if (p->remaining + t <= q3) {
                //process finished
                t += p->remaining;
                p->remaining = 0;
                p->turnaround = time + t - p->arrival_time;
                p->waiting = p->turnaround - p->burst_time;
                enqueue(&head4, &tail4, p);
                count++;
            } else {
                p->remaining -= q3 - t;
                t = q3;
                enqueue(&head1, &tail1, p);
            }
        }
        while (head3) {
            enqueue(&head1, &tail1, dequeue(&head3));
        }
        time += t;
    }
}

void print(process* head) {
    printf("\n");
    printf("+---------------+---------------+---------------+---------------+\n");
    printf("|    Process    |  Turnaround   |    Waiting    |   Response    |\n");
    printf("|      ID       |     time      |     time      |     time      |\n");
    printf("+---------------+---------------+---------------+---------------+\n");
    float sum_turnaround = 0, sum_waiting = 0, sum_response = 0, n = 0;
    while (head) {
        printf("|\t%d\t|\t%d\t|\t%d\t|\t%d\t|\n", head->PID, head->turnaround, head->waiting, head->response);
        sum_turnaround += head->turnaround;
        sum_waiting += head->waiting;
        sum_response += head->response;
        head = head->next;
        n++;
    }
    printf("+---------------+---------------+---------------+---------------+\n");
    printf("|    Average    |\t%.2f\t|\t%.2f\t|\t%.2f\t|\n", sum_turnaround / n, sum_waiting / n, sum_response / n);
    printf("+---------------+---------------+---------------+---------------+\n");
}
