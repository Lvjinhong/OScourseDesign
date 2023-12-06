#include <stdio.h>
#include "main.h"
// SRT调度算法
void srtScheduling(Process *processes, int n, float *results)
{
    int currentTime = 0;
    int completedProcesses = 0;
    int shortestTime, index;
    float totalWaitingTime = 0, totalTurnaroundTime = 0;
    Process *currentProcess = NULL;

    // 初始化每个进程的剩余时间
    for (int i = 0; i < n; i++)
    {
        processes[i].remainingTime = processes[i].burstTime;
    }

    while (completedProcesses < n)
    {
        shortestTime = 9999;
        index = -1;

        // 寻找剩余时间最短的进程
        for (int i = 0; i < n; i++)
        {
            if (processes[i].arrivalTime <= currentTime && processes[i].remainingTime < shortestTime && processes[i].remainingTime > 0)
            {
                shortestTime = processes[i].remainingTime;
                index = i;
            }
        }

        if (index != -1)
        { // 如果找到了合适的进程
            currentProcess = &processes[index];
            currentProcess->remainingTime--;
            printf("时间 %d: 进程 %d 正在执行\n", currentTime, currentProcess->processId);

            if (currentProcess->remainingTime == 0)
            { // 如果进程完成
                printf("时间 %d: 进程 %d 完成\n", currentTime, currentProcess->processId);
                currentProcess->turnaroundTime = currentTime - currentProcess->arrivalTime + 1;
                currentProcess->waitingTime = currentProcess->turnaroundTime - currentProcess->burstTime;
                totalWaitingTime += currentProcess->waitingTime;
                totalTurnaroundTime += currentProcess->turnaroundTime;
                completedProcesses++;
            }
        }

        // 时间前进
        currentTime++;

        if (index == -1 && completedProcesses < n)
        {
            printf("时间 %d: CPU空闲\n", currentTime);
        }
    }

    // 打印统计信息
    printf("\n进程ID\t到达时间\t服务时间\t等待时间\t周转时间\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].processId, processes[i].arrivalTime, processes[i].burstTime, processes[i].waitingTime, processes[i].turnaroundTime);
    }

    // 计算并打印平均等待时间和平均周转时间
    float avgWaitingTime = totalWaitingTime / n;
    float avgTurnaroundTime = totalTurnaroundTime / n;
    results[0] = avgWaitingTime;
    results[1] = avgTurnaroundTime;
    printf("\n平均等待时间: %.2f\n", avgWaitingTime);
    printf("平均周转时间: %.2f\n", avgTurnaroundTime);
}
