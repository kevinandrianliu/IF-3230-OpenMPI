#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstdio>
#include <cstdlib>
#include <utility>
#include <math.h>
#include <mpi.h>

#define MASTER 0
using namespace std;

double startT, stopT;
int position(int *arr, int eff_size);

//declare random array procedure
void rng(int* arr, int n) {
    int seed = 13515070;
    srand(seed);
    for(long i = 0; i < n; i++) {
        arr[i] = (int)rand();
    }
}

//sorting procedure
void sort(int *arr, int s)
{
	int eff_size, minpos;
	int temp;
	
	for(eff_size = s; eff_size > 1; eff_size--) {
		minpos = position(arr, eff_size);
		temp = arr[minpos];
		arr[minpos] = arr[eff_size-1];
		arr[eff_size-1] = temp;
	}
}

//define position function
int position(int *arr, int eff_size)
{
	int i, min = 0;
	
	for(i=0; i<eff_size; i++)
		min = arr[i] > arr[min] ? i: min;
	return min;
}


main(int argc, char **argv)
{
	int * arr; //array elemen
	int * local_array; //array lokal
	int n = atoi(argv[1]); //jumlah elemen dalam array
	int s; //jumlah elemen dalam array lokal = n/p
	int p; // jumlah processor
	int my_rank; //rank
	int i,j; //counter

	MPI_Status status;

	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);
	MPI_Comm_size(MPI_COMM_WORLD,&p);

	//declare input array + file
	if(my_rank==0)
	{
		//initial array
		arr = (int *)malloc(n*sizeof(int));
		rng(arr,n);
		s = n/p;
		for (j=0; j<p; j++) {
			for (i=0; i<s; i++){
				arr[j*s+i] = arr[j*s+i]%(2*n/p)+(j*2*n/p);
			}
		}

		//external input file
		FILE * fout;
		fout = fopen("input","w");
		for(i=0;i<n;i++)
			fprintf(fout,"%d\n",arr[i]);
		fclose(fout);
	}

	//start timer
	startT = MPI_Wtime();

	//define local array
	s = n/p;
	local_array = (int*)malloc(s*sizeof(int));

	//split to threads
	MPI_Scatter(arr, s, MPI_INT, local_array, s, MPI_INT, 0, MPI_COMM_WORLD);

	//sorting on each thread
	sort(local_array, s);

	//recombine sorted arrays on threads
	MPI_Gather(local_array, s, MPI_INT, arr, s, MPI_INT, 0, MPI_COMM_WORLD);

	//stop timer
	stopT = MPI_Wtime();

	//print time + result array
	if(my_rank==0)
	{

		//time
		printf("%d threads for %d elements: %f secs\n", p, n, (stopT-startT));
		
		//result array output
		FILE * fout;
		fout = fopen("output","w");
		for(i=0;i<n;i++)
			fprintf(fout,"%d\n",arr[i]);
		fclose(fout);
	}

	//free memory
	free(local_array);
	if (my_rank==0)
		free(arr);

	MPI_Finalize();
}
