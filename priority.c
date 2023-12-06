#include <stdio.h>
#include "main.h"
#include <math.h>
// 队列节点
typedef struct Node
{
    Process *process;
    struct Node *next;
} Node;

// 队列
typedef struct
{
    Node *front;
    Node *rear;
    int size;
} Queue;

// 初始化队列
void initQueue(Queue *q)
{
    q->front = q->rear = NULL;
    q->size = 0;
}

// 进入队列
void enterQueue(Queue *q, Process *p)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->process = p;
    newNode->next = NULL;

    if (q->rear == NULL)
    {
        q->front = q->rear = newNode;
    }
    else
    {
        q->rear->next = newNode;
        q->rear = newNode;
    }
    q->size++;
}

// 离开队列
Process *poll(Queue *q)
{
    if (q->front == NULL)
    {
        return NULL;
    }

    Node *temp = q->front;
    Process *p = temp->process;
    q->front = q->front->next;

    if (q->front == NULL)
    {
        q->rear = NULL;
    }

    free(temp);
    q->size--;

    return p;
}

// 按优先级排序
void sortWithPriority(Process *processes, int n)
{
    // 简单的冒泡排序
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (processes[j].priority < processes[j + 1].priority)
            {
                Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }
}
int max(int a, int b)
{
    return (a > b) ? a : b;
}

void Priority(Process *processes, int n, float *results)
{
    sortWithPriority(&processes[1], n - 1);
    printf("初始化进程序列信息：\n");
    printProcessInfo(processes, n);
    printf("进程ID 到达时间 服务时间 开始时间 完成时间 等待时间 周转时间 \n");
    Queue queue;
    initQueue(&queue);
    enterQueue(&queue, &processes[0]);

    int currentTime = processes[0].arrivalTime;
    int completedProcesses = 0;
    float sum_T_time = 0, sum_ZZ_time = 0;

    while (queue.size > 0)
    {
        Process *currentProcess = poll(&queue);
        if (currentProcess == NULL)
        {
            break;
        }

        // 计算开始时间
        int startTime = max(currentTime, currentProcess->arrivalTime);
        int finishTime = startTime + currentProcess->burstTime;

        // 计算等待时间和周转时间
        int T_time = startTime - currentProcess->arrivalTime;   // 等待时间
        int ZZ_time = finishTime - currentProcess->arrivalTime; // 周转时间

        sum_T_time += T_time;
        sum_ZZ_time += ZZ_time;

        printf("%d\t%d\t%d\t  %d\t  %d\t  %d\t  %d\n", currentProcess->processId, currentProcess->arrivalTime, currentProcess->burstTime, startTime, finishTime, T_time, ZZ_time);

        // 更新当前时间
        currentTime = finishTime;
        // 更新已完成的进程数量
        completedProcesses++;

        // 添加新到达的进程
        for (int i = completedProcesses; i < n && processes[i].arrivalTime <= currentTime; i++)
        {
            enterQueue(&queue, &processes[i]);
            completedProcesses++;
        }

        // 如果队列为空且仍有未处理的进程
        if (queue.size == 0 && completedProcesses < n)
        {
            enterQueue(&queue, &processes[completedProcesses]);
        }
    }
    results[0] = sum_T_time / n;
    results[1] = sum_ZZ_time / n;
    printf("平均等待时间为%.2f\n平均周转时间为%.2f\n", sum_T_time / n, sum_ZZ_time / n);
}