## Program to Simulate Scheduling Algorithms

Generic code in C of CPU Scheduling algorithms:
- [First Come First Serve](https://github.com/pratyushgguptaa/operating-system/blob/main/scheduling-algorithms/fcfs_sjf_srtf_rr_npp_pp.c#:~:text=void-,first_come_first_serve,-(int%20n%2C%20int*%20pro%2C%20int*%20arrival%2C%20int*%20burst)%20%7B)
- [Shortest Job First](https://github.com/pratyushgguptaa/operating-system/blob/main/scheduling-algorithms/fcfs_sjf_srtf_rr_npp_pp.c#:~:text=void-,shortest_job_first,-(int%20n%2C%20int*%20pro%2C%20int*%20arrival%2C%20int*%20burst)%20%7B)
- [Shortest Remaining Time First](https://github.com/pratyushgguptaa/operating-system/blob/main/scheduling-algorithms/fcfs_sjf_srtf_rr_npp_pp.c#:~:text=void-,shortest_remaining_time_first,-(int%20n%2C%20int*%20pro%2C%20int*%20arrival%2C%20int*%20burst)%20%7B)
- [Round Robin](https://github.com/pratyushgguptaa/operating-system/blob/main/scheduling-algorithms/fcfs_sjf_srtf_rr_npp_pp.c#:~:text=void-,round_robin,-(int%20n%2C%20int*%20pro%2C%20int*%20arrival%2C%20int*%20burst)%20%7B)
- [Non-Preememptive Priority](https://github.com/pratyushgguptaa/operating-system/blob/main/scheduling-algorithms/fcfs_sjf_srtf_rr_npp_pp.c#:~:text=%7D-,void%20non_preemptive_priority(int%20n%2C%20int*%20pro%2C%20int*%20arrival%2C%20int*%20burst%2C%20int*%20pri),-%7B)
- [Preemptive Priority](https://github.com/pratyushgguptaa/operating-system/blob/main/scheduling-algorithms/fcfs_sjf_srtf_rr_npp_pp.c#:~:text=void%20preemptive_priority(int%20n%2C%20int*%20pro%2C%20int*%20arrival%2C%20int*%20burst%2C%20int*%20pri)%20%7B)

### Inputs
- Number of processes.
- Process ID, arrival time, burst time and priority of each process.
- Selecting one of the Scheduling algorithms.
- If Round Robin is selected, input the time quantum.

### Output
- Turnaround time, waiting time, response time of each process.
- Average of the above data.

### Examples
```bash
  Enter the number of processes: 7
  Enter the data of each process, space-separated, as shown:
  Process-ID. Arrival-time Burst-time Priority
  PID A B Pri
  1 0 1 2
  2 1 7 6
  3 2 3 3
  4 3 6 5
  5 4 5 4
  6 5 15 10
  7 6 8 9
  Select any one scheduling algorithm:
  1) First Come First Serve
  2) Shortest Job First
  3) Shortest Remaining Time First
  4) Round Robin
  5) Non Preemptive priority
  6) Prememptive priority
  Enter you choice: 6

  ┌───────────────┬───────────────┬───────────────┬───────────────┐
  │    Process    │  Turnaround   │    Waiting    │   Response    │
  │      ID       │     time      │     time      │     time      │
  ├───────────────┼───────────────┼───────────────┼───────────────┤
  │       1       │       1       │       0       │       0       │
  │       3       │       3       │       0       │       0       │
  │       5       │       6       │       1       │       1       │
  │       4       │       13      │       7       │       7       │
  │       2       │       21      │       14      │       0       │
  │       7       │       24      │       16      │       16      │
  │       6       │       40      │       25      │       25      │
  ├───────────────┼───────────────┼───────────────┼───────────────┤
  │    Average    │       15.43   │       9.00    │       7.00    │
  └───────────────┴───────────────┴───────────────┴───────────────┘
```