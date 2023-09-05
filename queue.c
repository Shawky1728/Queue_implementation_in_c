#include "queue.h"

/*
 * @brief     check Queue is full
 * @parameter Queue_t pointer to stack
 * @return    uint8_t 1 or 0
 */

static uint8_t QueueIsFull(Queue_t *queue_obj)
{

    return (queue_obj->elementCount == queue_obj->queueMaxSize);
}

/*
 * @brief     check Queue is Empty
 * @parameter Queue_t pointer to stack
 * @return    uint8_t 1 or 0
 */

static uint8_t QueueIsEmpty(Queue_t *queue_obj)
{

    return (queue_obj->elementCount == 0);
}

/*
 * @brief     creat Queue
 * @parameter uint32_t MaxSize for Queue
 * @parameter status pointer to Queue
 * @return    A pointer to Queue created
 */

Queue_t *CreatQueue(uint32_t MaxSize, QueueStatus_t *status)
{

    Queue_t *myreturn = NULL;

    if (NULL == status)
    {
        *status = QUEUE_NULL_POINTER;
    }
    else
    {
        myreturn = (Queue_t *)malloc(sizeof(Queue_t));
        if (NULL == myreturn)
        {
            *status = QUEUE_NULL_POINTER;
            myreturn = NULL;
        }
        else
        {
            myreturn->elementCount = 0;
            myreturn->queueFront = -1;
            myreturn->queueRear = -1;
            myreturn->queueMaxSize = MaxSize;
            myreturn->queueArray = (void **)calloc(MaxSize, sizeof(void *));
            if (NULL == myreturn->queueArray)
            {
                *status = QUEUE_NULL_POINTER;
                free(myreturn);
            }
            else
            {
#ifdef DEBUG
                printf("the queue with size %d is created \n", MaxSize);
#endif
                *status = QUEUE_OK;
            }
        }
    }
    return myreturn;
}

QueueStatus_t EnqueueElement(Queue_t *queue_obj, void *item_ptr)
{

    QueueStatus_t status = QUEUE_NOK;
    if (NULL == queue_obj || NULL == item_ptr)
    {
        status = QUEUE_NULL_POINTER;
    }
    if (QueueIsFull(queue_obj))
    {
        status = QUEUE_FULL;
        item_ptr = NULL;
    }
    else
    {
        (queue_obj->queueRear)++;
        if (queue_obj->queueRear == queue_obj->queueMaxSize)
        {
            queue_obj->queueRear = 0;
        }
        queue_obj->queueArray[queue_obj->queueRear] = item_ptr;
        if (queue_obj->elementCount == 0)
        {
            queue_obj->queueFront = 0;
            queue_obj->elementCount = 1;
        }
        else
        {
            (queue_obj->elementCount)++;
        }
#ifdef DEBUG
        printf("the value %d is added to queue \n", *((uint32_t *)item_ptr));
#endif
        status = QUEUE_OK;
    }

    return status;
}

void *DequeueElement(Queue_t *queue_obj, QueueStatus_t *status)
{

    void *ReturnElement = NULL;
    if (NULL == queue_obj || NULL == status)
    {
        *status = QUEUE_NULL_POINTER;
    }
    else
    {
        if (QueueIsEmpty(queue_obj))
        {
            *status = QUEUE_EMPTY;
            ReturnElement = NULL;
        }
        else
        {
            ReturnElement = queue_obj->queueArray[queue_obj->queueFront];
            (queue_obj->queueFront)++;
            if (queue_obj->queueFront == queue_obj->queueMaxSize)
            {
                queue_obj->queueFront = 0;
            }
            else
            {
            }
            if (1 == queue_obj->elementCount)
            {
                queue_obj->queueFront = -1;
                queue_obj->queueRear = -1;
            }
            else
            {
            }
            (queue_obj->elementCount)--;
            *status = QUEUE_OK;
        }
    }
    return ReturnElement;
}

void *QueueFront(Queue_t *queue_obj, QueueStatus_t *status)
{

    void *ReturnElement = NULL;
    if (NULL == queue_obj || NULL == status)
    {
        *status = QUEUE_NULL_POINTER;
    }
    else
    {
        if (QueueIsEmpty(queue_obj))
        {
            *status = QUEUE_EMPTY;
        }
        else
        {
            ReturnElement = queue_obj->queueArray[queue_obj->queueFront];
            *status = QUEUE_OK;
        }
    }
    return ReturnElement;
}

void *QueueRear(Queue_t *queue_obj, QueueStatus_t *status)
{

    void *ReturnElement = NULL;
    if (NULL == queue_obj || NULL == status)
    {
        *status = QUEUE_NULL_POINTER;
    }
    else
    {
        if (QueueIsEmpty(queue_obj))
        {
            *status = QUEUE_EMPTY;
        }
        else
        {
            ReturnElement = queue_obj->queueArray[queue_obj->queueRear];
            *status = QUEUE_OK;
        }
    }
    return ReturnElement;
}

QueueStatus_t GetQueueCount(Queue_t *queue_obj, uint32_t *QueueCount)
{

    QueueStatus_t status = QUEUE_NOK;
    if (NULL == queue_obj || NULL == QueueCount)
    {
        status = QUEUE_NULL_POINTER;
    }
    else
    {
        QueueCount = queue_obj->elementCount;
        status = QUEUE_OK;
    }

    return status;
}

QueueStatus_t DestroyQueue(Queue_t *queue_obj)
{
    QueueStatus_t status = QUEUE_NOK;
    if (NULL == queue_obj)
    {
        status = QUEUE_NULL_POINTER;
    }
    else
    {
        if (queue_obj->queueArray != NULL)
        {
            free(queue_obj->queueArray);
        }
        free(queue_obj);
        status = QUEUE_OK;
    }
    return status;
}
