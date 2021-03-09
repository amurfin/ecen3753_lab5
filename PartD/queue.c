#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

struct node_t* create_queue(struct task_t* task, int size) {
    struct node_t * head = NULL;
    for (int i = 0; i < size; i++)
    {
        if (is_empty(&head))
            head = create_new_node(&task[i]);
        else
            push(&head, &task[i]);
    }
    return head;
}

struct node_t* create_new_node(struct task_t* task) {
    struct node_t * newNode = (struct node_t *) malloc(sizeof(struct node_t));
    newNode->task = task;
    newNode->next = NULL;
    return newNode;
}

struct task_t* peek(struct node_t** head) {
    return (* head)->task;
}

void pop(struct node_t** head) {
    struct node_t * oldHead = * head;
    (*head) = (*head)->next;
    free(oldHead);
}

void push(struct node_t** head, struct task_t* task) {
    struct node_t * currNode = * head;
    struct node_t * newNode = create_new_node(task);
    while (currNode->next != NULL)
        currNode = currNode->next;
    newNode->next = NULL;
    currNode->next = newNode;
}

int is_empty(struct node_t** head) {
    if ((*head) == NULL)
        return 1;
    else
        return 0;
}

void empty_queue(struct node_t** head) {
    while (!is_empty(head))
        pop(head);
}

void update_priority(struct node_t** head, int time) {
    struct node_t * currNode = * head;
    while (1)
    {
        // if current time = task's execution time, priority *= 4
        if (currNode->task->execution_time == time)
            currNode->task->priority *= 4;
        // if current time = task's time left to execute, priority *= 2
        // else if because we don't want to *= 8 when execution_time == left_to_execute
        else if (currNode->task->left_to_execute == time)
            currNode->task->priority *= 2;
        // escape case (end of queue)
        if (currNode->next == NULL)
            break;
        // continue case (not end of queue)
        else
            currNode = currNode->next;
    }
}
