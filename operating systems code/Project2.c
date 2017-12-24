/* C program for Merge Sort, compliments of geeksforgeeks.org */
/* code found here: https://www.geeksforgeeks.org/merge-sort/ */
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

int array[] = {9, 12, 64, 0, 8, -1, 12, 16, 13};

// Merges two subarrays of arr[].
// First subarray is arr[l..m]
// Second subarray is arr[m+1..r]
void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;

    /* create temp arrays */
    int L[n1], R[n2];

    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];

    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        };
        k++;
    }

    /* Copy the remaining elements of L[], if there
       are any */
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    /* Copy the remaining elements of R[], if there
       are any */
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

/* l is for left index and r is right index of the
   sub-array of arr to be sorted */
void mergeSort(int arr[], int l, int r)
{
    if (l < r)
    {
        // Same as (l+r)/2, but avoids overflow for
        // large l and h
        int m = l+(r-l)/2;

        // Sort first and second halves
        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);

        merge(arr, l, m, r);
    }
}

/* UTILITY FUNCTIONS */
/* Function to print an array */
void printArray(int A[], int size)
{
    int i;
    for (i=0; i < size; i++)
        printf("%d ", A[i]);
    printf("\n\n");
}

void *wrapSortH(void *param){
  int size = sizeof(array) / sizeof(array[0]);
  int mid = floor(size/2.0);
  mergeSort(array, mid + 1, size - 1);

  return 0;
}

void *wrapSortL(void *param){
  int size = sizeof(array) / sizeof(array[0]);
  int mid = floor(size/2.0);
  mergeSort(array, 0, mid);

  return 0;
}

void *wrapMerge(void *param){
  int size = sizeof(array) / sizeof(array[0]);
  int mid = floor(size/2);

  merge(array, 0, mid, size - 1);

  return 0;
}

/* main */
int main()
{
  /* start initializers */
  pthread_t tid1;
  pthread_t tid2;
  pthread_t tid3;
  pthread_attr_t attr;

  int size = sizeof(array) / sizeof(array[0]);
  int mid = floor(size/2.0);
  /* end initializers */

  printf("Unsorted array: \n");
  printArray(array, size);

  printf("Beginning split sorts.\n\n");
  pthread_attr_init(&attr);
  pthread_create(&tid1, &attr, wrapSortL, NULL);
  pthread_create(&tid2, &attr, wrapSortH, NULL);
  pthread_join(tid1, NULL);
  pthread_join(tid2, NULL);

  printf("Done with split sorts. Current array: \n");
  printArray(array, size);

  printf("Beginning merge.\n\n");
  pthread_create(&tid3, &attr, wrapMerge, NULL);
  pthread_join(tid3, NULL);

  printf("Sorted array: \n");
  printArray(array, size);

}
