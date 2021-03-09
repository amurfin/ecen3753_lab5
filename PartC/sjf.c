#include "sjf.h"
#include "queue.h"
#include <stdio.h>

void init(struct task_t *task, int *execution, int size) {
    for (int i = 0; i < size; i++)
    {
        task[i].process_id = i;
        task[i].execution_time = execution[i];
        task[i].waiting_time = 0;
        task[i].turnaround_time = 0;
    }
}

void shortest_job_first(struct task_t *task, int size) {
    // 1. Create Queue based on the task array in the correct order
    // Re-arrange task array in order of lo->hi execution time
    int tempProcessID;
    int tempExecutionTime;
    // loop # of iterations of size so algorithm fixes entire array
    for (int i = 0; i < size; i++)
    {
        // go through each element, swap if next item is of smaller size
        for (int i = 0; i < (size - 1); i++)
        {
            if (task[i + 1].execution_time < task[i].execution_time)
            {
                // copy current task data into local temp
                tempProcessID = task[i].process_id;
                tempExecutionTime = task[i].execution_time;
                // put elements of next task into current
                task[i].process_id = task[i + 1].process_id;
                task[i].execution_time = task[i + 1].execution_time;
                // put former elements of current task into next task
                task[i + 1].process_id = tempProcessID;
                task[i + 1].execution_time = tempExecutionTime;
            }
        }
    }
    // with task array properly ordered for SJF - create Queue
    struct node_t * sjfQueue = create_queue(task, size);
    // 2. Process each "task" until completion
    struct task_t * prevTask = NULL;
    while (!is_empty(&sjfQueue))
    {
        struct task_t * currTask = peek(&sjfQueue);
        if (prevTask == NULL)
            currTask->waiting_time = 0;
        else
        {
            currTask->waiting_time = prevTask->waiting_time + prevTask->execution_time;
            if (currTask->waiting_time < 0)
                currTask->waiting_time = 0;
        }
        currTask->turnaround_time = currTask->waiting_time + currTask->execution_time;
        prevTask = currTask;
        pop(&sjfQueue);
    }
}

float calculate_average_wait_time(struct task_t *task, int size) {
    float total = 0.0;
    for (int i = 0; i < size; i++)
        total += task[i].waiting_time;
    return (float)total / (float)size;
}

float calculate_average_turn_around_time(struct task_t *task, int size) {
  float total = 0.0;
  for (int i = 0; i < size; i++)
      total += task[i].turnaround_time;
  return (float)total / (float)size;
}
