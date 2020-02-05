#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define STACK_ERR INT_MIN; // -2 billion and something
// STACK_ERR === INT_MIN, which is ^

typedef struct Stack
{
  // our actual stack, where the info actually goes
  int *array;
  // current spot in your array thats on the "top"
  int top;
  // how much our stack can hold
  int capacity;
} Stack;

// This is called a functional prototype. - lets you use it before its declared  and has to be after the struct because it uses the struct in it
int isFull(Stack *s);
int isEmpty(Stack *s);


// Creates a stack dynamically and returns its pointer
Stack *create_stack(int capacity)
{
  Stack *stackname = malloc(sizeof(Stack)); //must be a pointer because malloc returns memory addresses
  stackname->capacity = capacity; // must be dereferenced because it only has the address
  stackname->top = -1;
  stackname->array = malloc(sizeof(int)*capacity);
  return stackname;
}

// Adds an element to our stack
void push(Stack *s, int data)
{
  if (isFull(s))
  {
    printf("Error! Stack is full!");
    return;
  }
  
  s->array[++s->top] = data; //must put ++ before the number so that it adds it before the line of code is excecuted
  //you put the ++ before s and not the top because (s->top) is the number youre modifying

  
}

// Gets and removes the top element from stack 
int pop(Stack *s)
{
  if(isEmpty(s))
  {
    printf("Error! Stack is empty!");
    return STACK_ERR;
  }

  return s->array[s->top--];

  // x-- 
  // x -= 1
  // x = x - 1

  // print(x)
  // if(x++ == 5)
  // {}
  // print(x)
}

// Returns any nonzero number if empty, 0 otherwise
int isEmpty(Stack *s)
{
  return (s == NULL || s->top < 0);
}

// Returns nonzero if full, 0 otherwise
int isFull(Stack *s)
{
  return (s == NULL || (s->capacity == s->top - 1));// if the order was switched it would be bad because we could seg fault by checking the capacity (dereferencing) first which could mean dereferencing a NULL pointer
}

// Checks the top element on our stack
int peek(Stack *s)
{
  if(isEmpty(s)) // 0 == false and any other non zero # == true
  {
    printf("Error! The stack is empty!\n");
    return STACK_ERR;
  }
  return s->array[s->top];
}

// free any allocated memory
Stack *jenga(Stack *s)
{
  free(s->array);//You need to free array first because it is inside the stack so if you free the stack first you will lose the arra
  free(s);
  return NULL;
}

void print_stack(Stack *s)
{
  int i;
  if (isEmpty(s))
  {
    printf("The stack is empty!\n");
    return;
  }

  for (i = 0; i <= s->top; i++)
    printf("%d, ", s->array[i]);
  printf("\n");

}

int main(void) {
  // create a stack of 5 capacity.
  Stack *s = create_stack(5);
  push(s, 1);
  push(s, 7);
  push(s, 10);
  printf("%d was just popped!\n", pop(s));
  printf("%d is now at the top of our stack!\n", peek(s));
  print_stack(s);
  jenga(s);
  
  return 0;
}

// 4 ways you can seg fault
// =========================
// 1. dereferencing a NULL pointer
// 2. dereferencing an uninitalized pointer
// 3. Going out of bounds of your array
// 4. Going so far out of bounds, you exceed the memory allowed for your program to run

// short circuiting
/*
  True && True = True = 112323423
  False && True = False = 0
  True || True = True = 1
  True || False = True = -1

Only checks the first one if it needs to
*/
