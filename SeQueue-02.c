/*********************************ex02.c*********************************/

/* 要求：用户每次输入一个数字，输入的数字大于0，则该数字入队
 * 输入的数字小于0，则弹出队头元素
 * 输入0，则终止输入，并输出在队列中的元素 
 */

#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXSIZE 50
#define OVERFLOW 2

typedef int Status;
typedef struct
{
    int* data;
    int front;
    int rear;
} LinkQueue;

Status init(LinkQueue* LQ) //初始化
{
    LQ->data = (int*)malloc(MAXSIZE * sizeof(int)); //开辟内存空间
    if (!LQ->data) //开辟失败，直接退出
    {
        exit(OVERFLOW);
    }
    LQ->front = 0;
    LQ->rear = 0;
    return OK;
}

Status push(LinkQueue* LQ, int e) //入队，每次入队成功，尾指针rear+1，如果到达尾部，则不会再进行存储
{
    if ((LQ->rear + 1) % MAXSIZE == LQ->front) //判断是否为满
    {
        printf("Queue full! %d can't enqueue!\n", e);
        return ERROR;
    }
    LQ->data[LQ->rear] = e;
    LQ->rear = (LQ->rear + 1) % MAXSIZE;
    printf("%d enqueued.\n", e);
    return OK;
}

Status isFull(LinkQueue* LQ) //判断是否为空
{
    if (LQ->front == LQ->rear)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

Status pop(LinkQueue* LQ, int e) //出队，每次出队成功，头指针front+1，如果队空，则无法出队
{
    if (isFull(LQ)) //判断是否为空 
    {
        printf("Queue empty!\n");
        return ERROR;
    }
    e = LQ->data[LQ->front];
    LQ->front = (LQ->front + 1) % MAXSIZE;
    printf("%d dequeued.\n", e);
    return OK;
}

Status del(LinkQueue* LQ)
{
    free(LQ);
    return OK;
}

Status print(LinkQueue* LQ) //输出队列中的元素
{
    if (isFull(LQ))
    {
        return ERROR;
    }
    int i = LQ->front;
    while (i != LQ->rear)
    {
        printf("%d  ", LQ->data[i]);
        i = (i + 1) % MAXSIZE;
    }
    printf("\n");
    return OK;
}

int getLength(LinkQueue *LQ) //获取长度
{
    return ((LQ->rear - LQ->front + MAXSIZE) % MAXSIZE);
}

int main()
{
    LinkQueue LQ;
    init(&LQ);
    int num;
    int e;
    printf("Enter:\n");
    do
    {
        scanf("%d", &num);
        getchar();
        if (num > 0)
        {
            push(&LQ, num);
        }
        else if (num < 0)
        {
            pop(&LQ, e);
        }
    } while (num != 0);
    print(&LQ);
    return 0;
}
