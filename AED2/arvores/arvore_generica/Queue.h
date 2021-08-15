#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED

typedef struct _CELL CELL;
typedef struct _QUEUE QUEUE;

QUEUE* new_queue();
void queue_insert(QUEUE *q, int Element);
void queue_remove(QUEUE *q);
int queue_front(QUEUE *q);
int queue_size(QUEUE *q);
int empty_queue(QUEUE *q);

#endif // QUEUE_H_INCLUDED
