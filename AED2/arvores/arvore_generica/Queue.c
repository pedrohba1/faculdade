#include <stdio.h>
#include <stdlib.h>
#include "Queue.h"

struct _CELL{
    int pl;
    struct _CELL *next;
};

 struct _QUEUE{
    int size;
    struct _CELL *front, *back;
};

QUEUE* new_queue() {
    QUEUE *new = (QUEUE*) malloc(sizeof(QUEUE));
    new->front = NULL;
    new->back = NULL;
    new->size = 0;
    return new;
}

void queue_insert(QUEUE *q, int Element){
    CELL *new = (CELL*)malloc(sizeof(CELL));

    if(q->size == 0) {
        q->front = new;
        q->back = new;
    } else {
        q->back->next = new;
        q->back = new;
    }
    new->pl = Element;
    new->next = NULL;
    q->size++;
}

void queue_remove(QUEUE *q) {
    CELL *aux = q->front;
    q->front = q->front->next;
    free(aux);
    q->size--;
    return;
}

int queue_front(QUEUE *q) {
    return q->front->pl;
}

int queue_size(QUEUE *q) {
    return q->size;
}

int empty_queue(QUEUE *q){
    if(q->size == 0)
        return 1;
    else
        return 0;
}
