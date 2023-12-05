#include <stdio.h>
#include "main.h"
// 时间片轮转调度算法
void roundRobinScheduling(Process *processes, int n, int timeQuantum)
{
    int i, totalBurstTime = 0;
    int currentTime = 0;

    // 计算总的执行时间
    for (i = 0; i < n; i++)
    {
        totalBurstTime += processes[i].burstTime;
        processes[i].remainingTime = processes[i].burstTime;
    }

    // 执行时间片轮转调度
    while (totalBurstTime > 0)
    {
        for (i = 0; i < n; i++)
        {
            if (processes[i].remainingTime > 0)
            {
                if (processes[i].remainingTime <= timeQuantum)
                {
                    currentTime += processes[i].remainingTime;
                    totalBurstTime -= processes[i].remainingTime;
                    processes[i].waitingTime = currentTime - processes[i].arrivalTime - processes[i].burstTime;
                    processes[i].turnaroundTime = currentTime - processes[i].arrivalTime;
                    processes[i].remainingTime = 0;
                }
                else
                {
                    currentTime += timeQuantum;
                    totalBurstTime -= timeQuantum;
                    processes[i].remainingTime -= timeQuantum;
                }
            }
        }
    }
}