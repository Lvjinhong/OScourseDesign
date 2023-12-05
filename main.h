#ifndef Main
#define Main

#include <stdio.h>
// 其他必要的包含文件

// 进程结构体
typedef struct
{
    int processId;
    int arrivalTime;
    int burstTime;
    int waitingTime;
    int turnaroundTime;
    int remainingTime;
    int priority;
    float responseRatio;
} Process;
void swap(Process *xp, Process *yp);
void sortByPriority(Process *processes, int n);
void sortByBurstTime(Process *processes, int n);
void hrpScheduling(Process *processes, int n);
void srtScheduling(Process *processes, int n);
void sortByArrivalTime(Process *processes, int n);
void roundRobinScheduling(Process *processes, int n, int timeQuantum);
#endif