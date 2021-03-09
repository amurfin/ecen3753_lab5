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
