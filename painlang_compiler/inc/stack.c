#include<stdio.h>

int stack_push(int value, int stack[], int *top, int stackSize){
    /* The function pushes the int value into the stack array. */ 
    /* If the stack is not full, returns 0, otherwise returns -1.*/
 if(*top == -1){
  stack[stackSize - 1] = value;
  *top = stackSize - 1;
  return 0;
 }
 else if(*top == 0){
  #ifdef STACK_DEBUG
    printf("The stack is already full. \n");
  #endif
  return -1;
 }
 else{
  stack[(*top) - 1] = value;
  (*top)--;
  return 0;
 }
}

int stack_pop(int stack[], int *top, int stackSize){
    /* The function pops a int value into the stack array */
    /* If the stack is empty, returns 0 - the stack is implemented for the calculator 
       and the 0 value means empty stack in this case. */
 int value = 0;
 if(*top == -1){   
   #ifdef STACK_DEBUG  
   printf("The stack is empty. \n");
   #endif
   return value;
 }
 else{  
  #ifdef STACK_DEBUG
    printf("Element popped: %d \n", stack[(*top)]);
  #endif
  //If this was the last element, set stack size to -1 to see it is empty.      
  value=stack[*top];
  if((*top) == stackSize - 1){    
    (*top) = -1;
  }

  else{
    (*top)++;
    
  }
  return(value);
 }
}


