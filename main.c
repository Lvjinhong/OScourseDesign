#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "main.h"
float results[6][2];
// 测试用例生成器
void generateTestCases(Process processes[], int n)
{
    srand(1); // 随机数种子
    for (int i = 0; i < n; i++)
    {
        processes[i].processId = i + 1;
        processes[i].arrivalTime = rand() % 10;   // 0到9之间的随机到达时间
        processes[i].burstTime = rand() % 10 + 5; // 1到10之间的随机服务时间
        processes[i].priority = rand() % 10;      // 0到9之间的优先级
    }
}
// 交换两个进程的位置
void swap(Process *xp, Process *yp)
{
    Process temp = *xp;
    *xp = *yp;
    *yp = temp;
}

// 计算等待时间和周转时间
void calculateTimes(Process *processes, int n, int index)
{
    int i;
    int totalWaitingTime = 0;
    int totalTurnaroundTime = 0;
    int currentTime = 0; // 当前时间，用于跟踪进程的完成时间

    // 对于第一个进程
    processes[0].waitingTime = 0;                                    // 第一个进程的等待时间为0
    processes[0].turnaroundTime = processes[0].burstTime;            // 周转时间为爆发时间
    currentTime = processes[0].arrivalTime + processes[0].burstTime; // 更新当前时间为第一个进程的完成时间

    // 累加第一个进程的等待时间和周转时间
    totalWaitingTime += processes[0].waitingTime;
    totalTurnaroundTime += processes[0].turnaroundTime;

    // 计算后续进程的等待时间和周转时间
    for (i = 1; i < n; i++)
    {
        // 如果当前时间小于进程的到达时间，则更新当前时间为进程的到达时间
        if (currentTime < processes[i].arrivalTime)
        {
            currentTime = processes[i].arrivalTime;
        }

        processes[i].waitingTime = currentTime - processes[i].arrivalTime;
        currentTime += processes[i].burstTime; // 更新当前时间为这个进程的完成时间
        processes[i].turnaroundTime = currentTime - processes[i].arrivalTime;

        // 累加等待时间和周转时间
        totalWaitingTime += processes[i].waitingTime;
        totalTurnaroundTime += processes[i].turnaroundTime;
    }

    printf("\n***********************************\n");
    printf("测试结果如下：\n");
    // 输出每个进程的等待时间和周转时间
    printf("\n进程ID\t等待时间\t周转时间\n");
    for (i = 0; i < n; i++)
    {
        printf("%d\t\t%d\t\t%d\n", processes[i].processId, processes[i].waitingTime, processes[i].turnaroundTime);
    }
    results[index][0] = (float)totalWaitingTime / n;
    results[index][1] = (float)totalTurnaroundTime / n;
    // 输出平均等待时间和平均周转时间
    printf("\n平均等待时间: %.2f", results[index][0]);
    printf("\n平均周转时间: %.2f", results[index][1]);
    printf("\n***********************************\n\n");
}

int compareArrivalTime(const void *a, const void *b)
{
    Process *p1 = (Process *)a;
    Process *p2 = (Process *)b;
    return p1->arrivalTime - p2->arrivalTime;
}

// 根据到达时间对进程进行排序
void sortProcessesByArrivalTime(Process *processes, int n)
{
    qsort(processes, n, sizeof(Process), compareArrivalTime);
}
// 打印进程信息的函数
void printProcessInfo(Process *processes, int n)
{
    printf("进程信息：\n");
    printf("ID\t到达时间\t执行时间\t优先级\n");

    for (int i = 0; i < n; i++)
    {
        printf("%d\t\t%d\t\t%d\t\t%d\n", processes[i].processId, processes[i].arrivalTime, processes[i].burstTime, processes[i].priority);
    }
}
void testInit(Process *processes)
{
    processes[0].processId = 1;
    processes[0].arrivalTime = 0;
    processes[0].burstTime = 8;
    processes[0].priority = 3;
    processes[1].processId = 2;
    processes[1].arrivalTime = 1;
    processes[1].burstTime = 3;
    processes[1].priority = 1;
    processes[2].processId = 3;
    processes[2].arrivalTime = 5;
    processes[2].burstTime = 9;
    processes[2].priority = 2;
    processes[3].processId = 4;
    processes[3].arrivalTime = 3;
    processes[3].burstTime = 1;
    processes[3].priority = 2;
    processes[4].processId = 5;
    processes[4].arrivalTime = 4;
    processes[4].burstTime = 2;
    processes[4].priority = 4;
    // Initialize remaining fields to 0 or appropriate default values
    for (int i = 0; i < 4; i++)
    {
        processes[i].waitingTime = 0;
        processes[i].turnaroundTime = 0;
        processes[i].remainingTime = processes[i].burstTime; // Assuming remaining time is the burst time at initialization
                                                             // Assuming default priority to 0
        processes[i].responseRatio = 0.0;                    // Assuming default response ratio to 0.0
    }
}

int main()
{
    int n = 5, timeQuantum = 3; // 进程数量 时间片大小
    // 输入进程数量和时间片
    // printf("请输入进程数量和时间片: ");
    // scanf("%d %d", &n, &timeQuantum);
    printf("进程数量：%d\t时间片大小：%d\n", n, timeQuantum);
    // 创建进程数组
    Process processes[6][n];
    for (int i = 0; i < 6; i++)
    {
        /* code */
        testInit(processes[i]);
        // generateTestCases(processes[i], n);
    }
    // generateTestCases(processes, n);
    printf("生成测试用例：\n");
    printProcessInfo(processes[0], n);

    //*****************************************************
    printf("\n-------------------------FCFS算法-----------------------------\n");
    sortProcessesByArrivalTime(processes[0], n);
    printf("按照到达时间排序后的进程信息：\n");
    printProcessInfo(processes[0], n);
    // 调用计算函数
    calculateTimes(processes[0], n, 0);

    //*****************************************************
    printf("\n-------------------------SJF非抢占式短作业优先法-----------------------------\n");
    sortByArrivalTime(processes[1], n);
    sortByBurstTime(&processes[1][1], n - 1);
    printf("按照到达-执行时间排序后的进程信息：\n");
    printProcessInfo(processes[1], n);
    // 调用计算函数
    calculateTimes(processes[1], n, 1);
    // calculateSJFTimes(processes[1], n, results[1]);

    //*****************************************************
    printf("\n--------------------------SRT最短剩余时间优先法----------------------------\n");
    printProcessInfo(processes[2], n);
    // 执行SRT调度算法
    srtScheduling(processes[2], n, results[2]);
    // 调用计算函数

    //*****************************************************
    printf("\n---------------------------HRRN最高响应比优先法---------------------------\n");
    sortProcessesByArrivalTime(processes[3], n);
    printf("按照到达排序后的进程信息：\n");
    printProcessInfo(processes[3], n);
    // hrpScheduling(processes[3], n);
    hrrnScheduling(processes[3], n, results[3]);
    // 调用计算函数
    //*****************************************************
    printf("\n----------------------------优先级调度算法--------------------------\n");
    // 按照优先级排序
    sortProcessesByArrivalTime(processes[4], n);
    Priority(processes[4], n, results[4]);
    //*****************************************************
    printf("\n------------------------------RR轮转法------------------------\n");
    rrScheduling(processes[5], n, timeQuantum, results[5]);
    //*****************************************************
    printf("最终结果如下:\n");
    printf("\t\tFCFS\tSJF\tSRT\tHRP\t优先级\tRR\n");
    printf("平均等待时间:");
    for (int i = 0; i < 6; i++)
        printf("\t%.2f", results[i][0]);
    printf("\n平均周转时间");
    for (int i = 0; i < 6; i++)
        printf("\t%.2f", results[i][1]);

    return 0;
}