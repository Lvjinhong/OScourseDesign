#include <stdio.h>
#include "main.h"
// SRT调度算法
void srtScheduling(Process *processes, int n)
{
    int i, shortestProcess, currentTime = 0;
    int totalBurstTime = 0, completedProcesses = 0;
    int isCompleted[n];

    // 初始化标志数组
    for (i = 0; i < n; i++)
    {
        isCompleted[i] = 0;
        totalBurstTime += processes[i].burstTime;
        processes[i].remainingTime = processes[i].burstTime;
    }

    // 执行SRT调度
    while (completedProcesses < n)
    {
        shortestProcess = -1;

        // 查找剩余时间最短的进程
        for (i = 0; i < n; i++)
        {
            if (processes[i].arrivalTime <= currentTime && !isCompleted[i])
            {
                if (shortestProcess == -1 || processes[i].remainingTime < processes[shortestProcess].remainingTime)
                {
                    shortestProcess = i;
                }
            }
        }

        // 更新当前时间和进程状态
        if (shortestProcess != -1)
        {
            currentTime++;
            processes[shortestProcess].remainingTime--;

            if (processes[shortestProcess].remainingTime == 0)
            {
                completedProcesses++;
                isCompleted[shortestProcess] = 1;
                processes[shortestProcess].waitingTime = currentTime - processes[shortestProcess].arrivalTime - processes[shortestProcess].burstTime;
                processes[shortestProcess].turnaroundTime = currentTime - processes[shortestProcess].arrivalTime;
            }
        }
        else
        {
            currentTime++;
        }
    }
}