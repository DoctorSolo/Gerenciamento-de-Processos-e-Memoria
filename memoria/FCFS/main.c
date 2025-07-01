#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


#define MAX_SIZE 5


typedef void (*timeRelatedFunction)();


typedef struct{
    timeRelatedFunction items[MAX_SIZE];
    int inicio;
    int final_;
    int n_itens;
} CircularQueue;



void processo00(){
    sleep(5);
    printf("Processo 00 executado ");
}





void initializeQueue(CircularQueue *q){
    q->inicio = 1;
    q->final_ = -1;
    q->n_itens = 0;
}


int isFull(CircularQueue *q){
    return q->n_itens == MAX_SIZE;
}


int isEmpty(CircularQueue *q){
    return q->n_itens == 0;
}


void enqueue(CircularQueue *q, timeRelatedFunction item)
{
    if (isFull(q)){
        printf("Fila cheia!");
        return;
    }
    if (isEmpty(q)){
        q->inicio = 0;
    }

    q->final_ = (q->final_ + 1) % MAX_SIZE;
    q->items[q->final_] = item;
    q->n_itens++;
}


timeRelatedFunction dequeue(CircularQueue *q)
{
    if (isEmpty(q)){
        printf("Fila vazia!");
        return NULL;
    }

    timeRelatedFunction item = q->items[q->inicio];
    q->n_itens--;

    if (isEmpty(q)){
        q->inicio = -1;
        q->final_ = -1;
    } else {
        q->inicio = (q->inicio + 1) % MAX_SIZE;
    }
    item();
    return NULL;
}


void showQueue(CircularQueue *q)
{
    if (isEmpty(q)){
        printf("fila vazia");
        return;
    }
    for (int i = 0; i < q->n_itens; i++){
        printf("%p ", q->items[(q->inicio + i) % MAX_SIZE]);
    }
    printf("\n");
}


int main()
{
    CircularQueue queue01;
    initializeQueue(&queue01);

    enqueue(&queue01, processo00);
    enqueue(&queue01, processo00);
    enqueue(&queue01, processo00);
    enqueue(&queue01, processo00);
    enqueue(&queue01, processo00);

    showQueue(&queue01);

    dequeue(&queue01);
    showQueue(&queue01);

    dequeue(&queue01);
    showQueue(&queue01);
}














