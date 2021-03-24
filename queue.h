#include "common.h"
#define MAXQUEUE    26

typedef char QueueEntry;
typedef struct queue {
    int count;
    int front;
    int rear;
    QueueEntry entry[MAXQUEUE];
} Queue;

void CreateQueue(Queue *q);
void EnQueue(QueueEntry x, Queue *q);
void DeQueue(QueueEntry *x, Queue *q);
void ClearQueue(Queue *q);
void QueueFront(QueueEntry *item, Queue *q);
void TraverseQueue(Queue *q, void (*Visit)(QueueEntry));
int QueueSize(Queue *q);
Boolean QueueEmpty(Queue *q);
Boolean QueueFull(Queue *q);

/* CreateQueue: create the queue.
 * Pre:     None.
 * Post:    The queue q has been initialized to be empty.
 * */
void CreateQueue(Queue *q) {
    q->count = 0;
    q->front = 0;
    q->rear = -1;
}

/* EnQueue: append an entry to the queue.
 * Pre:     The queue q has been created and is not full.
 * Post:    The entry x has been stored in the queue as its last entry.
 * Uses:    QueueFull, Error.
 * */
void EnQueue(QueueEntry x, Queue *q) {
    if(QueueFull(q))
        Error("Queue is full, cannot enqueue.");
    else {
        q->count++;
        q->rear = (q->rear + 1) % MAXQUEUE;
        q->entry[q->rear] = x;
    }
}

/* DeQueue: remove first entry in the queue.
 * Pre:     The queue q has been created and is not empty.
 * Post:    The first entry in the queue has been removed and returned as the
 *          value of x.
 * Uses:    QueueEmpty, Error.
 * */
void DeQueue(QueueEntry *x, Queue *q) {
    if(QueueEmpty(q))
        Error("Queue is empty, cannot dequeue.");
    else {
        q->count--;
        *x = q->entry[q->front];
        q->front = (q->front + 1) % MAXQUEUE;
    }
}

/* QueueSize: return the number of entries in the queue.
 * Pre:     The queue q has been created.
 * Post:    The function returns the number of entries in the queue.
 * */
int QueueSize(Queue *q) {
    return q->count;
}

/* QueueEmpty: returns non-zero if the queue is empty.
 * Pre:     The queue q has been created.
 * Post:    The function returns non-zero if the queue q is empty, zero
 *          otherwise.
 * */
Boolean QueueEmpty(Queue *q) {
    return q->count <= 0;
}

/* QueueFull: returns non-zero if the queue is full.
 * Pre:     The queue q has been created.
 * Post:    The function returns non-zero if the queue q is empty, zero
 *          otherwise.
 * */
Boolean QueueFull(Queue *q) {
    return q->count >= MAXQUEUE;
}

/* ClearQueue: dequeues all items in the queue.
 * Pre:     The queue q has been created and is not empty.
 * Post:    The queue q is returned as empty.
 * */
void ClearQueue(Queue *q) {
    if(QueueEmpty(q))
        Error("Queue is empty, cannot clear.");
    else {
        q->count = 0;
        q->front = 0;
        q->rear = -1;
    }
}

/* QueueFront: returns the item at the head of the queue.
 * Pre:     The queue q has been created and is not empty.
 * Post:    The item at the head of the queue has been returned as the value
 *          of x.
 * */
void QueueFront(QueueEntry *item, Queue *q) {
    if(QueueEmpty(q))
        Error("Queue is empty, cannot peek.");
    else
        *item = q->entry[q->front];
}

/* TraverseQueue:   iterates through each node in the queue performing the
 *                  function Visit on each node.
 * Pre:     The queue q has been created and is not empty.
 * Post:    The queue has been fully traversed.
 * */
void TraverseQueue(Queue *q, void (*Visit)(QueueEntry)) {
    for(int i=0; i<q->count; i++)
        (*Visit)(q->entry[(q->front+i)%MAXQUEUE]);
}
