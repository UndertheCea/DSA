#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
int countshop = 0;

typedef struct disjointSet{
    int parrent;
    int size; // only root record the size 
} DisjointSet; // we name this structure DisjointSet

// it'll create a 1d array of structure
DisjointSet ** new_shop(int N) // N is the numbers of shops             
{  
    // ds is a pointer that points to each city structure pointer
    DisjointSet **ds = (DisjointSet**)malloc(N*sizeof(DisjointSet*));   

    for(int i = 0; i < N; i++){
        ds[i] = (DisjointSet*)malloc(sizeof(DisjointSet));
    }
   
   if (!ds){// if st is a null pointer
      return ds;   
      printf("i think we are in trouble now ");
   }                                                                              

   return ds;                                        
}

DisjointSet* makeset(int i){
    DisjointSet *newSet = (DisjointSet*)malloc(sizeof(DisjointSet));
    newSet->parrent = i;
    newSet->size = 1;
    return newSet;
}

int find_set(int s, DisjointSet **shop) {
    if(shop[s]->parrent != s){
        return find_set(shop[s]->parrent,shop);
    }
    return shop[s]->parrent;
    
}

int Link (int a,int b,DisjointSet **shop){
    if(shop[a]->size > shop[b]->size){
        shop[b]->parrent = a;
    }
    else{
        shop[a]->parrent = b;
        
        if (shop[a]->size == shop[b]->size){
            shop[b]->size += 1;
            return 1;
        }

    }
    return 0;

}

void unLink (int a, int b, DisjointSet **shop, int normal){
    countshop++;

    if(shop[a]->parrent == b){
        if (normal == 1){
            shop[b]->parrent = b;
            shop[a]->parrent = a;

        }
        else if(normal == 15){ // they are originally the same size
            shop[b]->size--;
            shop[b]->parrent = b;
            shop[a]->parrent = a;

        }

    }
    else if (shop[b]->parrent == a){
        if (normal == 1){
            shop[b]->parrent = b;
            shop[a]->parrent = a;

        }
        else if(normal == 15){ // they are originally the same size
            shop[a]->size--;
            shop[b]->parrent = b;
            shop[a]->parrent = a;

        }
    }

}


bool same_set(int a, int b, DisjointSet **shop) {
    int ra = find_set(a,shop), rb = find_set(b,shop);
    if (ra == rb){
        return true;
    }
    else{
        return false;
    }
}

// node is use for the adjlinklist 
typedef struct node{
    struct node *next; // all the days that is linked to the current day
    int currday; // what day is today 
    bool visited;
}Node;

// initialize a pointer that points to the new node
Node *new_node(int day){
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->currday = day;
    newNode->next = NULL;
    newNode->visited = false; 
    return newNode;
}

// it'll create a 1d array as the adjlinklist
Node **new_graph(int M) // there are M days          
{  
    // nd is a pointer that points to each node's pointer
    Node **nd = (Node**)malloc(M*sizeof(Node*));

    for(int i = 0; i < M; i++ ){
        nd[i] = new_node(i);
    }

    if (!nd){// if nd is a null pointer
      printf("i think we are in trouble now ");
      return nd;   
      
    }                                                                              

   return nd;                                        
}

// we only need add last when we meet boom day
// we'll add value to the last of head  
void addLast(int head, int val, Node **graph)
{
    Node *lastNode = graph[head];
    //last node's next address will be NULL.
    while(lastNode->next != NULL)
    {
        lastNode = lastNode->next;
    }
    //create a Node and add it at the end of the linked list
    lastNode->next = new_node(val);
    
}

// operate according to the type of day 
int operate(int day, int** operation,DisjointSet ** shop){
    if (operation[day][0] == -1){ // query
        printf("this is query\n");
        printf("there are %d shops now \n", countshop);

        return countshop;
    } 
    else if (operation[day][0] == -2){// union 
        int parrent1 = find_set(operation[day][1],shop);
        operation[day][1] = parrent1;
        int parrent2 = find_set(operation[day][2],shop);
        operation[day][2] = parrent2;
        printf("before merge, there are %d shops\n",countshop);


        if (parrent1 != parrent2){ // they are already not the same
            operation[day][3] = 1; // record that this merge is legal
            countshop --;
            int temp = Link(parrent1,parrent2,shop); 
            
            if (temp == 1){
                // the merge is equal 
                operation[day][3] = -1;
            }
        }
        printf("after merge, there are %d shops\n",countshop);
        
        return -1;

    }
    else if (operation[day][0] == -3){// boom day 
        printf("boom boom\n");
        return -1;
    }
    return -1;

}
// we have to operate on shop but reference on the Node(the adjacency link list)
void DFS( int here, Node **graph, int **operation,DisjointSet **shop,int* ans) {  
	// now we are at the node, so we do the day's operation 
    printf("\nwe are at day%d\n",here);
    ans[here] = operate(here,operation,shop);
    
    // step deeper
    Node *temp = graph[here]->next;
    // while means we have to go through all the link list 
    while (temp != NULL){
        
        DFS(temp->currday, graph, operation, shop,ans);
        temp = temp->next;
    }


    // there are nothing in the adjlink list, means we are now at thee leaf
    if (operation[here][0] == -2){ // we need to step back if it is merge
        if (operation[here][3] == 1){
            printf("we reverse link at day %d\n", here);
            printf("before unlink, there are %d shops\n",countshop);
            
            unLink(operation[here][1],operation[here][2],shop,1);
            
            
            printf("after unlink, there are %d shops\n",countshop);
        
        }
        else if (operation[here][3] == -1){
            // it is a special link
            printf("we reverse a special link at day %d\n", here);
            printf("before unlink, there are %d shops\n",countshop);
            
            unLink(operation[here][1],operation[here][2],shop,15);

            
            printf("after unlink, there are %d shops\n",countshop);

            
        }
        else{
            printf("the link at day %d is useless\n", here);
            // they were originally the same set
            return;

        }
    }

}


int main() {
    int N, M;
    scanf("%d %d",&N,&M);
    countshop = N;

    int *answer = (int*)calloc(M+1,sizeof(int)); 
    for(int i = 0; i< M+1; i++){
        answer[i] = -1;
    }


    
    // shop is an array stores the current circumatance
    DisjointSet **shop =  new_shop(N);

    for(int i = 0; i<M; i++){
        shop[i] = makeset(i);
    }
    
    // shopgraph is an adjlist for the dfs use from day 0 to day M 
    Node ** shopgraph = new_graph(M+1);
    

    // query = -1
    // merge = -2
    // boom = -3

    // operation is 4*M array which reads both the operation and the the day if needed
    int **operation = (int**)calloc(M+1,sizeof(int*));  
    for(int i = 0; i < M+1; i++){
        operation[i] = (int*)calloc(4,sizeof(int));
    }

    int currnode = -1;
    for (int i = 0; i < M+1;i++){
        
        if(currnode == -1){ // we'll skip the first 
            currnode = 0;
            continue;
        }


        // read how the operations are ordered and construct the adj linklist
        char *title = (char*)malloc(10*sizeof(char));
        
        scanf("%s", title);
        
        if (title[0] == 'b'){
            // means the latter day have to restart from the boom day and today may be the end of the tree
            int day;
            scanf("%d",&day);
            
            addLast(currnode,i,shopgraph);
            while(operation[day][0] == -3){
                day = operation[day][1];
            }
                 
            
            currnode = day; // the latter will restart from here 
            operation[i][0] = -3;
            operation[i][1] = day ;
  
        }
        else if (title[0] == 'q'){

            // add today after the former and update currnode as today
            addLast(currnode,i,shopgraph);
            currnode = i;
            operation[i][0] = -1;

            
        }
        else if (title[0] == 'm'){
            int shop1,shop2;
            scanf("%d %d",&shop1, &shop2);
        

            // add today after the former and update currnode as today
            addLast(currnode,i,shopgraph);
            currnode = i;
            
            operation[i][0] = -2;
            operation[i][1] = shop1-1; // the index starts from 0 
            operation[i][2] = shop2-1;

            
        }
        free(title);
    }


    // check the shopgraph
    printf("this is the adj list \n");
    for(int i = 0; i<M+1;i++){
        printf("this is %d day ",i);
        Node *temp = shopgraph[i];
        while(temp != NULL){
            printf("%d ",temp->currday);
            temp = temp->next;
        }

        printf("\n");

    }

    printf("\n\nwe start to dfs\n");
    DFS(0,shopgraph,operation,shop,answer);

    printf("we start to print answer: \n");
    for (int i = 0; i < M+1; i++){
        if (answer[i] != -1){
            printf("%d\n",answer[i]);
        }
    }

    return 0;
}