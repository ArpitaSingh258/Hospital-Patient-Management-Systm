#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct {
    int priority;
    char name[50];
    char ailment[50];
    int age;
} Patient;

typedef struct {
    Patient heap[MAX];
    int size;
} PriorityQueue;

void initQueue(PriorityQueue* pq) {
    pq->size = 0;
}

void swap(Patient* a, Patient* b) {
    Patient temp = *a;
    *a = *b;
    *b = temp;
}

void enqueue(PriorityQueue* pq, char* name, char* ailment, int age, int priority) {
    if (pq->size >= MAX) {
        printf("Queue is full!\n");
        return;
    }

    Patient newPatient = {priority, "", "", age};
    strcpy(newPatient.name, name);
    strcpy(newPatient.ailment, ailment);

    pq->heap[pq->size] = newPatient;
    int i = pq->size;
    pq->size++;

    // Heapify up
    while (i != 0 && pq->heap[(i - 1) / 2].priority > pq->heap[i].priority) {
        swap(&pq->heap[(i - 1) / 2], &pq->heap[i]);
        i = (i - 1) / 2;
    }
}

Patient dequeue(PriorityQueue* pq) {
    if (pq->size <= 0) {
        printf("Queue is empty!\n");
        Patient emptyPatient = {-1, "", "", -1};
        return emptyPatient;
    }

    Patient root = pq->heap[0];
    pq->heap[0] = pq->heap[pq->size - 1];
    pq->size--;

    int i = 0;
    // Heapify down
    while (i < pq->size) {
        int smallest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < pq->size && pq->heap[left].priority < pq->heap[smallest].priority)
            smallest = left;

        if (right < pq->size && pq->heap[right].priority < pq->heap[smallest].priority)
            smallest = right;

        if (smallest != i) {
            swap(&pq->heap[i], &pq->heap[smallest]);
            i = smallest;
        } else {
            break;
        }
    }

    return root;
}

void displayQueue(PriorityQueue* pq) {
    if (pq->size == 0) {
        printf("Queue is empty!\n");
        return;
    }

    printf("\nCurrent Patient Queue:\n");
    printf("Priority | Name       | Age | Ailment\n");
    printf("--------------------------------------\n");
    for (int i = 0; i < pq->size; i++) {
        printf("%8d | %-10s | %3d | %s\n", pq->heap[i].priority, pq->heap[i].name, pq->heap[i].age, pq->heap[i].ailment);
    }
}

int main() {
    PriorityQueue pq;
    initQueue(&pq);

    enqueue(&pq, "Alice", "Flu", 30, 3);
    enqueue(&pq, "Bob", "Heart Attack", 65, 1);
    enqueue(&pq, "Charlie", "Broken Arm", 25, 2);

    displayQueue(&pq);

    printf("\nTreating Patient: %s\n", dequeue(&pq).name);
    displayQueue(&pq);

    printf("\nTreating Patient: %s\n", dequeue(&pq).name);
    displayQueue(&pq);

    return 0;
}