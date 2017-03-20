The C program can be executed using slurm_apsp.sh or compiling it in terminal itself. 

apsp_small.c solves a graph with 4 nodes(graph taken from wiki to validate implementation).

apsp_1200_nodes solves a graph with 1200 nodes. 

Execute the c program as 
gcc apsp_small.c -o apsp_small
./apsp_small

gcc -fopenmp apsp_1200_nodes.c -o apsp_1200_nodes
./apsp_1200_nodes


Note: When the program was executed using slurm_apsp.c in RC, time was same for all threads. But there was decrease in execution time when C program was executed in terminal itself, compiling using gcc and running it.
