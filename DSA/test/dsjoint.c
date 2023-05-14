#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct disjointSet{
    // TODO: Determine fields to use by your method
    int root;
    int next;
    int size; // only root record the size 
} DisjointSet;

// a set of array 
DisjointSet ds[1 << 24];
// set is something which checked is the index already exists
bool set[1 << 24] = {};
// 1<<24 == 2^24

//
int c2i(char c) { 
    if ('0' <= c && c <= '9') return c - '0';
    else if ('a' <= c && c <= 'z') return c - 'a' + 10;
    else if ('A' <= c && c <= 'Z') return c - 'A' + 36;
    return -1;
}

int hash(const char* s) {  
    return s[0];
    int ret = 0;
    int mask = (1<<24)-1;
    int len = strlen(s);
    for (int i = 0; i < len; i++)
        ret = mask & (ret << 4) | c2i(s[i]);
    return ret;
}

void makeset(int i){
    ds[i].root = i;// i is after hash 
    ds[i].size = 1;
    ds[i].next =-1;// it points to no one 
}

inline void static init(const char* s) {
    int i = hash(s);
    if(set[i]){
        printf("there are %d in set %s\n",ds[ds[i].root].size, s);
    }
    
    if (!set[i]) {
        makeset(i);
        set[i] = 1;
    }
}

int find_set(const char* s) {
    init(s);
    int i = hash(s);
    return ds[i].root;
}

int find_last( int a ){
    while(ds[a].next!=-1){
        a = ds[a].next;
    }
    return a;
}

void group(const char *ra, const char *rb) {
    int i1 = hash(ra);
    int i2 = hash(rb);
    int roota = ds[i1].root;
    int rootb = ds[i2].root;
    int len1 = ds[roota].size;
    int len2 = ds[rootb].size;


    // we union b to a
    if(len1>len2){
        // update the larger root's size
        ds[roota].size += ds[rootb].size; 

        int lasta = find_last(i1);
        // point the last of a to the root of b
        ds[lasta].next = rootb;
        ds[rootb].root = roota;
        // change element's root to a's root
        while(ds[rootb].next != -1){
            
            rootb = ds[rootb].next;
            ds[rootb].root = roota; // gradually move rootb to the last 
        }
        printf("\nroota: %c\n",roota);
        printf("rootb: %c\n",rootb);
    }
    else{ // union a to b
        ds[rootb].size += ds[roota].size; 
        int lastb = find_last(i2);
        ds[lastb].next = roota;
        ds[roota].root = rootb;
        while(ds[roota].next != -1){
            
            roota = ds[roota].next; 
            ds[roota].root = rootb;// gradually move rootb to the last 
        }
        printf("\nroota: %c\n",roota);
        printf("rootb: %c\n",rootb);


    }
    
}



bool same_set(const char*a, const char* b) {
    int i1 = hash(a);
    int i2 = hash(b);
    int roota = ds[i1].root;
    int rootb = ds[i2].root;

    if (roota == rootb){
        return true;
    }
    else{
        return false;
    }
}

int main() {
    int N;
    scanf("%d", &N);

    for (int index = 0; index<N ;index++){
        char title[10];

        char name1[15];
        char name2[15];

        scanf("%s %s %s",title,name1,name2);
        init(name1);
        init(name2);

        //read two name and group them together
        if(title[0]=='g'){ 
            printf("this is %d time we do %s and %s\n",index,name1,name2);
            int i1 = hash(name1);
            int i2 = hash(name2);
            int root1 = ds[i1].root;
            int root2 = ds[i2].root;

            printf("\nroota: %c\n",root1);
            printf("rootb: %c\n",root2);
            
            if (same_set(name1,name2) == false){
                group(name1,name2);
            }
            
            
            

            if (same_set(name1,name2) == false){
                printf("\nfuck they do not have same set\n");
            }

            printf("%s has the set size %d\n",name1,ds[root1].size);
            printf("%s has the set size %d\n",name2,ds[root2].size);

        }
        else if(title[0]=='t'){
            printf("this is %d time we do %s and %s\n",index,name1,name2);
            int i1 = hash(name1);
            int i2 = hash(name2);
            int root1 = ds[i1].root;
            int root2 = ds[i2].root;

            printf("%s has the set size %d\n",name1,ds[root1].size);
            printf("%s has the set size %d\n",name2,ds[root2].size);

            if (same_set(name1,name2)){
                printf("Positive\n");
            }
            else{
                printf("Negative\n");
            }

        }



    }

    return 0;
}