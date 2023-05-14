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

char infix [1000000];
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
    if (!st){// st is a null pointer
        return st;   
        printf("i think we are in trouble now ");
    }                                            
    st->top = 0; // the end of the stack 
    st->capacity = length;
    st->size=0;  // the number of element stores in stack  
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
    else{
        return false;
    }
}

char peekchar(stack *self)
{
    assert(!is_empty(self));

    return self->charelement[self->top];
}

long long peeklong(stack *self)
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
    
    self->charelement = new;
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


print    return true;
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
// if op1 is higher or equal than op2 than return true
bool precedence (long long op1,long long op2){
    int level1,level2;
    switch( op1 )
    {
        case LONG_MAX-1: // +
            level1 = 0;
            break;
        case LONG_MAX-2: // -
            level1 = 0;
            break;
        case LONG_MAX-3: // *
            level1 = 1;
            break;
        case LONG_MAX-4: // /
            level1 = 1;
            break;
        case LONG_MAX-5: // %
            level1 = 1;
            break;
        case LONG_MAX-7: // (
            level1 = 2;
            break;
    }
    switch( op2 )
    {
        case (LONG_MAX-1): // +
            level2 = 0;
            break;
        case (LONG_MAX-2): // -
            level2 = 0;
            break;
        case (LONG_MAX-3): // *
            level2 = 1;
            break;
        case (LONG_MAX-4): // /
            level2 = 1;
            break;
        case (LONG_MAX-5): // %
            level2 = 1;
            break;
        case (LONG_MAX-7): // (
            level2 = 2;
            break;
    } 

    if (level1<level2){
        return false;
    }
    else{
        return true;
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

long long evalutepostfix(stack *self){

    long long ans=0;
    stack *calculation = new_stack(3);
    long long first;
    long long second;
    long long result;
    long long index =0;
    while(index<self->size){

        switch(self->numelement[index]){
            case LONG_MAX-1://'+'
                
                second = popnum(calculation);
                first = popnum(calculation);
                result = first+second;
                pushnum(calculation,result);
                printf("\nthis is %lld plus %lld \n",first,second);
                first=0;
                second=0;
                result=0;

                break;
            case LONG_MAX-2://'-'
                second = popnum(calculation);
                first = popnum(calculation);
                result = first-second;
                pushnum(calculation,result);
                printf("\nthis is %lld minus %lld \n",first,second);
                first=0;
                second=0;
                result=0;
                
                
                break;
            case LONG_MAX-3://'*'
                second = popnum(calculation);
                first = popnum(calculation);
                result = first*second;
                pushnum(calculation,result);
                printf("\nthis is %lld multiply %lld \n",first,second);
                first=0;
                second=0;
                result=0;

                break;
            case LONG_MAX-4://'/'
                second = popnum(calculation);
                first = popnum(calculation);
                // if one is positive and the other is negative 
                if((first>0&&second<0)||(first<0&&second>0)){
                    if (first%second!=0){
                        result = first/second-1;
                    }
                    else{
                        result = first/second;
                    }
                }
                else
                {
                        result = first/second;
                }
                printf("\nthis is %lld devide %lld \n",first,second);
                pushnum(calculation,result);
                first=0;
                second=0;
                result=0;

                break;
            case LONG_MAX-5://'%'
                second = popnum(calculation);
                first = popnum(calculation);
                result = first%second;
                printf("\nthis is %lld mod %lld \n",first,second);
                pushnum(calculation,result);
                first=0;
                second=0;
                result=0;

                break;
            default:
                //push the number into the stack
                pushnum(calculation,self->numelement[index]);
                break;
        }
        
        index++;
    }
    for(int i =0; i< self->size;i++){
        self->numelement[i]=0;
    }
    ans = popnum(calculation);
    self->numelement[0]=ans;
    self->top =0;
    self->size =1;

    
    return ans;
    
}


int main(int argc, char* argv[]){

    
    
    stack *operator = new_stack(3); // which only store operator as a approximaiton to LONG_MAX
    stack *postfix = new_stack(3); // which store postfix numbers and operator 
    
    
    scanf("%s", infix); // read all the number into infix 
    long long orilength = strlen(infix);
    long long trash;
    long long ans;
    
    printf("\nthis is the original input: ");
    for (int i = 0; i < orilength ;i++){
        printf( "%c", infix[i] );
    }
    
    int countoperands=0; 
    long long tempnum = 0;
    for (int i = 0; i< orilength; i++)
    {
        
        
        // if is an operand, count and then add it to postfix
        if (isoperand(infix[i])==0){
            tempnum = tempnum*10 + (long long)(infix[i]-'0');
            countoperands++;
            
        }    
        // If it is ‘(‘, push it to the operator and push the number before it into postfix
        else if (infix[i] == '('){
            if (tempnum!=0){
                printf( "we push  %d\n",tempnum);
                pushnum(postfix,tempnum);
                tempnum=0;
                printf( "\npostfix has the length of %d\n",postfix->size );
                printf( "postfix top at %d\n",postfix->top );
            }
            
            pushnum(operator, LONG_MAX-7);
            printf( "\nthere are %d things in stack of operator\n",operator->size );
        }
         
        // If it is an ‘)’ pop operators from stack until we meet ‘(‘ 
        else if (infix[i] == ')'){
            // we first push the number
            if (tempnum!=0){
                printf("\nwe push  %d\n",tempnum);
                pushnum(postfix,tempnum);
                tempnum=0;
                printf( "\npostfix has the length of %d\n",postfix->size );
                printf( "postfix top at %d\n",postfix->top );
            }
            // operator is not empty and we haven't met (
            while (!is_empty(operator) && peeklong(operator) != LONG_MAX-7){ 
                long long temppostfix = popnum(operator);
                printf("\nwe push  %d\n",temppostfix);
                pushnum(postfix,temppostfix);

                printf( "\npostfix has the length of %d\n",postfix->size );
                printf( "postfix top at %d\n",postfix->top );
            
            }
            trash = popnum(operator);// clear the '(' in the stack
            trash=0;
            
        }
        else if (infix[i]=='='){
            // push the last number first
            if (tempnum!=0){
                printf("\nwe push %d\n",tempnum);
                pushnum(postfix,tempnum);
                tempnum=0;
                printf( "\npostfix has the length of %d\n",postfix->size );
                printf( "postfix top at %d\n",postfix->top );
            }
            while (!is_empty(operator)){
                long long temppostfix = popnum(operator);
                printf("\nwe push  %d\n",temppostfix);
                pushnum(postfix,temppostfix);
                printf( "\npostfix has the length of %d\n",postfix->size );
                printf( "postfix top at %d\n",postfix->top );
            }
            ans = evalutepostfix(postfix);
            printf("\n\nthis is ans: %d\n\n ",ans);
            
        }
        else // meet operator
        {
            long long tempoper;
            // we first push the number to postfix
            if (tempnum!=0){
                printf("\nwe push %lld\n",tempnum);
                pushnum(postfix,tempnum);
                tempnum=0;
                printf( "\npostfix has the length of %d\n",postfix->size );
                printf( "postfix top at %d\n",postfix->top );
            }
            //change operator to long long 
            switch(infix[i]){
                case '+':
                    tempoper = LONG_MAX-1;
                    break;
                case '-':
                    tempoper = LONG_MAX-2;
                    break;
                case '*':
                    tempoper = LONG_MAX-3;
                    break;
                case '/':
                    tempoper = LONG_MAX-4;
                    break;
                case '%':
                    tempoper = LONG_MAX-5;
                    break;
            }
            
            //stack is not empty and operators in stack has higher or same precedence 
            //we do not push '('
     
            while (!is_empty(operator) && precedence(operator->numelement[operator->top],tempoper) && (peeklong(operator) != LONG_MAX-7)){//tempoper >= the last in stack
                long long temppostfix = popnum(operator);
                printf("\nwe push %lld\n",temppostfix);
                pushnum(postfix,temppostfix);
                printf( "\npostfix has the length of %d\n",postfix->size );
                printf( "postfix top at %d\n",postfix->top );
                
            }
            // then push the operator itself to operator in the form of long long 

            pushnum(operator, tempoper);
            printf( "\nthere are %d things in stack of operator\n",operator->size );
        }
 
    }


    printf("\nwe are out of while now \n\n");
    printf( "\npostfix has the length of %d\n",postfix->size );
    printf( "postfix top at %d\n",postfix->top );
    
    return 0;

