#include <stdio.h> 
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <stdint.h>
#include <limits.h>
long long q = LLONG_MAX/((int)('~'-'!')+1)+1;
long long d = (int)('~'-'!')+1;


// we set a list structure which point to next node adn eventually become a list
typedef struct Spell {
    int origindex;
    long long rabin;
    long long initialrabin;
    int *arr;
      
}spell; // next time we can call the Spell "spell"


spell **new_spell(int K,int L)               
{                                                       
    // sp is a pointer that points to each spell's address
    spell **sp = (spell**)malloc(K * sizeof(spell*));
    for(int i = 0; i < K; i++){
        sp[i] = (spell*)malloc(sizeof(spell));
    }

    // set up properties and malloc an int arrary that stores the spell elements
    for(int i = 0; i < K; i++) {
        sp[i]->origindex = i;
        sp[i]->rabin = -1;
        sp[i]->initialrabin = -1;
        sp[i]->arr = (int*)malloc(L*sizeof(int));
    }

    // check if we acquire the memory
    if (!sp){
        return sp;   // return a null pointer
        printf("houston we are in trouble now");
    } 
    return sp;                                        
}

int compare (const void * a, const void * b)
{
    spell *orderA = *(spell **)a;
    spell *orderB = *(spell **)b;
    if (orderB->rabin > orderA->rabin){
        return 1;
    }
    else if(orderB->rabin < orderA->rabin){
        return -1;
    } 
    else{
        return 0;
    }
}

int compareinitial (const void * a, const void * b)
{
    spell *orderA = *(spell **)a;
    spell *orderB = *(spell **)b;
    if (orderB->initialrabin > orderA->initialrabin){
        return 1;
    }
    else if(orderB->initialrabin < orderA->initialrabin){
        return -1;
    } 
    else{
        return 0;
    }
}

// expdtol reference to an array and the target index
void expdtol(long long* arr,int l){ 
    arr[0] = 1;
    for (int i = 1;i<l;i++){
        arr[i] = arr[i-1]*d;
        arr[i] %=q;
    }
}

// adjust the rabin value for every spell with some digits covered
void adjustrabin(spell **self ,int L ,int K,int adjindex,long long *arr ){
    long long expadj = arr[L-adjindex-1];
    for (int i = 0; i< K ;i++){
        // when we meet the number we want to ignore, we minus it's d^index*number
        
        self[i]->rabin = (self[i]->initialrabin)-(self[i]->arr[adjindex])*expadj; 
        self[i]->rabin %= q;
        if (self[i]->rabin < 0){
            self[i]->rabin += q;
        }
        
    } 
}

long long countC(long long num){
    return (num*(num-1)/2);
}

int main(int argc, char* argv[]){
    int k,l,flag;
    scanf("%d %d %d",&k,&l,&flag);
    
    spell **magic = new_spell(k,l);
    long long *expdarrtol = (long long*) calloc(l , sizeof(long long));
    expdtol(expdarrtol,l);

    for(int i = 0; i < k;i++){
        char *chararr = (char*)malloc( ( l + 1 )*sizeof(char)); // for 0 to (l-1) stores the data and l stores '/0'
        scanf("%s",chararr); // read at most l elements
        magic[i]->initialrabin = 0; 
        // change these char into integer and count the rabin 
        for(int j = 0; j < l;j++){
            magic[i]->arr[j] = (int)(chararr[j]-'!');
            magic[i]->initialrabin = (magic[i]->initialrabin*d)%q;
            magic[i]->initialrabin += magic[i]->arr[j];
            magic[i]->initialrabin %= q;
            
        }

        free(chararr);
    }
    
    if (flag == 0){
        bool ifprint = false;
        // now we'll adjust the rabin value for l times, and we cover from 
        for(int i = 0; i<l;i++){
            adjustrabin(magic,l,k,i,expdarrtol);
            printf("\nthis %d is adjust rabin\n",i);
            for (int i = 0; i<k;i++){
                
                printf("%d ",magic[i]->rabin);
                printf("\n");
            }
            // sort all the k element in the magic array 
            qsort (magic, k, sizeof(spell*), compare);

            printf("\nthis %d is adjust rabin after sort\n",i);
            for (int times = 0; times<k;times++){
                
                printf("%lld with index %d ",magic[times]->rabin,magic[times]->origindex);
                printf("\n");
            }

            // search the first two that owns same rabin and print their origin index
            for(int search = 0 ;search < k-1;search++){
                if(magic[search]->rabin == magic[search+1]->rabin){
                    printf("Yes\n");
                    printf("%d %d",magic[search]->origindex,magic[search+1]->origindex);
                    ifprint = true;
                    break;
                } 
            }
            if (ifprint == true){
                break;
            }

        }
        if (ifprint == false){
            printf("No");
        }
        
    }
    else if (flag == 1){
        // check all the one that are originally the same
        int countsame = 0;
        long long ansofsame = 0;
        
        qsort(magic,k,sizeof(spell*),compareinitial);
        
        printf("\nthis is the rabin after sort\n");
        for (int i = 0; i<k;i++){
            
            printf("%lld with index %d ",magic[i]->initialrabin, magic[i]->origindex);
            printf("\n");
        }

        printf("\nbefore covering\n");
        for (int i = 0; i < k-1;i++){
            // if the following few has the same rabin a
            if(magic[i]->initialrabin == magic[i+1]->initialrabin){
                // now we meet the first two that are the same 
                while(i+1<k && magic[i]->initialrabin == magic[i+1]->initialrabin){
                    countsame++;
                    i++;
                }
                // before we quit these couple we add them to the answer
                countsame++;
                ansofsame += countC(countsame);
                printf("we add %d\n",countC(countsame));
                countsame = 0;
                
            }
            
        }
        if (countsame == l){
            printf("Yes\n");
            printf("%d",ansofsame);
            return 0;
        }
        
        long long ans = 0 ;
        // for those that are not originally the same, find similiar
        for(int i = 0; i<l;i++){
            adjustrabin(magic,l,k,i,expdarrtol);
            // sort all the k element in the magic array 
            qsort(magic,k,sizeof(spell*),compare);

            printf("\nthis %d is adjust rabin after sort\n",i);
            for (int times = 0; times<k;times++){
                
                printf("%lld with index %d ",magic[times]->rabin,magic[times]->origindex);
                printf("\n");
            }

            int countsimilar = 0;
            
            // search those own same rabin 
            for(int search = 0 ;search < k-1;search++){
                if(magic[search]->rabin == magic[search+1]->rabin){
                    // when we meet similar we'll find until not similar
                    while(search+1<k && magic[search]->rabin == magic[search+1]->rabin){
                        countsimilar++;
                        search++;
                    }
                    countsimilar++;

                    ans += countC(countsimilar);
                    printf("we add %d\n",countC(countsimilar));
                    countsimilar = 0;
                }
            }
            
            ans -= ansofsame;
            printf("this is %d times ans : %d\n",i,ans);
        }
        ans += ansofsame;
        printf("Yes\n");
        printf("%d",ans);
 
    } 




    return 0;
}