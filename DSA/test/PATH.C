#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct disjointSet{
    // TODO: Determine fields to use by your method
    int parrent;
    int next;
    int size; // only root record the size 
} DisjointSet;

DisjointSet ds[1 << 24];
bool set[1 << 24] = {};

int c2i(char c) { 
    if ('0' <= c && c <= '9') return c - '0';
    else if ('a' <= c && c <= 'z') return c - 'a' + 10;
    else if ('A' <= c && c <= 'Z') return c - 'A' + 36;
    return -1;
}

int hash(const char* s) {  
    int ret = 0;
    int mask = (1<<24)-1;
    int len = strlen(s);
    for (int i = 0; i < len; i++)
        ret = mask & (ret << 4) | c2i(s[i]);
    return ret;
}

void makeset(const char* s){
    int i = hash(s);
    ds[i].parrent = i;// i is after hash 
    ds[i].size = 1;
    ds[i].next =-1;// it points to no one
}

inline void static init(const char* s) {
    int i = hash(s);
    if (!set[i]) {
        makeset(s);
        set[i] = 1;
    }
}

int find_set(int s) {
    if(ds[s].parrent != s){
        ds[s].parrent = find_set(ds[s].parrent);
    }

    return ds[s].parrent;
}

int find_last( int a){
    while(ds[a].next!=-1){
        a = ds[a].next;
    }
    return a;
}
void Link (int a,int b){
    if(ds[a].size>ds[b].size){
        ds[b].parrent = a;
    }
    else{
        ds[a].parrent = b;
        if (ds[a].size == ds[b].size){
            ds[b].size +=1;
        }

    }
}

void group(const char *ra, const char *rb) {
    int numa = hash(ra);
    int numb = hash(rb);
    Link(find_set(numa),find_set(numb));    
}

bool same_set(const char*a, const char* b) {
    int numa = hash(a);
    int numb = hash(b);
    int ra = find_set(numa), rb = find_set(numb);
    if (ra == rb){
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

            
            if (same_set(name1,name2) == false){
                group(name1,name2);
            }


        }
        else if(title[0]=='t'){



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