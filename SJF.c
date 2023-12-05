#include <stdio.h>
#include "main.h"
// // 按照进程的执行时间进行排序
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

// int main()
// {
//     int n; // 进程数量
//     int i;

//     // 输入进程数量
//     printf("请输入进程数量: ");
//     scanf("%d", &n);

//     // 创建进程数组
//     Process processes[n];

//     // 输入每个进程的到达时间和执行时间
//     for (i = 0; i < n; i++)
//     {
//         printf("请输入进程%d的到达时间和执行时间: ", i + 1);
//         scanf("%d %d", &processes[i].arrivalTime, &processes[i].burstTime);
//         processes[i].processId = i + 1;
//     }

//     // 按照到达时间排序
//     sortByArrivalTime(processes, n);

//     // 按照执行时间排序
//     sortByBurstTime(processes, n);

//     // 调用计算函数
//     calculateTimes(processes, n);

//     return 0;
// }
