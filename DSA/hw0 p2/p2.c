#include <stdio.h> 
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
/* 
+ = LONG_MAX-1
- = LONG_MAX-2
* = LONG_MAX-3
/ = LONG_MAX-4
% = LONG_MAX-5
= = LONG_MAX-6
( = LONG_MAX-7
) = LONG_MAX-8
*/


typedef struct Stack { // we set a stack structure
    size_t size; // the current size of stack
    size_t capacity;// maximum size
    size_t top; // the index now
    char *charelement; // we'll use this char array to store the numbers and operators 
    long long * numelement;
} stack; // next time we can call the Stack "stack"

char infix [1000000]="";
//long long postfix [1500000]={0};


stack * new_stack(int length); // constructor of the stack with specific length
void delete_stack(stack *self);
bool is_empty( stack *self);// "true" means it is empty 
char peekchar( stack *self);
bool pushchar(stack *self, char data);
bool expandchar(stack *self);
char popchar(stack *self);
long long popnum(stack *self);
bool expandnum(stack* self);
bool pushnum(stack *self, long long  data);

stack * new_stack(int length)               
{                                                       
    stack *st = (stack*)malloc(sizeof(stack));  // assign memeory for st
    if (!st){
        return st;   // return a null pointer
        printf("i think we are in trouble now ");
    }                                            
    st->top = 0; 
    st->capacity = length;
    st->size=0;  // it stored nothing now   
    st->charelement = (char*)malloc(st->capacity*sizeof(char));
    st->numelement = (long long*)malloc(st->capacity*sizeof(long long));                                   

    return st;                                        
}
  
// true if it is empty
bool is_empty(stack *self)
{
    assert(self);
    if(self->size == 0){
        return true;
    }
}

char peekchar(stack *self)
{
    assert(!is_empty(self));

    return self->charelement[self->top];
}

char peeklong(stack *self)
{
    assert(!is_empty(self));

    return self->numelement[self->top];
}

bool pushchar(stack *self, char data)
{
    if (expandchar(self)==false){//we can't expand it now
        return false;
    }
    if (self->size > 0){
        self->top = (self->top + 1) % self->capacity;
    }

    self->charelement[self->top] = data;
    self->size++;

    return true;
}

bool expandchar(stack* self){
    if (self->size < self->capacity) {
        return true;
    }

    size_t originalsize = self->size;
    char *old = self->charelement;
    self->capacity = self->size*2;// just expand it by 2
    char *new = malloc(self->capacity*sizeof(char));
    
    if (new==NULL){
        return false;
    }
    // self->size somehow represent the original size
    size_t index =0;
    int i = self->top;
    int j = self->top;
    while (index < self->capacity){
        new[i]=old[j];

        if (i == 0) {
            i = self->capacity-1;
        } else {
            i--;
        }
        if (j == 0) {
            j = self->size-1;
        } else {
            j--;
        }
        index++;
    }
    
    self->charelement= new;
    free(old);

    return true;

}

bool pushnum(stack *self, long long  data)
{
    if (expandnum(self)==false)//we can't expand it now
        return false;

    if (self->size > 0){
        self->top = (self->top + 1) % self->capacity;
    }
        

    self->numelement[self->top] = data;
    self->size++;

    return true;
}

bool expandnum(stack* self){
    if (self->size < self->capacity) {
        return true;
    }

    size_t originalsize = self->size;
    long long *old = self->numelement;
    self->capacity = self->size*2;// just expand it by 2
    long long *new = malloc(self->capacity*sizeof(long long));
    
    if (new==NULL){
        return false;
    }
    // self->size somehow represent the original size
    size_t index =0;
    int i = self->top;
    int j = self->top;
    while (index < self->capacity){
        new[i]=old[j];

        if (i == 0) {
            i = self->capacity-1;
        } else {
            i--;
        }
        if (j == 0) {
            j = self->size-1;
        } else {
            j--;
        }
        index++;
    }
    
    self->numelement= new;
    free(old);

    return true;

}

// +, -, *, /, %,
// if op1 is higher than op2 than return true
bool precedence (long long op1,long long op2){
    int level1,level2;
    switch( op1 )
    {
        case LONG_MAX-1: // +
            level1 = 0;
        case LONG_MAX-2: // -
            level1 = 0;
        case LONG_MAX-3: // *
            level1 = 1;
        case LONG_MAX-4: // /
            level1 = 1;
        case LONG_MAX-5: // %
            level1 = 1;
    }
    switch( op2 )
    {
        case LONG_MAX-1: // +
            level2 = 0;
        case LONG_MAX-2: // -
            level2 = 0;
        case LONG_MAX-3: // *
            level2 = 1;
        case LONG_MAX-4: // /
            level2 = 1;
        case LONG_MAX-5: // %
            level2 = 1;
    }  
    if (level1>level2){
        return true;
    }
    else{
        return false;
    }
}

char popchar(stack *self){
    char popped = self->charelement[self->top];

    if(self->top == 0 ){
        self->top= self->capacity-1;
    }
    else{
        self->top--;
    }
    self->size--;
    return popped;
}

long long popnum(stack *self){
    long long popped = self->numelement[self->top];

    if(self->top == 0 ){
        self->top= self->capacity-1;
    }
    else{
        self->top--;
    }
    self->size--;
    return popped;
}

int isoperand(char oper){
    switch( oper )
    {
        case '+':
            return 1;
        case '-':
            return 2;
        case '*':
            return 3;
        case '/':
            return 4;
        case '%':
            return 5;
        case '(':
            return 6;
        case ')':
            return 7;
        case '=':
            return 8 ;
        default:
            return 0;
    } 

}


int main(int argc, char* argv[]){


  
  stack *operator = new_stack(3); // which only store operator as a approximaiton to LONG_MAX
  for (long long i =0; i<10; i++){
    pushnum(operator,i);
  }

  int k =10;
  

  for (int i = 0; i < k;i++){
      printf( "%d", operator->numelement[i] );
  }
    

        


    return 0;
}