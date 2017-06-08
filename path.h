#ifndef PATH_H
#define PATH_H

#define CAPACITY 1024

typedef volatile struct stack stack_t;

struct stack {
  int stack[CAPACITY];
  //As in lecture, head should be the index in the array where you will next dequeue (remove) an element,
  int top;
};

stack_t *stack_new();

int isEmpty();

int isFull();

int push(int i);

int pop();

int peek();
#endif
