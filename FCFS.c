#include "main.h"
int t() {}

// 按照进程的到达时间进行排序
void sortByArrivalTime(Process *processes, int n)
{
    int i, j;
    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (processes[j].arrivalTime > processes[j + 1].arrivalTime)
            {
                swap(&processes[j], &processes[j + 1]);
            }
        }
    }
}
