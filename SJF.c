#include <stdio.h>
#include <stdlib.h>
#include "main.h"
// 比较函数，用于按照到达时间和执行时间排序
int compare(const void *a, const void *b)
{
    Process *processA = (Process *)a;
    Process *processB = (Process *)b;

    // 如果到达时间相同，则比较执行时间
    if (processA->arrivalTime == processB->arrivalTime)
    {
        return processA->burstTime - processB->burstTime;
    }
    return processA->arrivalTime - processB->arrivalTime;
}
void sortByBurstTime(Process *processes, int n)
{
    int i, j;
    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (processes[j].burstTime > processes[j + 1].burstTime)
            {
                swap(&processes[j], &processes[j + 1]);
            }
        }
    }
}

// 计算等待时间和周转时间
void calculateSJFTimes(Process *processes, int n, int index)
{
    int i, j;
    int currentTime = 0;
    int totalWaitingTime = 0;
    int totalTurnaroundTime = 0;
    qsort(&processes[1], n - 1, sizeof(Process), compare); // 根据到达时间和执行时间排序
    printf("按照到达-执行时间排序后的进程信息：\n");
    printProcessInfo(processes, n);
}
