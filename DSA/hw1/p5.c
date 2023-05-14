#include <stdio.h> 
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <stdint.h>
#include <inttypes.h>
// we set a list structure which point to next node adn eventually become a list
typedef struct List {
    int id;
    struct List *link;// which is a pointer point to both previous and following node
    int group; // the group people belongs to 
    bool occupied; // if the kth place is occupied by group then return true

}list; // next time we can call the List "list"

list* XOR(list *x,list* y);
void traverse(list *head);
list* insert(list *head, int K,int data);
list* reverse(list* head);
list* delEnd(list* head);
list *** new_list(int M,int K);



// construct the xor operator
list* XOR(list *x, list *y) {
    return (list*)((uintptr_t)(x) ^ (uintptr_t)(y));
}

// we'll vist the list from head
void traverse(list *head)
{
    
    list* curr = head;

    list* prev = NULL;
    list *next;

    while (curr != NULL)
    {
        printf("%d ", curr->id);

        next = XOR(prev, curr->link);
        prev = curr;
        curr = next;
    }

}

//insert a node at the beginning of the XOR linked list
list* insert(list* head, int K,int data)// input a pointer to *head
{
    //malloc a new node and assign its id 
    list* newNode = (list*)malloc(sizeof(list));
    
    // If XOR linked list is empty
    if (head == NULL) {

        // Stores data value in the node
        newNode->id = data;
 
        // Stores XOR of previous and next pointer
        newNode->link = XOR(NULL, NULL);

        newNode->occupied = true;
        newNode->group = K;
        
        // Update pointer of head node
        head = newNode;
        return head;
    }
 
    // If the XOR linked list is not empty
    else {
 
        // Stores the address of current node
        list* curr = head;// from now on curr should be the old one 
 
        // Stores the address of previous node
        list* prev = NULL;
 
        // Update curr node address
        // XOR(NULL, curr->link) represent the address of next node
        curr->link = XOR(newNode, XOR(NULL, head->link));
 
        // Update new node address
        newNode->link = XOR(NULL, curr);
        
        newNode->occupied=true;
    
        newNode->id = data;
        newNode->group = K;
        // Update head
        head = newNode;
        return head;
    }

}

list* reverse(list* head)
{
    // Stores XOR pointer in current node
    list* curr = head;
    list* prev = NULL;
    list* next;
    if (curr == NULL)// the size of list is 0
        return NULL;
    else {
 
        while (XOR(prev, curr->link) != NULL)
        {
            //printf("we are reversing through %d\n ", curr->id);
            next = XOR(prev, curr->link);
            prev = curr;
            curr = next;
        }
 
        // Update the head pointer
        
        return curr;
    }
    
}

list* merge(list*startwithhead, list*startwithtail)
{
    // add(nxt1)
    list* nxt1 = XOR(NULL,startwithhead->link);
    // add(nxt2)
    list* nxt2 = XOR(NULL,startwithtail->link);

    startwithhead->link = XOR(startwithtail,nxt1);
    startwithtail->link = XOR(nxt2,startwithhead);

    // from start with tail, we reverse it and find the tail of it as head

    list* prev = startwithhead;
    list* next = nxt2;
    list* curr = startwithtail;
    // while add(next) != null
    while (XOR(prev, curr->link) != NULL) {

        // Forward traversal
        next = XOR(prev, curr->link);

        // Update prev
        prev = curr;

        // Update curr
        curr = next;
    }

    // Update the head pointer
    list* head = curr;
    return head;
    
}

list* delEnd(list* head)
{
    // Base condition
    if (head == NULL)
        printf("List is empty");
    else {
  
        // Stores XOR pointer in current node
        list* curr = head;
  
        // Stores XOR pointer of
        // in previous Node
        list* prev = NULL;
  
        // Stores XOR pointer of
        // in next node
        list* next;
  
        // Traverse XOR linked list until the last
        //XOR(curr->link, prev) represent add(next)
        while (XOR(curr->link, prev) != NULL) {
  
            // Forward traversal
            next = XOR(prev, curr->link);
  
            // Update prev
            prev = curr;
  
            // Update curr
            curr = next;
        }
        printf("\n%d enetr from group%d to the bathroom\n",curr->id,curr->group);
        // If the Linked List contains more than 1 node
        if (prev != NULL){
            
            prev->link = XOR(XOR(prev->link, curr), NULL);
        }
        // Otherwise
        else{
            head = NULL;
        }
    }

    return head;
}

list* delfirst(list* head)
{
    // If list is empty
    if (head == NULL)
        printf("List Is Empty");
    else {
  
        // Store the node to be deleted
        list* temp = head;
  
        // Update the head pointer as the next node
        //XOR(NULL, temp->link) represents the add(nxt)
        printf("\nleave %dfrom group%d \n",head->id,head->group);
        head = XOR(NULL, temp->link);
  
        // if linked list contains only one node, head should be NULL
        if (head != NULL) {// moer than one thing in the linklist
  
            // Update head node address
            // since temps is the one going to be deleted and head is the next 
            // XOR(temp,(*head)->link) represents the add(the next of head)
            (head)->link= XOR(NULL, XOR(temp,(head)->link));
        }
        else{// now the list is empty
            head =NULL;
        }
        free(temp);
    }
    // Returns head of new linked list
    return head;
}

// construct the map of list
list *** new_list(int M,int K)               
{                                                       
    // assign memeory for ls, which is a 2D array
    list ***ls = (list***)malloc(M * sizeof(list**));
    for(int i=0; i< M; i++) {
        ls[i] = (list **)malloc(K * sizeof(list*));
        for (int j =0; j < K; j++){
            //ls[i][j] = (list *)malloc(K * sizeof(list));
            ls[i][j] = (list *)malloc(sizeof(list));
        }
    }

    for(int i=0; i< M; i++) {
        for (int j =0; j<K;j++){
            ls[i][j] = NULL;
        }
        
    }

    // check if we acquire the memory
    if (!ls){
        return ls;   // return a null pointer
        printf("i think we are in trouble now ");
    } 
    return ls;                                        
}



int main(int argc, char* argv[]){
    int M, K, N;// M bathrooms//K groups 

    scanf("%d %d %d", &M, &N, &K);

    printf("hello we are finally in %d %d %d\n",M,N,K);
    //memset(array, 0, sizeof(array[0][0]) * m * n);
    int nearby[M][2];
    memset(nearby, 0, sizeof(nearby[0][0]) * M * 2);
    int start[M];// it says where the entry of next node is and somehow shows the end of the list 
    int first[M];// it says where the first group standing at 
    memset(start, 0, M*sizeof(start[0]));
    memset(first, 0, M*sizeof(first[0]));
    int isclose[M];// it says where the first group standing at 
    memset(isclose, 0, M*sizeof(isclose[0]));
    int **checkK = (int**)calloc(M, sizeof(int*));
    for(int i = 0; i < M; i++) {
        checkK[i] = (int*)calloc(K, sizeof(int));
    }
    

    for(int i = 0; i < M; i++) {
        for(int j = 0; j < K; j++) {
            checkK[i][j]=-1;
        } 
    }
 
    list ***bathrooms = new_list(M,K); // we set a map composed by pointer of structure with M times K
    // this is the 2D array that keeps the target bathroom 

  
    for (int i=0;i<M;i++){
        if (i == 0){
            nearby[i][0]=M-1;
            nearby[i][1]=i+1;
        }
        else if (i+1==M){
            nearby[i][0]=i-1;
            nearby[i][1]=0;
        }
        else{
            nearby[i][0]=i-1;
            nearby[i][1]=i+1;
        }
    }


   
    for (int times = 0; times<N;times++){
        
        char *title = (char*)malloc( 10*sizeof(char) );
        scanf("%s", title);

        if((char)title[0]=='e'){
            int i,j,m;// id j from group i in line m
            scanf(" %d %d %d", &i ,&j, &m);

            
            int entry = start[m];
            bool alreadyenter = false;
            // if the map exist the place for it to enter
            if(checkK[m][i] != -1){
                int location = checkK[m][i];
                bathrooms[m][location] = insert(bathrooms[m][location],i,j);
                printf("we enter %d from group %d to [%d][%d]\n\n",bathrooms[m][location]->id,bathrooms[m][location]->group,m,location);
                alreadyenter = true;
                    
            }
 
            if (alreadyenter != true){// then we find the next node for it to enter
                
                bathrooms[m][start[m]] = insert(bathrooms[m][start[m]],i,j);
                printf("we enter %d from group %d to [%d][%d]\n\n",bathrooms[m][start[m]]->id,bathrooms[m][start[m]]->group,m,start[m]);
                checkK[m][i] = start[m];

                
                
                start[m] = start[m]+1; // update the next as entry 
                
                if(start[m]==K){
                    start[m]=0;
                }
            }
            
        }
        
        else if((char)title[0]=='l'){
            int m;
            scanf(" %d", &m );
            
            // we are now at first space so we got the last group
            int index = start[m]-1;
            if (index<0){
                index = K-1;
            }
            
            // update the list on the map to the head
            
            int tempgroup = bathrooms[m][index]->group;
            
            bathrooms[m][index] = delfirst(bathrooms[m][index]);
            
            
            // if after leave the group become zero we update the tail
            
            if(bathrooms[m][index] == NULL){
                start[m] = start[m]-1;
                if (start[m]<0){
                    start[m] = K-1;
                }
                checkK[m][tempgroup]=-1;
            }


        }
        
        else if((char)title[0]=='g'){
            int m;
            scanf(" %d", &m );
            printf("\nwe go someone to bathroom\n");
            int tempgroup = bathrooms[m][first[m]]->group;
            
            printf("before delete\n");
            traverse(bathrooms[m][first[m]]);
            bathrooms[m][first[m]] = delEnd(bathrooms[m][first[m]]);
            printf("after delete\n");
            traverse(bathrooms[m][first[m]]);

            // if the group become zero after go 
            
            if (bathrooms[m][first[m]] == NULL ){
                checkK[m][tempgroup]=-1;
                first[m] = first[m] + 1;
                if (first[m] == K){
                    first[m]=0;
                }
            }

        }

        else if((char)title[0]=='c'){

            printf("\nhello we are in close now\n");
            int m;
            scanf(" %d", &m );
            int pre = nearby[m][0];
            int nxt = nearby[m][1];

            nearby[nxt][0]=nearby[m][0];
            nearby[pre][1]=nearby[m][1];

            //tail states that where people should start to leave 
            
            // first we find the tail of the link list
            // second we find if the pre abthroom have the same group
            // if not we find the enrty of pre bathroom and try to merge the people together 
            // also we have to update the data in entry if we enter new group of people
            // keep doing this shit until the tail meet head

            // update the tail from the start array 
            //there are no people in the line
            bool fuckjustclose = false;
            if (start[m] == first[m] && bathrooms[pre][start[m]] == NULL){
                fuckjustclose = true;
            }

            int tail = start[m]-1;
            int head = first[m];
            if (tail<0){
                tail = K-1;
            }

            // this time we go from tail to head 
            while (tail != head && fuckjustclose == false){
                
                // tail is the current group's place

                printf("\nwe are dealing with group %d with %d standing at first in line %d \n",bathrooms[m][tail]->group,bathrooms[m][tail]->id,m);
                //bathrooms[m][tail] = reverse(bathrooms[m][tail]);
                //printf("after reverse %d is going to leave first to line %d \n\n" ,bathrooms[m][tail]->id,pre);
                //current group's group;
                int tempgroup = bathrooms[m][tail]->group;
    
                bool existgroup = false;
                int templocation;
                
                if (checkK[pre][tempgroup] != -1){
                    printf("luckily, we finds the same group in other line\n");
                    existgroup = true;
                    templocation = checkK[pre][tempgroup];
                    printf("before merge, the target group has first %d\n" ,bathrooms[pre][templocation]->id);
                    bathrooms[pre][templocation] = merge(bathrooms[pre][templocation],bathrooms[m][tail]);
                    bathrooms[m][tail] = NULL;
                    printf("after merge, the first become %d\n\n" ,bathrooms[pre][templocation]->id);
                }
                   
     
                if (existgroup == false){
                    printf("unfortunately, we can't find the same group in other line\n");
                    // we just update the whole list to the the space 
                    int entry = start[pre];
                    start[pre] = start[pre]+1;
                    
                    if (start[pre] == K){
                        start[pre] = 0;
                    }
                    printf("they are going to stay in[%d][%d]\n",pre,entry);
                    bathrooms[m][tail] = reverse(bathrooms[m][tail]);
                    bathrooms[pre][entry] = bathrooms[m][tail];
                    bathrooms[m][tail] = NULL;
                    printf("with %d standing at first\n\n",bathrooms[pre][entry]->id);
  
                    checkK[pre][tempgroup] = entry;

                }

                checkK[m][tempgroup] =-1 ;

                tail--;
                if (tail < 0){
                    tail = K-1;
                }
            }
            if (tail == head && fuckjustclose == false) {
                // tail is the current group's place

                printf("\nwe are dealing with group %d with %d standing at first in line %d \n",bathrooms[m][tail]->group,bathrooms[m][tail]->id,m);
                //bathrooms[m][tail] = reverse(bathrooms[m][tail]);
                //printf("after reverse%d is going to leave first to line %d \n\n" ,bathrooms[m][tail]->id,pre);
                //current group's group;
                int tempgroup = bathrooms[m][tail]->group;
    
                bool existgroup = false;
                int templocation;
                
                if (checkK[pre][tempgroup] != -1){
                    printf("luckily, we finds the same group in other line\n");
                    existgroup = true;
                    templocation = checkK[pre][tempgroup];
                    printf("before merge, the target group has first %d\n" ,bathrooms[pre][templocation]->id);
                    bathrooms[pre][templocation] = merge(bathrooms[pre][templocation],bathrooms[m][tail]);
                    bathrooms[m][tail] = NULL;
                    printf("after merge, the first become %d\n\n" ,bathrooms[pre][templocation]->id);
                }
                   
     
                if (existgroup == false){
                    printf("unfortunately, we can't find the same group in other line\n");
                    // we just update the whole list to the the space 
                    int entry = start[pre];
                    start[pre] = start[pre]+1;
                    
                    if (start[pre] == K){
                        start[pre] = 0;
                    }
                    printf("they are going to stay in[%d][%d]\n",pre,entry);
                    bathrooms[m][tail] = reverse(bathrooms[m][tail]);
                    bathrooms[pre][entry] = bathrooms[m][tail];
                    bathrooms[m][tail] = NULL;
                    printf("with %d standing at first\n\n",bathrooms[pre][entry]->id);
  
                    checkK[pre][tempgroup] = entry;

                }

                checkK[m][tempgroup] =-1 ;

                tail--;
                if (tail < 0){
                    tail = K-1;
                }
            }

            isclose[m] = 1;
   

        }
        free(title);
    }


    for(int width = 0; width < M;width++){// go over all the bathrooms
        printf("\nwe starts to print answer now\n");
        // we have to print from the head to tail
        int head = first[width];
        int tail = start[width]-1;
        // it is the first time
        bool dofirst;

        
        if (tail<0){
            tail = K-1;
        }
    

        // we print the last people in the head since it enters the head first
        while( head != tail && isclose[width]!=1){// while they doesn't meet each other 
            
            //printf("\nhead before reverse%d\n", bathrooms[width][head]->id);
            bathrooms[width][head] = reverse(bathrooms[width][head]);
            //printf("head after reverse%d\n", bathrooms[width][head]->id);
            traverse(bathrooms[width][head]);
            
            head++;
            if (head == K){
                head = 0;
            }
        }
        // do the last time
        if(head == tail && isclose[width]!=1){
            //printf("\nhead before reverse%d\n", bathrooms[width][head]->id);
            bathrooms[width][head] = reverse(bathrooms[width][head]);
            //printf("head after reverse%d\n", bathrooms[width][head]->id);
            traverse(bathrooms[width][head]);
        }
        printf("\n");

    }
   return 0;

}
 