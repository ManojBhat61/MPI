/*
 * mpi_hello.c
 *
 *  Created on: Jun 30, 2016
 *      Author: root
 */



#include <stdio.h>
#include <string.h>
#include <mpi.h>

const int MAX_STRING = 100;

int main(void)
{

   int comm_sz; /* Number of processes */
   int my_rank; /* My process rank */

	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

	/* call function */
	/* greeting( my_rank, comm_sz); */
    
    /* call the next function */
    addnumbers( my_rank, comm_sz);

	MPI_Finalize();
	return 0;
}

void greeting( int my_rank, int comm_sz)
{
	char greeting[MAX_STRING];
	if (my_rank != 0) {
		sprintf(greeting, "Greetings from process %d of %d!", my_rank, comm_sz);
		MPI_Send(greeting, strlen(greeting)+1, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
	} else {
		printf("Greetings from process %d of %d!\n", my_rank, comm_sz);
		int q = 0;
		for (q = 1; q < comm_sz; q++) {
			MPI_Recv(greeting, MAX_STRING, MPI_CHAR, q, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			printf("%s\n", greeting);
		}
	}

}
void addnumbers(int my_rank, int comm_sz)
{
	printf(" Here 1\n");
	if ( my_rank == 0)
	{
		printf(" Here 2\n");
		int q = 0; int start = 1; int end = 10;
		for (q = 1; q < comm_sz; q++) {
	        printf(" ** my_rank = %d, start = %d, q = %d\n", my_rank, start, q);
            
            /* destination is important. */
			MPI_Send(&start, 1, MPI_INT, q, 0, MPI_COMM_WORLD);
            start = start + end;
		}
	}
    else
    {
    	printf(" Here 2a\n");
       	int sum = 0;
        int start = 0;
        int i = 0;
        printf ("Here 2b - before receive\n");
        /* first 0 says that the source is the proces 0 */
        MPI_Recv( &start, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf ("Here 2c - after receive\n");
        for (i = start; i < (start + 10); i++)
            sum = sum + i;
        printf(" ** my_rank = %d, start = %d, sum = %d\n", my_rank, start, sum);
    }
    
}
