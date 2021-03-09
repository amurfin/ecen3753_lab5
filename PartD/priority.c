#include "priority.h"
#include "queue.h"
#include <stdio.h>

void init(struct task_t *task, int *execution, int *priority, int size) {
    for (int i = 0; i < size; i++)
    {
        task[i].process_id = i;
        task[i].execution_time = execution[i];
        task[i].waiting_time = 0;
        task[i].turnaround_time = 0;
        task[i].priority = priority[i];
        task[i].left_to_execute = execution[i];
    }
}

void priority_schedule(struct task_t *task, int size) {
    // Hints:
    // 1. Create Queue based on the task array in the correct order
    // 2. Each task can be processed for a time interval of 1 (i.e quantum time of 1)
    // 3. You can process by pushing and popping items from the queue
    // 4. You must recalculate the priorities after every turn

    // create queue, not worrying about ordering since algorithm re-orders constantly
    struct node_t * priorityQueue = NULL;
    priorityQueue = create_queue(task, size);

    // create tick
    int scheduler_tick = 0;

    // IDEA:
    // run update_priority()
    // peek through queue to find highest priority value - store for compare
    // pop thru to get to the previously found priority task (re-push popped tasks to queue)
    // when at the proper task, process for 1 time unit
    // if that completed task, pop
    // increment tick
    struct task_t * currTask;
    struct node_t * savedHead;
    int currHighestPriority;
    while (!is_empty(&priorityQueue))
    {
        // run update_priority()
        update_priority(&priorityQueue, (scheduler_tick + 1));

        // peek through queue to find highest priority value - store for compare
        savedHead = priorityQueue;
        currTask = peek(&priorityQueue);
        currHighestPriority = currTask->priority;
        while (1)
        {
            if (priorityQueue->next == NULL)
                break;
            else
                priorityQueue = priorityQueue->next;
            currTask = peek(&priorityQueue);
            if (currTask->priority > currHighestPriority)
                currHighestPriority = currTask->priority;
        }
        priorityQueue = savedHead;

        // pop thru to get to the previously found priority task (re-push popped tasks to queue)
        currTask = peek(&priorityQueue);
        while (currTask->priority != currHighestPriority)
        {
            // pop
            pop(&priorityQueue);
            // re-push to bottom of stack
            push(&priorityQueue, currTask);
            // peek new task
            currTask = peek(&priorityQueue);
        }

        // w/task to process now at top of queue, process task for 1 time quanta
        currTask->left_to_execute -= 1;
        scheduler_tick += 1;
        // if that task just completed, update waiting and turnaround times and pop for good
        if (currTask->left_to_execute == 0)
        {
            currTask->waiting_time = scheduler_tick - currTask->execution_time;
            currTask->turnaround_time = scheduler_tick;
            pop(&priorityQueue);
        }
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
