#include <stdio.h>
#include "main.h"

// 交换两个进程的位置
void swap(Process *xp, Process *yp)
{
    Process temp = *xp;
    *xp = *yp;
    *yp = temp;
}

// 按照进程的优先级进行排序
void sortByPriority(Process *processes, int n)
{
    int i, j;
    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (processes[j].priority > processes[j + 1].priority)
            {
                swap(&processes[j], &processes[j + 1]);
            }
        }
    }
}