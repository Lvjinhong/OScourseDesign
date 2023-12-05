#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "main.h"
double results[6][2];
// 测试用例生成器
void generateTestCases(Process processes[], int n)
{
    srand(time(NULL)); // 随机数种子
    for (int i = 0; i < n; i++)
    {
        processes[i].processId = i + 1;
        processes[i].arrivalTime = rand() % 10;   // 0到9之间的随机到达时间
        processes[i].burstTime = rand() % 10 + 1; // 1到10之间的随机服务时间
        processes[i].priority = rand() % 10;      // 0到9之间的优先级
    }
}

// 计算等待时间和周转时间
void calculateTimes(Process *processes, int n, int index)
{
    int i;
    int totalWaitingTime = 0;
    int totalTurnaroundTime = 0;

    processes[0].waitingTime = 0; // 第一个进程的等待时间为0

    // 计算每个进程的等待时间和周转时间
    for (i = 1; i < n; i++)
    {
        processes[i].waitingTime = processes[i - 1].waitingTime + processes[i - 1].burstTime;
        processes[i].turnaroundTime = processes[i].waitingTime + processes[i].burstTime;

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

int main()
{
    int n, timeQuantum = 1; // 进程数量 时间片大小
    // 输入进程数量和时间片
    printf("请输入进程数量和时间片: ");
    scanf("%d %d", &n, &timeQuantum);
    // 创建进程数组
    Process processes[6][n];

    for (int i = 0; i < 6; i++)
    {
        /* code */
        generateTestCases(processes[i], n);
    }
    // generateTestCases(processes, n);
    printf("生成测试用例：\n");
    printProcessInfo(processes[0], n);

    //*****************************************************
    printf("-------------------------FCFS算法-----------------------------\n");
    sortProcessesByArrivalTime(processes[0], n);
    printf("按照到达时间排序后的进程信息：\n");
    printProcessInfo(processes[0], n);
    // 调用计算函数
    calculateTimes(processes[0], n, 0);

    //*****************************************************
    printf("-------------------------SJF短作业优先法-----------------------------\n");
    sortByArrivalTime(processes[1], n);
    sortByBurstTime(processes[1], n);
    printf("按照到达-执行时间排序后的进程信息：\n");
    printProcessInfo(processes[1], n);
    // 调用计算函数
    calculateTimes(processes[1], n, 1);

    //*****************************************************
    printf("--------------------------SRT最短剩余时间优先法----------------------------\n");
    printProcessInfo(processes[2], n);
    // 执行SRT调度算法
    srtScheduling(processes[2], n);
    // 调用计算函数
    calculateTimes(processes[2], n, 2);
    //*****************************************************
    printf("---------------------------HRP最高响应比优先法---------------------------\n");
    printProcessInfo(processes[3], n);
    hrpScheduling(processes[3], n);
    // 调用计算函数
    calculateTimes(processes[3], n, 3);
    //*****************************************************
    printf("----------------------------优先级调度算法--------------------------\n");
    // 按照优先级排序
    sortByPriority(processes[4], n);
    sortProcessesByArrivalTime(processes[4], n);
    printf("按照优先级-到达排序后的进程信息：\n");
    printProcessInfo(processes[4], n);
    calculateTimes(processes[4], n, 4);
    //*****************************************************
    printf("------------------------------RR轮转法------------------------\n");
    roundRobinScheduling(processes[5], n, timeQuantum);
    calculateTimes(processes[5], n, 5);
    //*****************************************************
    printf("最终结果如下:\n");
    printf("\tFCFS\tSJF\tSRT\tHRP\t优先级\tRR\n");
    printf("平均等待时间:");
    for (int i = 0; i < 6; i++)
        printf("\t%.2f", results[i][0]);
    printf("\n平均周转时间");
    for (int i = 0; i < 6; i++)
        printf("\t%.2f", results[i][1]);

    return 0;
}