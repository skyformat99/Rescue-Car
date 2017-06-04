tatic stack[MAX_ELEM];
static top = -1;
// data structure:

typedef volatile struct stack stack_t;


struct stack {
    int stack[CAPACITY];
    //As in lecture, head should be the index in the array where you will next dequ
eue (remove) an element,
    int top;
};

stack_t *stack_new(){
    stack_t *stack_array = (stack_t *) malloc();
    
}

int isEmpty(){
  return (top == -1);
}

int isFull(){
  return (top == MAX_ELEM-1);
}

int push(int i){
  stack[++top] = i;
}

int pop(){
  return stack[top--];
}

int peek(){
  return stack[top];
}

