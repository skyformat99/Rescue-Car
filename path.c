#define MAX_ELEM 128

static int stack[MAX_ELEM];
static int top = -1;

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
