#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

int d =10;
long long q = LLONG_MAX/((int)('~'-'!')+1)+1;

// expdtol reference to an array and the target index
void expdtol(long long* arr,int l){ 
    arr[0] = 1;
    for (int i = 1;i<l;i++){
        arr[i] = arr[i-1]*d;
        arr[i] %=q;
    }
}


int main(int argc, char* argv[]){

    int l = 8;
    long long *expdarrtol = (long long*) calloc(l , sizeof(long long));

    // try to count to four 
    expdtol(expdarrtol,l);

    for(int i = 0; i<4;i++){
        printf("%lld\n",expdarrtol[i]);
    }

    return 0;
}
