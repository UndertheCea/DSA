#include <stdio.h> 
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <stdint.h>

char buffer[10000000] ;
int failure[10000000] = {0};
char revstr[10000000] ;
int revfail[10000000] = {0};
int main(int argc, char* argv[]){
    
    int ch;
    size_t index = 0; // index in buffer

    printf("Please, provide input: ");
    while ((ch = getchar()) != '\n' && ch != EOF) {
        buffer[index] = (char)ch;
        index++;
    }

    buffer[index] = '\0';

    if (ch == EOF) {
        
        printf("EOF encountered\n");
    }

    printf("%s\n", buffer);

    // buffer stores things from 0 - (index-1)
    int length = index; 
    printf("this is the length of the buffer%d\n", length);
    failure[0] = 0;
    int k = 0;
    for (int q = 1 ;q < length; q++){
        while (k > 0 && buffer[k] != buffer[q]){
            k = failure[k-1];
        }
        if (buffer[k] == buffer[q]){
            k++;
        }
        failure[q] = k;
    } 
    printf("\nthis is failure\n");
    for(int i = 0; i < length; i++){
            printf("%d",failure[i]);
    }

    // reverse string 
    printf("\nnow we start to reverse buffer");
    index--;
    for(int i = 0; i < length; i++){
        revstr[i] = buffer[index];
        printf("\nthis is the %d from buffer %c", index, buffer[index]);
        index--;
    }
    revstr[length] = '\0';

    //find failure funciton for reverse string
    revfail[0] = 0;
    k = 0;
    for (int q = 1 ;q < length; q++){
        while (k > 0 && revstr[k] != revstr[q]){
            k = revfail[k-1];
        }
        if (revstr[k] == revstr[q]){
            k++;
        }
        revfail[q] = k;
    } 
    printf("\nthis is reverse failure\n");
    for(int i = 0; i < length; i++){
        printf("%d",revfail[i]);
    }

    // find the string in reversed string 
    int i1 = 0; 
    int j1 = 0; // in reverse string which is the target
    while( j1 < length){
        if(buffer[i1] == revstr[j1]){
            i1++;
            j1++;          
        }
        else{
            if(i1 == 0){
                j1++;
            }
            else{ // i stays the same but move j forward
                i1 = failure[i1-1];
            }
        }

    }
    // since j has ++ , j just represent the length of paldindrome

    // find the reversed string in string 
    int i2 = 0;
    int j2 = 0;
    printf("\nthis is reverse buffer\n");
    for(int i = 0; i < length; i++){
        printf("%c",revstr[i]);
    }


    while( j2 < length){
        if(revstr[i2] == buffer[j2]){
            i2++;
            j2++;          
        }
        else{
            if(i2 == 0){
                j2++;
            }
            else{ // i stays the same but move j forward
                i2 = revfail[i2-1];
            }
        }

    }
    printf("\n i1 = %d\n",i1);
    printf("\n i2 = %d\n",i2);
    int len1 = length - i1;
    int len2 = length - i2;
    if(i1 == i2){
        printf("\n i1 == i2\n");
        printf("we have add %d number\n",len1);
        
        if (len1 == 0 && len2 ==0){ // the word is originally palindrome
            for(int i = 0; i < length; i++){
                printf("%c",buffer[i]);
            }
        }
        else{ // output 2 answer 
            // output j1 first 
            for(int i = 0; i < len1; i++){
                printf("%c",revstr[i]);
            }
            for(int i = 0; i < length; i++){
                printf("%c",buffer[i]);
            }
            printf("\n");
            // output j2 
            for(int i = 0; i < len2; i++){
                printf("%c",buffer[i]);
            }
            for(int i = 0; i < length; i++){
                printf("%c",revstr[i]);
            }
        }
        

    }
    else if (i1 > i2){
        printf("\n i1 > i2\n");
        // j1 has more palindrome
        // output j1 first 
        printf("we have add %d number\n",len1);
        for(int i = 0; i < len1; i++){
            printf("%c",revstr[i]);
        }
        for(int i = 0; i < length; i++){
            printf("%c",buffer[i]);
        }
    }
    else{
        printf("\n i1 < i2\n");
        // j2 has more palindrome
        // output j2 
        printf("we have add %d number\n",len2);
        for(int i = 0; i < len2; i++){
            printf("%c",buffer[i]);
        }
        for(int i = 0; i < length; i++){
            printf("%c",revstr[i]);
        }
    }


    return 0;
}
