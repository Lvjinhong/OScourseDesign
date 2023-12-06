#ifndef Main
#define Main
#include <stdlib.h>
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
    int startTime;
    float responseRatio;
} Process;
void swap(Process *xp, Process *yp);
void Priority(Process *processes, int n, float *results);
void sortByBurstTime(Process *processes, int n);
void hrrnScheduling(Process *processes, int n, float *results);
void srtScheduling(Process *processes, int n, float *results);
void printProcessInfo(Process *processes, int n);
void sortByArrivalTime(Process *processes, int n);
void sortProcessesByArrivalTime(Process *processes, int n);
void calculateSJFTimes(Process *processes, int n, int index);
void rrScheduling(Process pro[], int num, int timeSlice, float *results);
#endif
