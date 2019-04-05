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

void rng(int* arr, int n) {
    int seed = 13515070;
    srand(seed);
    for(long i = 0; i < n; i++) {
        arr[i] = (int)rand();
    }
}

  
// A utility function to get maximum value in arr[] 
int getMax(int arr[], int n) 
{ 
    int mx = arr[0]; 
    for (int i = 1; i < n; i++) 
        if (arr[i] > mx) 
            mx = arr[i]; 
    return mx; 
} 
  
// A function to do counting sort of arr[] according to 
// the digit represented by exp. 
void countSort(int arr[], int n, int exp) 
{ 
    int output[n]; // output array 
    int i, count[10] = {0}; 
  
    // Store count of occurrences in count[] 
    for (i = 0; i < n; i++) 
        count[ (arr[i]/exp)%10 ]++; 
  
    // Change count[i] so that count[i] now contains actual 
    //  position of this digit in output[] 
    for (i = 1; i < 10; i++) 
        count[i] += count[i - 1]; 
  
    // Build the output array 
    for (i = n - 1; i >= 0; i--) 
    { 
        output[count[ (arr[i]/exp)%10 ] - 1] = arr[i]; 
        count[ (arr[i]/exp)%10 ]--; 
    } 
  
    // Copy the output array to arr[], so that arr[] now 
    // contains sorted numbers according to current digit 
    for (i = 0; i < n; i++) 
        arr[i] = output[i]; 
} 
  
// The main function to that sorts arr[] of size n using  
// Radix Sort 
void mpi_radix_sort(int arr[], int n) 
{ 
    // Find the maximum number to know number of digits 
    int m = getMax(arr, n); 
  
    // Do counting sort for every digit. Note that instead 
    // of passing digit number, exp is passed. exp is 10^i 
    // where i is current digit number 
    for (int exp = 1; m/exp > 0; exp *= 10) 
        countSort(arr, n, exp); 
} 
  
void print(int arr[], int n) 
{ 
    for (int i = 0; i < n; i++) 
        cout << arr[i] << "\n"; 
} 
  
int main(int argc, char **argv) 
{ 
    double start,stop; //waktu
    int n = atoi(argv[1]); //jumlah elemen
    int p,i,j; //p = jumlah thread, i/j = counter
    int arr[n]; //array elemen
    int my_rank;
    MPI_Status status;

    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);
    MPI_Comm_size(MPI_COMM_WORLD,&p);
    
    if(my_rank == 0) {
	
	//init array
    	rng(arr,n);
	int s = n/p;
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

    //init array lokal
    int s = n/p; //jumlah elemen dalam array lokal
    int l_arr[s]; //array lokal
    
    start = MPI_Wtime();

    //proses radix sort
    MPI_Scatter(arr, s, MPI_INT, l_arr, s, MPI_INT, 0, MPI_COMM_WORLD);
    mpi_radix_sort(l_arr, s);
    MPI_Gather(l_arr, s, MPI_INT, arr, s, MPI_INT, 0, MPI_COMM_WORLD);

    stop = MPI_Wtime();
    
    if (my_rank == 0) {
	//result array output
	FILE * fout;
	fout = fopen("output","w");
	for(i=0;i<n;i++)
		fprintf(fout,"%d\n",arr[i]);
	fclose(fout); 
	printf("time for radix sort for %d elements by %d processes: %f seconds\n",n,p,(stop-start));
    }
    MPI_Finalize();
} 