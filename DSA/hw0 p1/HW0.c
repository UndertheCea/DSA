#include<stdio.h> // header files  
#include <string.h>
#include <stdbool.h>

int compare(int [], int [],int ,int );
bool iszero(int[],int); // enter the array and the length of it 
bool iseven(int[]); // enter the array 
void devidebytwo(int*, int * );
void swaparray( int *, int *,int*,int*);
void subtract(int*,int*,int*,int);
void multiply (int*,int*,int* );//intarray1//arr//length of array1 

int main(int argc, char* argv[]) {
    
    char number1 [257]; // include null
    char number2 [257];

    //read the number with string format 
    scanf("%s %s", number1, number2); //One line containing two integers, a and b 
    int len1 = strlen(number1);
    int len2 = strlen(number2);
    int intarray1 [256]={0};
    int intarray2 [256]={0};
    int ans [256]={0};
    int two [256]= {0};
    two[0] =2;
    
    // convert the char arry into integer array with exact size and inverse it  
    for(int i=len1-1;i>=0;i--){ 
        
        intarray1[len1-1-i] = (int)(number1[i]-'0');
        
    } 

    for(int i=len2-1;i>=0;i--){ 
        intarray2[len2-1-i] = (int)(number2[i]-'0');
        
    } 

    int thelarge = compare(intarray1,intarray2,len1,len2);
    printf("\nthe larger array is %d\n",thelarge);

    // we always assume that array1 is smaller
    if(thelarge==1){ // if intarray1 is larger, then we should swap   
        swaparray(intarray1,intarray2,&len1,&len2);//enter the larger array first 

    }
    

    ans[0]=1;
    int lenans = 1;
    



    while(iszero(intarray1,len1)==false && iszero(intarray2,len2)==false){//just make sure to update the length whenever it is changed 
        if(iseven(intarray1)==true && iseven(intarray2)==true){
            multiply(ans,two,&lenans);
            
            printf("\n\nans after multiply : " );
            for(int i=0;i<lenans;i++){
                
                printf("%d", ans[i]);
            }
            
            devidebytwo(intarray1,&len1);
            devidebytwo(intarray2,&len2);
            
            printf("\n\nAfter devide2 \n" );
            printf("\narray 1 : \n" );
            for(int i=0;i<len1;i++){
                
                printf("%d", intarray1[i]);
            }
            
            printf("\narray 2 : \n");
            for(int i=0;i<len2;i++){ 
                
                printf("%d", intarray2[i]);
            }
            

        }
        else if (iseven(intarray1)==true)
        {
            
            printf("\n\nNow array1 is even \n" );
            printf("\narray 1 : \n" );
            for(int i=0;i<len1;i++){                       
                
                printf("%d", intarray1[i]);
            }
            printf("\narray 2 : \n");
            for(int i=0;i<len2;i++){ 
                
                printf("%d", intarray2[i]);
            }
            
            
            devidebytwo(intarray1,&len1);

            
            printf("\n\nWe only devide array1 by 2 \n" );
            printf("\narray 1 : \n" );
            for(int i=0;i<len1;i++){                       
                
                printf("%d", intarray1[i]);
            }
            printf("\narray 2 : \n");
            for(int i=0;i<len2;i++){ 
                
                printf("%d", intarray2[i]);
            }
            
            
        }
        else if (iseven(intarray2)==true)
        {
            
            printf("\n\nNow array2 is even \n" );
            printf("\narray 1 : \n" );
            for(int i=0;i<len1;i++){                       
                
                printf("%d", intarray1[i]);
            }
            printf("\narray 2 : \n");
            for(int i=0;i<len2;i++){ 
                
                printf("%d", intarray2[i]);
            }
            
            
            devidebytwo(intarray2,&len2);

            
            printf("\n\nWe only devide array2 by 2 \n" );
            printf("\narray 1 : \n" );
            for(int i=0;i<len1;i++){                       
                
                printf("%d", intarray1[i]);
            }
            printf("\narray 2 : \n");
            for(int i=0;i<len2;i++){ 
                
                printf("%d", intarray2[i]);
            }
            
        }

        if ( compare(intarray1,intarray2,len1,len2)==1){// intarray1 is larger

            swaparray(intarray1,intarray2,&len1,&len2); 
        }

        
        printf("\n\nBefore subtract \n" );
        printf("\narray 1 : \n" );
        for(int i=0;i<len1;i++){                                       
            printf("%d", intarray1[i]);
        }
        printf("\narray 2 : \n");
        for(int i=0;i<len2;i++){ 
                
            printf("%d", intarray2[i]);
        }
        
        // now intarray 1 is smaller
        subtract(intarray2,intarray1,&len2,len1); // intarray2 = intarrary2 - intarray1
        
        
        printf("\n\nAfter subtract \n" );
        printf("\narray 1 : \n" );
        for(int i=0;i<len1;i++){                                       
            printf("%d", intarray1[i]);
        }
        printf("\narray 2 : \n");
        for(int i=0;i<len2;i++){ 
                
            printf("%d", intarray2[i]);
        }

        if(iszero(intarray2,len2)==true){
            printf("\nintarray2 is now zero \n" );
            //break;
        }
        else{
            printf("\nintarray2 is not zero \n" );
        }
        
        
        
    }
    
    
    printf("\nThis is intarray1 : \n" );
    for(int i=0;i<len1;i++){                                       
        printf("%d", intarray1[i]);
    }
    printf("\nThis is the length1 we have now : %d\n",len1);
    
    multiply(intarray1,ans,&len1);


    printf("this is final answer:");
    
    for(int i=len1-1;i>=0;i--){                                       
        printf("%d", intarray1[i]);
    }
    int temp;
    scanf("%d", temp);
    return 0;
    
}

int compare(int a1[], int a2[],int l1, int l2) {
  
    if (l1 > l2){
       return 1; 
    }
    else if (l2 > l1){
        return 2;
    }
    else {
        for (int i = l1-1; i>=0 ; i--) {
            if (a1[i] > a2[i]){
                return 1;
            }
            if (a2[i] > a1[i]){
                return 2;
            }
    
        }
    }
    return 0; // if two number are thee same 
}



bool iszero(int a1[],int length){
    
    for(int i=0; i<length;i++){
        if (a1[i]!=0){
            return false;
        }
    }
    return true;
}

bool iseven(int a1[]){
    if (a1[0]%2==0){
        return true;
    }
    else{
        return false;
    } 

}

void devidebytwo(int *array,int *length){
    
    int len = *length;
    int r = 0;
    int c[256]={};
    for (int i=len-1; i>=0; i--){
        r = r * 10 + array[i];
        c[i] = r / 2;
        r %= 2;
    }
    if (array[len-1]==1){
        len -=1;
        
    }
    for (int i=0; i<=len; i++)
    {
        array[i]=c[i];
        
    } 
    
    *length = len;


}

void swaparray( int *a, int *b,int *length1,int *length2 )// a is longer b is shorter
{
    for ( int i = 0; i < 256; i++ )
    {
        int tmp = a[i];
        a[i] = b[i];
        b[i] = tmp;
    }
    int temp = *length1;
    *length1 = *length2;
    *length2 =temp;

}


//intarray1//arr//length of array1 
void multiply (int *a,int *times, int *length1) // a = a*times// length1 is the length of a 
{
   
    int lena = *length1;

    
    //first count the digit of times 
    int counttimes = 0;
    for ( int i = 256-1; i >=0; i-- ){ 
        if (times[i]==0){
            counttimes+=1;
        }
        else{
           break; 
        }
    }
    
    int lentimes = 256-counttimes;
    
    int temp[256] ={0};
    for(int i=0; i<lena; i++) {
        if(a[i]==0){
            continue;
        } 
        for(int j=0; j<lentimes; j++){
            temp[i+j]+= a[i]*times[j];
        }
            
    }
    int carry = 0;
    for(int i=0; i<256; ++i) {
        
        temp[i]+=carry;
        carry = temp[i] / 10;
        temp[i] %= 10;
    }
    
    // count the digit again 
    int count = 0;
    for ( int i = 256-1; i >=0; i-- ){
        if (temp[i]==0){
            count+=1;
        }
        else{
           break; 
        }
    }

    //iterate temp to a 
    for ( int i = 0; i < 256-count; i++ )
    { 
        a[i] = temp[i];
    }

    
    *length1 = 256-count;
}

// subtract will just iterate a = a-b
void subtract( int *a, int *b,int *length1, int length2 )// a is larger b is smaller
{
    int temp[256]={};
    int len = *length1;
    for (int i=len-1; i>=0; i--){
        if (i<=length2){
            temp[i] = a[i] - b[i];
        }
        else{
            temp[i] = a[i];
        }

    }
        
 
    for (int i=0; i<len; i++){ // 一口氣借位和補位
        if (temp[i] < 0)
        {
            temp[i+1]--;           // 借位
            temp[i] += 10;         // 補位
        }
    }
    for ( int i = 0; i < 256; i++ )
    {
        
        a[i] = temp[i];
        
    }
    int count = 0;
    for ( int i = 256-1; i >=0; i-- ){
        if (temp[i]==0){
            count+=1;
        }
        else{
           break; 
        }
    }
    
    *length1 = 256-count; 

}

