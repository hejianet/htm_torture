#include<stdio.h>
#include<inttypes.h>
#include "torture.h"

/* Abort due to syscall (printf); */
void workload0() {
	printf("Workload 0\n");
}

/* ----------- */
int fib(int x){
	if (x == 2 || x == 1)
		return 1;

	return fib(x-1) + fib(x-2);
}

/* Run a fibonnaci of 40 inside transaction */
void workload1() {
	int sum;
	int n = 40;

	sum = fib(n);
}

/* ----------- */
/* single nop  inside a transaction */
void workload2() {
	_ ("or 0,0,0 \n");
}

/* ----------- */
/* Calling tabort inside transaction */
void workload3() {
	_ ("tabort.  0\n");
}

/* ----------- */
/* Quick sort workload */
void quicksort(int *A, int len)
{
  if (len < 2) return;
 
  int pivot = A[len / 2];
 
  int i, j;
  for (i = 0, j = len - 1; ; i++, j--)
  {
    while (A[i] < pivot) i++;
    while (A[j] > pivot) j--;
 
    if (i >= j) break;
 
    int temp = A[i];
    A[i]     = A[j];
    A[j]     = temp;
  }
 
  quicksort(A, i);
  quicksort(A + i, len - i);
}

/* ----------- */
void workload4() {
	int a[] = {12, 3}; //, 9, 4, 9, 64};
	int n = sizeof a / sizeof a[0];
	quicksort(a, n);
}

/* ----------- */
/* loop */
void workload5() {
	int i ;
	for (i=0; i < 10; )
		i++;
}

// Infinite loop.
void workload6() {
	while(1);
}

/*** workdload7 ***/

unsigned long *array;

void Swap(unsigned long *a, unsigned long *b)
{
        int temp;
        temp = *a;
        *a = *b;
        *b = temp;
}

void PartitionArray(unsigned long *a, int left, int right, int *PivotLoc)
{
        *PivotLoc = left;

        while(1)
        {
                while(*(a+(*PivotLoc)) <= *(a+right) && *PivotLoc != right)
                {
                        right--;
                }
                if(*PivotLoc == right)
                {
                        break;
                }
                else if(*(a+(*PivotLoc)) > *(a+right))
                {
                        Swap((a+(*PivotLoc)), (a+right));
                        *PivotLoc = right;
                        left++;
                }

                while(*(a+(*PivotLoc)) >= *(a+left) && *PivotLoc != left)
                {
                        left++;
                }
                if(*PivotLoc == left)
                {
                        break;
                }
                else if(*(a+(*PivotLoc)) < *(a+left))
                {
                        Swap((a+(*PivotLoc)), (a+left));
                        *PivotLoc = left;
                        right--;
                }
        } // end while(1)
}

void QuickSort(unsigned long *a, int left, int right)
{
        if(left < right)
        {
                int PivotLoc;
                PartitionArray(a, left, right, &PivotLoc);
                QuickSort(a, left, PivotLoc-1);
                QuickSort(a, PivotLoc+1, right);
        }
}

void utpsm_qsort()
{
        QuickSort(array, 0, ARRAY_SIZE-1);
}

// illegal instruction.
void workload8() {
  _ (".long 0x0");
}

// trap
void workload9() {
  _ ("trap");
}
