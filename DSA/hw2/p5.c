#include <stdio.h> 
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <stdint.h>

typedef struct City { // we create the city as a structure 
   int distance; // it indicate how far the city is to the reference point
   int nearestmain;
   bool onmainline;

}city; // next time we can call the City "city"

//create a 1D array of cities that stores according to their name(index) 
city ** new_city(int length) // length is how many cities there are             
{                                                       
   city **ct = (city**)malloc(length*sizeof(city*));  // ct is a pointer that points to each city structure pointer 

   for(int i = 0; i < length; i++){
      ct[i] = (city*)malloc(sizeof(city));
   }
        

   for(int i=0; i < length; i++) {

      ct[i]->distance = -1;
      ct[i]->onmainline = false;
      ct[i]->nearestmain = -1;
   }
   
   if (!ct){// if st is a null pointer
      return ct;   
      printf("i think we are in trouble now ");
   }                                                                              

   return ct;                                        
}


int main(int argc, char* argv[]){
   int N,Q,S,R;
   scanf("%d %d %d %d", &N, &Q, &S, &R);
   // don't use the map[0]
   city **map = new_city(N+1);
   // it shows that how many citites are link to the specific city   
   int connections[N+1];//from 1 to N
   memset(connections, -1, (N+1)*sizeof(connections[0]));
   // set up the (N+1)*2 adjacency matrix 
   int **adjmatrix = (int**)calloc(N+1, sizeof(int*));
   for(int i = 0; i < N+1; i++){
      adjmatrix[i] = (int*)calloc(2, sizeof(int));
   }

   for(int i = 0; i < N+1; i++) {
      for(int j = 0; j < 2; j++) {
         adjmatrix[i][j] = -1;
      }  
   }
   // evrey city(from 1 - N) we remember their capacity
   int capacityofmatrix[N+1];
   memset(capacityofmatrix, 2, (N+1)*sizeof(capacityofmatrix[0]));
   


   // starts to read the connection between two cities
   for(int times = 0;times < N-1;times ++){
      int cit1,cit2;
      scanf("%d %d", &cit1, &cit2);
      if(connections[cit1] == -1){
         connections[cit1] = 0; 
      }
      if(connections[cit2] == -1){
         connections[cit2] = 0; 
      }

      if (connections[cit1]>=capacityofmatrix[cit1]){
         //expand the matrix as double of current capacity
         capacityofmatrix[cit1]*=2;
         int *new = malloc(capacityofmatrix[cit1]*sizeof(int));

         int index = 0;
         while (index < connections[cit1]){
            new[index]=adjmatrix[cit1][index];
            index++;
         }

         adjmatrix[cit1] = new;
         
      }

      // check do we need to free new
      if (connections[cit2]>=capacityofmatrix[cit2]){
         //expand the matrix as double of current capacity
         capacityofmatrix[cit2]*=2;
         int *new = malloc(capacityofmatrix[cit2]*sizeof(int));

         int index = 0;
         while (index < connections[cit2]){
            new[index]=adjmatrix[cit2][index];
            index++;
         }

         adjmatrix[cit2] = new;
      }
      adjmatrix[cit1][connections[cit1]] = cit2;
      adjmatrix[cit2][connections[cit2]] = cit1;
      connections[cit1]+=1;
      connections[cit2]+=1;
   }
   printf("\nthis is the adjmatrix\n");
   for (int i = 0; i < N+1; i++){
      for (int j = 0; j < N+1; j++){
         printf("%d ", adjmatrix[i][j]);
      }
      printf("\n");
   }
   // find the node which is singly linked as the top and starts to arrange the distance
   int visited = 0;
   // where we are now
   int location = 0; 

   for (int i = 1;i < N+1; i++ ){
      if (connections[i] == 1){
         location = i;
         break;
      }
   }
 
   map[location]->distance = 0;// set the distance of root as zero
   int queue[N]; // we put the cities that connects to current city into the stack
   memset(queue, -1, N*sizeof(queue[0]));
   int headofqueue = 0;
   queue[headofqueue] = location;// we put current location to the head of queue
   headofqueue++;
    
   
   
   // now we start from the current location
   while(visited < N){
      // whenever we read a city from our current location, we enqueue all its connecitons and write down their location
      for (int i = 0; i < connections[location];i ++){
         
         // if connect city hasn't been given value // if it's been given value we just skip it
         if (map[adjmatrix[location][i]]->distance == -1 ){ 
            queue[headofqueue] = adjmatrix[location][i]; // add it to the queue
            map[queue[headofqueue]]->distance = map[location]->distance + 1; // set its distance as one more than current location
            headofqueue++;
         }
                 
      }
      // update current location
      location = queue[visited];
      visited++;

      
   }
   
   // now we want to find the main line between resort and capital
   // set up the relative distance to the current root
   int reldisfromresort = map[R]->distance;
   int reldisfromcapital = map[S]->distance;
   map[R]->onmainline = true;
   map[R]->nearestmain = R;
   map[S]->onmainline = true;
   map[S]->nearestmain = S;
   int loc1 = R;
   int loc2 = S;

   // build up the main line
   while (loc1 != loc2){
      if (reldisfromresort > reldisfromcapital){
         // now resort is furthur so we move it a step before
         for( int i = 0; i < connections[loc1]; i ++ ){
            // for each that connects to current city, we find the parent city 
            if(map[adjmatrix[loc1][i]]->distance == map[loc1]->distance-1){
               // if we find the before city set it on main line and reset curr location and distance
               loc1 = adjmatrix[loc1][i];
               map[loc1]->onmainline = true;
               map[loc1]->nearestmain = loc1;
               reldisfromresort = map[loc1]->distance;
                
               break;
            } 
         }

      }
      else if (reldisfromcapital > reldisfromresort){
         // now capital is furthur so we move it a step before
         for( int i = 0; i < connections[loc2]; i ++ ){
            // for each that connects to current city, we find the parent city
            if(map[adjmatrix[loc2][i]]->distance == map[loc2]->distance-1){
               // if we find the before city set it on main line and reset curr location and distance
               loc2 = adjmatrix[loc2][i];
               map[loc2]->onmainline = true;
               map[loc2]->nearestmain = loc2;
               reldisfromcapital = map[loc2]->distance;

               break;
            } 
         }

      }
      // if they are at the same distance just move back both until they are at the same place
      else{
         for( int i = 0; i < connections[loc1]; i ++ ){
            // for each that connects to current city, we find the parent city 
            if(map[adjmatrix[loc1][i]]->distance == map[loc1]->distance-1){
               // if we find the before city set it on main line and reset curr location and distance
               loc1 = adjmatrix[loc1][i];
               map[loc1]->onmainline = true;
               map[loc1]->nearestmain = loc1;
               reldisfromresort = map[loc1]->distance;
               
               break;
            } 
         }
         for( int i = 0; i < connections[loc2]; i ++ ){
            // for each that connects to current city, we find the parent city
            if(map[adjmatrix[loc2][i]]->distance == map[loc2]->distance-1){
               // if we find the before city set it on main line and reset curr location and distance
               loc2 = adjmatrix[loc2][i];
               map[loc2]->onmainline = true;
               map[loc2]->nearestmain = loc2;
               reldisfromcapital = map[loc2]->distance;

               break;
            } 
         }

      }
   }

   for(int i = 1; i < N+1; i++){
      if(map[i]->onmainline == true){
         printf("\ncity %d is on the main line with nearst %d", i,map[i]->nearestmain);
      }
   }

   // for every mainline city, walk out until it meets the singly linked city 
   int waiting[N];
   memset(waiting, -1, N*sizeof(waiting[0]));
   int waitingentry = 0;
   int waitingcurr = 0;
   int currloc = -1;
   // first put all the main line city into the map
   for(int i = 1; i < N+1; i++){
      if(map[i]->onmainline == true){
         waiting[waitingentry] = i;
         waitingentry++;
      }
   }
   currloc = waiting[waitingcurr];
   while (waitingcurr < N){
      // for every city in the waiting, push its connections into the waiting
      for(int i = 0; i < connections[currloc];i ++){
         if(map[adjmatrix[currloc][i]]->nearestmain == -1){ // for every of its connections that are not on the main line
            waiting[waitingentry] = adjmatrix[currloc][i]; // push them into waiting
            map[adjmatrix[currloc][i]]->nearestmain = map[currloc]->nearestmain;
            waitingentry++;
         }
      }

      waitingcurr++;
      currloc = waiting[waitingcurr];

      
   }
   for(int i = 1; i< N+1;i++){
      printf("\nthis is city %d,with its nearestmain %d",i,map[i]->nearestmain);
   }
   
   printf("\n\nwe start to answer the queries\n");

   // starts to answer the quries 
   for(int quries = 0;quries < Q ;quries++){
      int querycity = 0;

      scanf(" %d", &querycity );
      printf("%d\n",map[querycity]->nearestmain);

   
      
   }
   return 0;
}
 