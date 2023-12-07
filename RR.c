#include <stdio.h>
#include "main.h"
// 时间片轮转调度算法
int min(int a, int b)
{
    return a < b ? a : b;
}

typedef struct QueueNode
{
    Process *data;
    struct QueueNode *next;
} QueueNode;

typedef struct
{
    QueueNode *front, *rear;
    int size;
} Queue;

void QueueInit(Queue *q)
{
    q->front = q->rear = NULL;
    q->size = 0;
}

void Enqueue(Queue *q, Process *p)
{
    QueueNode *temp = (QueueNode *)malloc(sizeof(QueueNode));
    temp->data = p;
    temp->next = NULL;
    if (q->rear == NULL)
    {
        q->front = q->rear = temp;
        q->size = 1;
        return;
    }
    q->rear->next = temp;
    q->rear = temp;
    q->size++;
}

Process *Dequeue(Queue *q)
{
    if (q->front == NULL)
    {
        return NULL;
    }
    QueueNode *temp = q->front;
    Process *p = temp->data;
    q->front = q->front->next;
    if (q->front == NULL)
    {
        q->rear = NULL;
    }
    free(temp);
    q->size--;
    return p;
}

void sortWithArrivalTime(Process pro[], int num)
{
    for (int i = 0; i < num - 1; i++)
    {
        for (int j = 0; j < num - i - 1; j++)
        {
            if (pro[j].arrivalTime > pro[j + 1].arrivalTime)
            {
                Process temp = pro[j];
                pro[j] = pro[j + 1];
                pro[j + 1] = temp;
            }
        }
    }
}
void rrScheduling(Process pro[], int num, int timeSlice, float *results)
{
    printf("进程ID 到达时间 服务时间 开始时间 完成时间 周转时间 带权周转时间\n");
    Queue queue;
    QueueInit(&queue);
    int currentTime = 0;
    float totalTurnaroundTime = 0, totalWeightedTurnaroundTime = 0, sumWaittime = 0;
    int completed = 0, i = 0;

    while (completed < num)
    {
        while (i < num && pro[i].arrivalTime <= currentTime)
        {
            Enqueue(&queue, &pro[i]);
            i++;
        }
        if (queue.size > 0)
        {
            Process *currentProcess = Dequeue(&queue);
            int executionTime = (currentProcess->remainingTime > timeSlice) ? timeSlice : currentProcess->remainingTime;
            currentTime += executionTime;
            currentProcess->remainingTime -= executionTime;
            if (currentProcess->remainingTime == 0)
            {
                currentProcess->turnaroundTime = currentTime - currentProcess->arrivalTime;
                currentProcess->waitingTime = currentProcess->turnaroundTime - currentProcess->burstTime;
                totalTurnaroundTime += currentProcess->turnaroundTime;
                totalWeightedTurnaroundTime += (float)currentProcess->turnaroundTime / currentProcess->burstTime;
                sumWaittime += currentProcess->waitingTime;
                printf("%d\t%d\t%d\t%d\t%d\t%d\t%.2f\n", currentProcess->processId, currentProcess->arrivalTime, currentProcess->burstTime, currentProcess->arrivalTime + currentProcess->waitingTime,
                       currentTime, currentProcess->turnaroundTime, (float)currentProcess->turnaroundTime / currentProcess->burstTime);
                completed++;
            }
            else
            {
                Enqueue(&queue, currentProcess);
            }
        }
        else
        {
            currentTime++;
        }
    }
    results[0] = sumWaittime / num;
    results[1] = totalTurnaroundTime / num;
    printf("平均等待时间为%.2f\n平均周转时间为%.2f\n\n", sumWaittime / num, totalTurnaroundTime / num);
}