
#include <stdlib.h> 
#include <stdio.h>

void PP(int *fibs, int len){
    for(int i = 0; i < len; i++){
        printf("%d ", fibs[i]);
    }
    printf("\n");
    
}


void fib(int *fibs, int len){
    
    //init
    int hold[len+1];
    for(int i = 0; i < len; i++){fibs[i] = 1; hold[i] = 1;} hold[len] = 1;
    

  if (len % 2 == 0) { //even
    for(int i = 0; i < len - 2; i++){
        
        if(i % 2 == 0){
            
            for(int j = 0; j <= i/2; j++){
                
                hold[len/2 + j] = fibs[len/2 - 1 + j] + fibs[len/2 + j];
                hold[len/2 - j] = fibs[len/2 - 1 + j] + fibs[len/2 + j];
                
            }
            ////printf
                printf("HOLD(%d): ",i);for(int k = 0; k < len+1; k++){ printf("%d ", hold[k]);} printf("\n");
                ////
        } else {
        
            for(int j = 0; j <= i/2; j++){
                fibs[len/2 - 1 - j] = hold[len/2 + j] + hold[len/2 + 1 + j];
                fibs[len/2 + j] = hold[len/2 + j] + hold[len/2 + 1 + j];
                
            }
            printf("FIB (%d): ",i);PP(fibs, len);
        }
        
       
        
    }
    

  } else {//odd
  
    

      for(int i = 0; i < len - 2; i++){
        
        if(i % 2 == 0){
            
            for(int j = 0; j <= i/2; j++){
                
                fibs[len/2 + j] = hold[len/2 - 1 + j] + hold[len/2 + j];
                fibs[len/2 - j] = hold[len/2 - 1 + j] + hold[len/2 + j];
                
            }
            ////printf
                printf("HOLD(%d): ",i);for(int k = 0; k < len+1; k++){ printf("%d ", hold[k]);} printf("\n");
                ////
        } else {
        
            for(int j = 0; j <= i/2; j++){
                hold[len/2 - 1 - j] = fibs[len/2 + j] + fibs[len/2 + 1 + j];
                hold[len/2 + j] = fibs[len/2 + j] + fibs[len/2 + 1 + j];
                
            }
            printf("FIB (%d): ",i);PP(fibs, len);
        }
        
       
        
    }
 
  }
  
}


int main()
{
    int n = 9;
    int *fibs = (int*)malloc((n) * sizeof(int));
    fib(fibs, n);

    PP(fibs, n);
    return 0;
}
