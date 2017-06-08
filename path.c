// data structure:

/*typedef volatile struct stack stack_t;
struct stack {
    int stack[CAPACITY];
    //As in lecture, head should be the index in the array where you will next dequ
eue (remove) an element,
    int top;
    };*/

#define MAX_ELEM 128
int stack[MAX_ELEM];
int top = -1;

/*stack_t *stack_new(){
    stack_t *st = (stack_t *) malloc();  
    stac
    }*/

int isEmpty(){
  return (top == -1);
}

int isFull(){
  return (top == MAX_ELEM-1);
}

void push(int i){
  if (!isFull()) stack[++top] = i;
}

int pop(){
  if (!isEmpty()) return stack[top--];
  else return -1;
}

int peek(){
  return stack[top];
}
