/*! \file BST.c
 *  \brief     this implement the operation to create a BST optimal
 *  \author    Bin Mohmad Shah Hariz
 *  \version   1.0
 *  \date      9/4/2017
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>
#include <BST.h>

static int **sum_frequency;
static int **optimal_cost;
static int **possible_root;
static int **BSTtree;
static int *frequency;
static int *array;
static int element;

int verify_element_number(int n, FILE *stream){
  int temp;
  int count = 0;
  int index = 0;
  frequency = malloc(n*sizeof(int));
  while( (fscanf(stream,"%i",&temp)) != EOF){
    if(count <= n){
      frequency[index] = temp;
      index++;
    }
    count++;
  }
  
  if(n <= count) {
    element = index;
    return 0;
  }else{
    fprintf(stdout, "The total element in file is: %i\n",count);
    free(frequency);
    frequency = NULL;
    return -1;
  }
}

void free_all_allocation(){
  free(array);
  free(frequency);
  for(int i = 0; i<element; i++){
    free(BSTtree[i]);
    free(sum_frequency[i]);
    free(optimal_cost[i]);
    free(possible_root[i]);
    
    BSTtree[i] = NULL;
    sum_frequency[i] = NULL;
    optimal_cost[i] = NULL;
    possible_root[i] = NULL;
  }

  free(BSTtree);
  free(sum_frequency);
  free(optimal_cost);
  free(possible_root);

  BSTtree = NULL;
  sum_frequency = NULL;
  optimal_cost = NULL;
  possible_root = NULL;
  array = NULL;
  frequency = NULL;
}

void create_element_array(){
  array = malloc(element*sizeof(int));
  BSTtree = malloc(element*sizeof(int*));
  sum_frequency = malloc(element*sizeof(int*));
  optimal_cost = malloc(element*sizeof(int*));
  possible_root = malloc(element*sizeof(int*));
  for(int i=0; i<element; i++){
    array[i] = i;
    BSTtree[i] = malloc(2*sizeof(int));
    BSTtree[i][0] = -1;
    BSTtree[i][1] = -1;
    sum_frequency[i] = malloc(element*sizeof(int));
    optimal_cost[i] = malloc(element*sizeof(int));
    possible_root[i] = malloc(element*sizeof(int));
  }
}

void initialization_possible_roots(){
  for(int i = 0; i < element; i++){
    for(int j = 0; j < element; j++){
      possible_root[i][j] = -1;
    }
  }
}

void* e( int i ) {
  assert( (i>=0) && (i<element));
  return (void*) &(array[i]);
}

void initialization_sum_freq(){
  for(int i=0; i<element; i++){
    for(int j=i; j<element; j++){
      if(j != 0){
	sum_frequency[i][j] = sum_frequency[i][j-1] + frequency[j];
      }else{
	sum_frequency[i][j] = frequency[j];
      }
    }
  }
}

void calculate_optimal_cost(int i, int j){
  optimal_cost[i][j] = INT_MAX;
  int temp = 0;
  for(int r = i; r <= j; r++){
    if(r==j){
      temp = optimal_cost[i][r-1];
    }else if( r == i){
      temp = optimal_cost[r+1][j];
    }else{
      temp = optimal_cost[i][r-1] + optimal_cost[r+1][j];
    }

    if(temp < optimal_cost[i][j]){
      possible_root[i][j] = r;
      optimal_cost[i][j] = temp;
    }
  }
  
  optimal_cost[i][j] = optimal_cost[i][j] + sum_frequency[i][j];
}


void computeABROpt(){
  initialization_sum_freq();

  for(int i = element-1; i>=0; i--){
    for(int j = i; j < element; j++){
      calculate_optimal_cost(i,j);
    }
  }
}

void organise_BSTtree(){
  put_BSTtree(0, element-1);
}

void put_BSTtree(int from,int to){
  int root = possible_root[from][to];

  if(from >= to){   
    return;
  }

  if(root == 0){
    put_BSTtree(root+1,to);
    BSTtree[root][1] = possible_root[root+1][to];
     return;
  }

  if(root == element-1){
    put_BSTtree(from,root-1);
    BSTtree[root][0] = possible_root[from][root-1];
    return;
  }

  put_BSTtree(from,root-1);
  put_BSTtree(root+1,to);
  
  BSTtree[root][0] = possible_root[from][root-1];
  BSTtree[root][1] = possible_root[root+1][to];
}


void write_BST_code(){
  fprintf(stdout, "static long BSTdepth = %i; // pour info. Non demandé\n",
	  optimal_cost[0][element-1]);
  fprintf(stdout, "static int BSTroot = %i;\n", possible_root[0][element-1]);
  fprintf(stdout, "static int BSTtree[%i][2] = {", element);
  for(int i=0; i<element; i++){
    fprintf(stdout, "\n{%i, %i}",BSTtree[i][0], BSTtree[i][1]);
    if(i < element-1) {
	fprintf(stdout, ", ");
    }
  }
  fprintf(stdout, " };\n");
  fprintf(stdout, "static int opt =%i;\n",optimal_cost[0][element-1]);
  fprintf(stdout, "static int p[%i] = {\n", element);
  for(int i=0; i<element; i++){
    fprintf(stdout, "%i",frequency[i]);
    if(i < element-1) {
	fprintf(stdout, ", \n");
    }
  }
  fprintf(stdout, "};");
}

/* ------------------operation naive ------------------- */

int sum(int from, int to)
{
    int total = 0;
    for (int i = from; i <= to; i++){
      total = total + frequency[i];
    }
    return total;
}

int cost_optimal(int i, int j)
{
   if (j < i)      
     return 0;
   if (j == i)     
     return frequency[i];

   int total_frequency = sum(i, j);

   int min = INT_MAX;

   for (int r = i; r <= j; r++)
   {
       int temp = cost_optimal(i, r-1) + cost_optimal(r+1, j);
       if (min > temp)
          min = temp;
   }
 
   return min + total_frequency;
}
 
void computeABROpr_naive()
{
  fprintf(stdout, "Optimal cost: %i\n", cost_optimal(0, element-1));
}
