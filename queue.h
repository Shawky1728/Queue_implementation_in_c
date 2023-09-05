#ifndef QUEUE_H
#define QUEUE_H
#include "std_types.h"
#define DEBUG

// struct of Queue 

typedef struct
{
    void **queueArray;
    sint32_t queueFront;
    sint32_t queueRear;
    uint32_t elementCount;
    uint32_t queueMaxSize;
} Queue_t;

// all status will happen

typedef enum
{

    QUEUE_NOK,
    QUEUE_OK,
    QUEUE_FULL,
    QUEUE_EMPTY,
    QUEUE_NULL_POINTER
} QueueStatus_t;

Queue_t *CreatQueue(uint32_t MaxSize, QueueStatus_t *status);
QueueStatus_t EnqueueElement(Queue_t *queue_obj, void *item_ptr);
void *DequeueElement(Queue_t *queue_obj, QueueStatus_t *status);
void *QueueFront(Queue_t *queue_obj, QueueStatus_t *status);
void *QueueRear(Queue_t *queue_obj, QueueStatus_t *status);
QueueStatus_t GetQueueCount(Queue_t *queue_obj, uint32_t *QueueCount);
QueueStatus_t DestroyQueue(Queue_t *queue_obj);

#endif
