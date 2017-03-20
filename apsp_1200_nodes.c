// Import header files for program
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

//Define the number of nodes in the graph
#define N 1200

//Define minimum function that will be used later on to calcualte minimum values between two numbers
#ifndef min
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif

//Define matrix of size N * N to store distances between nodes
//Initialize all distances to zero
int distance_matrix[N][N] = {0};

int main(int argc, char *argv[])
{
  int nthreads;
  int src, dst, middle;
  
  //Initialize the graph with random distances
  for (src = 0; src < N; src++)
  {
    for (dst = 0; dst < N; dst++)
    {
      // Distance from node to same node is 0. So, skipping these elements
      if(src != dst) {
        //Distances are generated to be between 0 and 19
        distance_matrix[src][dst] = rand() % 20;
      }
    }
  }
  
  //Define time variable to record start time for execution of program
  double start_time = omp_get_wtime();
  
  for (middle = 0; middle < N; middle++)
  {
    int * dm=distance_matrix[middle];
    for (src = 0; src < N; src++)
    {
      int * ds=distance_matrix[src];
      for (dst = 0; dst < N; dst++)
      {
        ds[dst]=min(ds[dst],ds[middle]+dm[dst]);
      }
    }
  }
  
  double time = omp_get_wtime() - start_time;
  printf("Total time for sequential (in sec):%.2f\n", time);
  
  for(nthreads=1; nthreads <= 10; nthreads++) {
    //Define different number of threads
    omp_set_num_threads(nthreads);
    
    // Define iterator to iterate over distance matrix
    //Define time variable to record start time for execution of program
    double start_time = omp_get_wtime();
    
    /* Taking a node as mediator
    check if indirect distance between source and distance via mediator
    is less than direct distance between them */
    #pragma omp parallel shared(distance_matrix)
    for (middle = 0; middle < N; middle++)
    {
      int * dm=distance_matrix[middle];
      #pragma omp parallel for private(src, dst) schedule(dynamic)
      for (src = 0; src < N; src++)
      {
        int * ds=distance_matrix[src];
        for (dst = 0; dst < N; dst++)
        {
          ds[dst]=min(ds[dst],ds[middle]+dm[dst]);
        }
      }
    }
    
    double time = omp_get_wtime() - start_time;
    printf("Total time for thread %d (in sec):%.2f\n", nthreads, time);
  }
  return 0;
  
}
