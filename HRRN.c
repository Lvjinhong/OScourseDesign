#include <stdio.h>

#include "main.h"
// HRP调度算法
void hrrnScheduling(Process *processes, int n, float *results)
{
    int currentTime = 0;
    int completedProcesses = 0;
    float totalWaitingTime = 0;
    float totalTurnaroundTime = 0;

    // 第一个进程直接开始执行
    processes[0].waitingTime = 0;
    processes[0].turnaroundTime = processes[0].burstTime;
    currentTime = processes[0].arrivalTime + processes[0].burstTime;
    totalWaitingTime += processes[0].waitingTime;
    totalTurnaroundTime += processes[0].turnaroundTime;
    completedProcesses++;

    while (completedProcesses < n)
    {
        int index = -1;
        float highestResponseRatio = -1;

        // 查找响应比最高的进程
        for (int i = 1; i < n; i++)
        {
            if (processes[i].arrivalTime <= currentTime && processes[i].burstTime > 0)
            {
                float responseRatio = (float)(currentTime - processes[i].arrivalTime + processes[i].burstTime) / processes[i].burstTime;
                printf("计算进程ID: %d，响应比: %.2f;\t", processes[i].processId, responseRatio);
                if (responseRatio > highestResponseRatio)
                {
                    highestResponseRatio = responseRatio;
                    index = i;
                }
            }
        }

        // 如果找到了响应比最高的进程
        if (index != -1)
        {
            printf("\n从中选择最高响应比进程ID: %d，其响应比: %.2f\n", processes[index].processId, highestResponseRatio);

            // 更新等待时间和周转时间
            processes[index].waitingTime = currentTime - processes[index].arrivalTime;
            processes[index].turnaroundTime = processes[index].waitingTime + processes[index].burstTime;

            // 更新总等待时间和总周转时间
            totalWaitingTime += processes[index].waitingTime;
            totalTurnaroundTime += processes[index].turnaroundTime;

            // 更新当前时间
            currentTime += processes[index].burstTime;
            processes[index].burstTime = 0; // 标记进程已完成
            completedProcesses++;
        }
        else
        {
            currentTime++; // 如果没有找到，则时间前进
        }
    }
    results[0] = totalWaitingTime / n;
    results[1] = totalTurnaroundTime / n;
    // 输出平均等待时间和平均周转时间
    printf("\n平均等待时间: %.2f\n", totalWaitingTime / n);
    printf("平均周转时间: %.2f\n", totalTurnaroundTime / n);
}
