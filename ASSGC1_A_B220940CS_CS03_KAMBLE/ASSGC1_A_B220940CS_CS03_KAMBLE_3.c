#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct patient {
  char name[50];
  int priority;
  char admittime[20];
};

struct pqueue {
  struct patient *heap;
  int size;
  int capacity;
};

void swap(struct patient *a, struct patient *b) {
  struct patient temp = *a;
  *a = *b;
  *b = temp;
}

void heapify(struct pqueue *pq, int index) {
  int largest = index;
  int lchild = 2 * index + 1;
  int rchild = 2 * index + 2;

  if (lchild < pq->size && (pq->heap[lchild].priority > pq->heap[largest].priority ||
         (pq->heap[lchild].priority == pq->heap[largest].priority &&
          strcmp(pq->heap[lchild].admittime, pq->heap[largest].admittime) < 0)))
    largest = lchild;
  if (rchild < pq->size && (pq->heap[rchild].priority > pq->heap[largest].priority ||
         (pq->heap[rchild].priority == pq->heap[largest].priority &&
          strcmp(pq->heap[rchild].admittime, pq->heap[largest].admittime) < 0)))
    largest = rchild;
  if (largest != index) {
    swap(&pq->heap[index], &pq->heap[largest]);
    heapify(pq, largest);
  }
}

struct patient createpatient(char name[], int priority, char admittime[]) {
  struct patient ptient;
  strcpy(ptient.name, name);
  ptient.priority = priority;
  strcpy(ptient.admittime, admittime);
  return ptient;
}

struct pqueue intializepqueue(int capacity) {
  struct pqueue pq;
  pq.heap = (struct patient *)malloc(capacity * sizeof(struct patient));
  pq.size = 0;
  pq.capacity = capacity;
  return pq;
}

void buildmaxheap(struct pqueue* pq) {
  for (int i = (pq->size)/ 2 - 1; i >= 0; i--) {
    heapify(pq, i);
  }
}

void insertpatient(struct pqueue *pq, struct patient ptient) {
  if (pq->size == pq->capacity) {
    return;
  }

  pq->heap[pq->size] = ptient;
  int i = pq->size;
  pq->size++;

  buildmaxheap(pq);
}

void treatnextpatient(struct pqueue *pq) {
  if(pq->size == 0) {
    return;
  }

  printf("%s %d %s\n", pq->heap[0].name, pq->heap[0].priority, pq->heap[0].admittime);

  swap(&pq->heap[0], &pq->heap[pq->size - 1]);
  pq->size--;
  buildmaxheap(pq);
}

void checknextpatient(struct pqueue *pq) {
  if(pq->size == 0)
    return;

  printf("%s %d %s\n", pq->heap[0].name, pq->heap[0].priority, pq->heap[0].admittime);
}

void dischargepatient(struct pqueue *pq, char name[], char admittime[]) {
  int i;
  for (i = 0; i < pq->size; i++) {
    if(strcmp(pq->heap[i].name, name) && strcmp(pq->heap[i].admittime, admittime))
      break;
  }

  pq->heap[i] = pq->heap[pq->size-1];
  pq->size--;
  buildmaxheap(pq);
}

void updatepriority(struct pqueue *pq, char name[], char admittime[], int npriority) {
  int i;
  for (i = 0; i < pq->size; i++) {
    if(strcmp(pq->heap[i].name, name) == 0 && strcmp(pq->heap[i].admittime, admittime) == 0)
      break;
  }
  if(i == pq->size)
    return;

  pq->heap[i].priority = npriority;

  buildmaxheap(pq);
}

void printpatients(struct pqueue *pq) {
  if(pq->size == 0)
    return;
  for (int i = pq->size - 1; i >= 0; i--) {
    swap(&pq->heap[0], &pq->heap[i]);
    heapify(pq, i);
  }
  for (int i = 0; i < pq->size; i++) {
    printf("%s %d %s\n", pq->heap[i].name, pq->heap[i].priority, pq->heap[i].admittime);
  } 
  buildmaxheap(pq);
}

int main() {
  struct pqueue pq = intializepqueue(100);

  char op;
  char name[50];
  int priority;
  char admittime[50];

  while (1) {
    scanf(" %c", &op);
    switch (op) {
      case 'a':
        scanf("%s %d %s", name, &priority, admittime);
        insertpatient(&pq, createpatient(name, priority, admittime));
        break;
      case 't':
        treatnextpatient(&pq);
        break;
      case 'c':
        checknextpatient(&pq);
        break;
      case 'd':
        scanf("%s %s", name, admittime);
        dischargepatient(&pq, name, admittime);
        break;
      case 'u':
        scanf("%s %s %d", name, admittime, &priority);
        updatepriority(&pq, name, admittime, priority);
        break;
      case 'p':
        printpatients(&pq);
        break;
      case 'e':
        return 0;
    }
  }  
}
