#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define NTHREADS 10

int n=2;
int m=3;
int p=3;
int q=4;

int a[2][3]={{ 2, 5, 7 },{ 4, 7, 9 }};
int b[3][4]={{ 1, 3, 5, 7 },{ 9, 2, 4, 3 },{ 1, 3, 1, 6}};
int c[2][4];

struct arg_struct
{
   int arg1;
   int arg2;
} *args;

void *MatMulti (void *arguments)
{
   struct arg_struct *args = arguments;
  
     for (int k = 0; k < m; k++) {
    c[args->arg1][args->arg2] += a[args->arg1][k] * b[k][args->arg2];
    }
    
   pthread_exit(NULL);
   return NULL;
}

int main()
{
    int b=1;
    int count=0;
    pthread_t tid[NTHREADS];
    void * retvals[NTHREADS];
    
     if(m!=p){
        printf("Invalid Matrix");
        b=0;
    }
    
     for (int i = 0; i < n; i++) {
        for (int j = 0; j < q; j++) {
            c[i][j] = 0;
       
             args = malloc(sizeof(struct arg_struct) * 1);

             args->arg1 = i;
             args->arg2 = j;
            
            if (pthread_create(&tid[count], NULL, &MatMulti, args) != 0)
       {
          printf("Uh-oh!\n");
          return -1;
       }
            count++;

            }
        }
    
    for (int i = 0; i < count; i++){
   
    if(pthread_join(tid[i], &retvals[i])){
    return -2;
    }
   
    }
    
    if(b==1){
     printf("The product of the two matrices is: \n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < q; j++) {
            printf("%d\t", c[i][j]);
        }
        printf("\n");
    }
    }
    
   return 0;
}
