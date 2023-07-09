#include<stdio.h>
#include<stdlib.h>
#include <time.h>
#include<math.h>
int** multiply(int** arr1,int** arr2){
    int** ar=(int**)(malloc(2*sizeof(int*)));
    for(int i=0;i<2;i++){
        ar[i]=(int*)(malloc(2*sizeof(int)));
    }
    for(int i=0;i<2;i++){
            for(int j=0;j<2;j++){
                ar[i][j]=0;
               for(int k=0;k<2;k++){
                ar[i][j]=arr2[k][j]*arr1[i][k]+ar[i][j];
                ar[i][j]=ar[i][j]%2021;
               }
            }
        }
        return ar;
}
int** func(int long long n,int **arr){
    if(n==1){
        return arr;
    }
    int** a=func(n/2,arr);
    int**b=multiply(a,a);
    if(n%2==0){ 
        return b;
    }
    else{
        return multiply(b,arr);
    }
}
int Rfib(int long long n){
    if(n==0 || n==1){
        return n;
    }
    return (Rfib(n-1)+Rfib(n-2))%2021;
}
int Ifib(int long long n){
    if(n==0 || n==1){
        return n;
    }
    int a=0;
    int b=1;
    int temp;
    for(long long int i=2;i<=n;i++){
        temp=b;
       b=(a+b)%2021;
        a=temp;
    }
    return b%2021;
}
int cleverFib(int long long n){
    int** arr=(int**)(malloc(2*sizeof(int*)));
    for(int i=0;i<2;i++){
        arr[i]=(int*)(malloc(2*sizeof(int)));
    }
    arr[0][0]=1;arr[0][1]=1;arr[1][0]=1;arr[1][1]=0;
    int **a=func(n,arr);
    return a[1][0]%2021;
}
int main(){
clock_t start_tc, end_tc,start_ti, end_ti,start_tr, end_tr;

     int long long n;
     scanf("%lld",&n);
//Rfib
start_tr = clock();
    printf("%d\n",Rfib(n));
end_tr = clock();
double total_t1 = (double)(end_tr - start_tr)/(CLOCKS_PER_SEC);


// IFib
start_ti = clock();
    printf("%d\n",Ifib(n));
end_ti = clock();
double total_t2 = (double)(end_ti - start_ti) / (CLOCKS_PER_SEC);


// CleverFib
     start_tc = clock();
      printf("%d",cleverFib(n));
    end_tc = clock();
   double total_t3 = (double)(end_tc - start_tc) /(CLOCKS_PER_SEC);
   
    return 0;
}
