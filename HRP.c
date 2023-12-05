#include <stdio.h>
#include "main.h"
// HRP调度算法
void hrpScheduling(Process *processes, int n)
{
    int i, shortestProcess, currentTime = 0;
    int totalBurstTime = 0, completedProcesses = 0;

    // 计算总的执行时间
    for (i = 0; i < n; i++)
    {
        totalBurstTime += processes[i].burstTime;
    }

    // 执行HRP调度
    while (completedProcesses < n)
    {
        // TODO 改
        printf("HRP:%d", completedProcesses);
        float highestResponseRatio = -1;

        // 查找响应比最高的进程
        for (i = 0; i < n; i++)
        {
            if (processes[i].arrivalTime <= currentTime && processes[i].burstTime > 0)
            {
                float responseRatio = (float)(currentTime - processes[i].arrivalTime + processes[i].burstTime) / processes[i].burstTime;

                if (responseRatio > highestResponseRatio)
                {
                    highestResponseRatio = responseRatio;
                    shortestProcess = i;
                }
            }
        }
        //HACK:
        // 更新当前时间和进程状态
        if (highestResponseRatio != -1)
        {
            currentTime += processes[shortestProcess].burstTime;
            processes[shortestProcess].waitingTime = currentTime - processes[shortestProcess].arrivalTime - processes[shortestProcess].burstTime;
            processes[shortestProcess].turnaroundTime = currentTime - processes[shortestProcess].arrivalTime;
            processes[shortestProcess].responseRatio = highestResponseRatio;
            processes[shortestProcess].burstTime = 0;
            completedProcesses++;
        }
        else
        {
            currentTime++;
        }
    }
}