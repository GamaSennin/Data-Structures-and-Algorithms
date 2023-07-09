#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#define N 1e3 // Value of size of array is determined by N

int long long comp_quick = 0; // variable for number of comparisions in quick-sort
int long long comp_merge = 0; // variable for number of comparisions in merge-sort
double cimp[(int)N]; // Global auxillary array for implementation of improved Merge Sort

void swap(double *a, double *b)
{ // Function to swap to elements
    double t = *a;
    *a = *b;
    *b = t;
    return;
}

int partition(double arr[], int si, int ei)
{ // Code for partition
    int i = si + 1;
    while (ei > i - 1)
    {
        if (arr[i] > arr[si])
        {
            swap(&arr[i], &arr[ei]);
            i--;
            ei--;
        }
        comp_quick++;
        i++;
    }
    swap(&arr[si], &arr[i - 1]);
    return i - 1;
}
void quicksort(double arr[], int si, int ei)
{ // Function to perform quicksort
    if (ei > si)
    {
        int ind = partition(arr, si, ei);
        quicksort(arr, si, ind - 1);
        quicksort(arr, ind + 1, ei);
    }
    return;
}

void merge(double arr[], int mid, int si, int ei)
{ // Function to perform merge sort(inefficent)
    int i = si, j = mid + 1, k = 0, size = ei - si + 1;
    int *c = (int *)(malloc(size * sizeof(double)));
    while (i <= mid && j <= ei)
    {
        if (arr[i] < arr[j])
        {
            c[k] = arr[i];
            k++;
            i++;
        }
        else if (arr[i] > arr[j])
        {
            c[k] = arr[j];
            k++;
            j++;
        }
        else
        {
            c[k] = arr[i];
            k++;
            i++;
        }
        comp_merge++;
    }
    if (i <= mid)
    {
        while (i <= mid)
        {
            c[k] = arr[i];
            k++;
            i++;
        }
    }
    else if (j <= ei)
    {
        while (j <= ei)
        {
            c[k] = arr[j];
            j++;
            k++;
        }
    }
    for (int l = 0; l < k; l++)
    {
        arr[si + l] = c[l];
    }
    free(c);
}
void mergesort(double arr[], int si, int ei)
{
    if (si >= ei)
    {
        return;
    }
    int mid = (ei + si) / 2;
    mergesort(arr, si, mid);
    mergesort(arr, mid + 1, ei);
    merge(arr, mid, si, ei);
}

void merge_imp(double arr[], int mid, int si, int ei)
{ // Improved version of merged sort with global auxillary array
    int i = si, j = mid + 1, k = 0;

    while (i <= mid && j <= ei)
    {
        if (arr[i] < arr[j])
        {
            cimp[k] = arr[i];
            k++;
            i++;
        }
        else if (arr[i] > arr[j])
        {
            cimp[k] = arr[j];
            k++;
            j++;
        }
        else
        {
            cimp[k] = arr[i];
            k++;
            i++;
        }
    }
    if (i <= mid)
    {
        while (i <= mid)
        {
            cimp[k] = arr[i];
            k++;
            i++;
        }
    }
    else if (j <= ei)
    {
        while (j <= ei)
        {
            cimp[k] = arr[j];
            j++;
            k++;
        }
    }
    for (int l = 0; l < k; l++)
    {
        arr[si + l] = cimp[l];
    }
}
void mergesort_imp(double arr[], int si, int ei)
{// Code to run Improved Merge-Sort
    if (si >= ei)
    {
        return;
    }
    int mid = (ei + si) / 2;
    mergesort_imp(arr, si, mid);
    mergesort_imp(arr, mid + 1, ei);
    merge_imp(arr, mid, si, ei);
}

int main()
{
    clock_t t;
    clock_t time_taken;
    srand((unsigned)time(NULL));
    int MAXRANGE = 100000;

    /*
    Q-1.1 Comparisions

    int long long avg_comp_quick=0;
    int long long avg_comp_merge=0
    double arr1[(int)N];
    double arr2[(int)N];

    for(int i=0;i<500;i++){

       for(int i=0;i<N;i++){
           double random_num = ( ( double ) rand ( ) / (double ) RAND_MAX)*MAXRANGE;
           arr1[i]=random_num;
           arr2[i]=arr1[i];
       }

       quicksort(arr1,0,N-1);
       avg_comp_quick+=comp_quick;
       comp_quick=0;

       mergesort(arr2,0,N-1);
       avg_comp_merge+=comp_merge;
       comp_merge=0;
   }

       printf("%d\n",avg_comp_merge/500);
       printf("%d\n",avg_comp_quick/500);

     */

    /*
     Q-1.2 Comparisions and Time Complexity of QuickSort

    FILE*fp;
    fp= fopen("output.csv","w" );

    int time_taken_microseconds=0;
    double arr[(int)N];

     for(int i=0;i<500;i++){

        for(int i=0;i<N;i++){
            double random_num = ( ( double ) rand ( ) / (double ) RAND_MAX)*MAXRANGE;
            arr[i]=random_num;
        }

         t=clock();
        quicksort(arr,0,N-1);
        time_taken=clock()-t;
        time_taken_microseconds+= ((double) time_taken*1000000/(double)CLOCKS_PER_SEC);

    }
        fprintf(fp,"%d %d",N,time_taken_microseconds/500);
        fclose(fp);

      */

    /*
     Q-1.3 Time Complexity
    FILE*fp1;
    FILE*fp2;
    fp1= fopen("quick.csv","w" );
    fp2= fopen("merge.csv","w" );

     int time_taken_microseconds1=0;
     int time_taken_microseconds2=0;
     double arr1[(int)N];
     double arr2[(int)N];
     int ctr=0;

     for(int i=0;i<500;i++){

        for(int i=0;i<N;i++){
            double random_num = ( ( double ) rand ( ) / (double ) RAND_MAX)*MAXRANGE;
            arr1[i]=random_num;
            arr2[i]=arr1[i];
        }

        t=clock();
        quicksort(arr1,0,N-1);
        time_taken=clock()-t;
        time_taken_microseconds1+= ((double) time_taken*1000000/(double)CLOCKS_PER_SEC);

        t=clock();
        mergesort(arr2,0,N-1);
        time_taken=clock()-t;
        time_taken_microseconds2+= ((double) time_taken*1000000/(double)CLOCKS_PER_SEC);

        if(time_taken_microseconds1>time_taken_microseconds2){
            ctr++;
        }

    }

        fprintf(fp1,"%d %d",N,time_taken_microseconds1/500);
        fprintf(fp2,"%d %d",N,time_taken_microseconds2/500);
        fclose(fp1);
        fclose(fp2);

        printf("%d\n",ctr);

      */

    /*
    Q-1.4 Improved Merge-Sort

   FILE*fp1;
   FILE*fp2;
   fp1= fopen("quick.csv","w" );
   fp2= fopen("merge_imp.csv","w" );

    int time_taken_microseconds1=0;
    int time_taken_microseconds2=0;
    double arr1[(int)N];
    double arr2[(int)N];
    int ctr=0;

    for(int i=0;i<500;i++){

       for(int i=0;i<N;i++){
           double random_num = ( ( double ) rand ( ) / (double ) RAND_MAX)*MAXRANGE;
           arr1[i]=random_num;
           arr2[i]=arr1[i];
       }

       t=clock();
       quicksort(arr1,0,N-1);
       time_taken=clock()-t;
       time_taken_microseconds1+= ((double) time_taken*1000000/(double)CLOCKS_PER_SEC);

       t=clock();
       mergesort_imp(arr2,0,N-1);
       time_taken=clock()-t;
       time_taken_microseconds2+= ((double) time_taken*1000000/(double)CLOCKS_PER_SEC);

       if(time_taken_microseconds1>time_taken_microseconds2){
           ctr++;
       }

   }

       fprintf(fp1,"%d %d",N,time_taken_microseconds1/500);
       fprintf(fp2,"%d %d",N,time_taken_microseconds2/500);
       fclose(fp1);
       fclose(fp2);

       printf("%d\n",ctr);

     */

    /*
    Q-2 Reliability of Quick Sort

    Following code prints no. of times code exceeds average by a certain
    percent for a particula value of n

   clock_t t;
   clock_t time_taken;
   srand((unsigned) time(NULL)) ;
   int MAXRANGE = 100000;
   double time_taken_microseconds1[500];
   double average=0;
   int ct[6];
   double percent[6];
   percent[0]=0.05;
   percent[1]=0.1;
   percent[2]=0.2;
   percent[3]=0.3;
   percent[4]=0.5;
   percent[5]=1;
   for(int i=0;i<500;i++){

       for(int i=0;i<N;i++){
   double random_num = ( ( double ) rand ( ) / (double ) RAND_MAX)*MAXRANGE;
   arr1[i]=random_num;


   }
       t=clock();
       quicksort(arr1,0,N-1);

       time_taken=clock()-t;
       time_taken_microseconds1[i]= ((double) time_taken*1000000/(double)CLOCKS_PER_SEC);
   average+=time_taken_microseconds1[i];
    }
    average/=500;
   for(int i=0;i<6;i++)
   {
       ct[i]=0;
       for(int j=0;j<500;j++)
       {
           if((double)average*(1+percent[i])<time_taken_microseconds1[j])
           ct[i]++;
       }
       printf("%d\n",ct[i]);
   }

   */
    return 0;
}