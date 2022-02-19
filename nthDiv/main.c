#include <stdio.h>
#include <math.h>
#include <stdlib.h> 
#include "raylib.h"

//Hackathon: https://ypstemhackathon2022.devpost.com/?ref_feature=challenge&ref_medium=discover

#define SW 1000
#define SH 800
#define e 2.71828

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
        } else {
        
            for(int j = 0; j <= i/2; j++){
                fibs[len/2 - 1 - j] = hold[len/2 + j] + hold[len/2 + 1 + j];
                fibs[len/2 + j] = hold[len/2 + j] + hold[len/2 + 1 + j];
                
            }
        }   
    }
    
  } else {//odd
  
      for(int i = 0; i < len - 2; i++){
        
        if(i % 2 == 0){
            
            for(int j = 0; j <= i/2; j++){
                
                fibs[len/2 + j] = hold[len/2 - 1 + j] + hold[len/2 + j];
                fibs[len/2 - j] = hold[len/2 - 1 + j] + hold[len/2 + j];
                
            }
        } else {
        
            for(int j = 0; j <= i/2; j++){
                hold[len/2 - 1 - j] = fibs[len/2 + j] + fibs[len/2 + 1 + j];
                hold[len/2 + j] = fibs[len/2 + j] + fibs[len/2 + 1 + j];
                
            }
        }
    }
  }
}

double higher(double (*f)(double), double x, double n){
  const long double h = .00001;

  int *fibs = (int*)malloc((n + 1) * sizeof(int));
  fib(fibs, n+1);

  double numer = 0;

  for(int i = 0; i <= n; i++){
    numer += pow(-1, i) * fibs[i] * (*f)(x + (n-i)*h);

  }

  return numer / (pow(h, n));
}


double taylor(double a, double x, int iteration, double (*f)(double)){
    double y = 0;
    long long int unsigned  factorial = 1;
    for(int i = 1; i < iteration; i++){
        double derivative = higher(f,a,i);
        y += (derivative / factorial) * powf(x - a, i-1);
        
        factorial *= i;
    }
    
    return y;
}


double f1(double x) {return 70/tan(x/70);}
double f4(double x) {return e*e*cos(x/20);}
double f3(double x) {return sinh(x/50);}
double f2(double x) {return 30*powf(e, cos(x/30));}



int main()
{
 
    InitWindow(SW, SH, "Higher-Order Derivative Sim | John Lins");
    
    double (*funcs[3])(double x) = {&f1, &f2, &f3};

   double num_of_it = 1;
   int index_of_func = 0;

    SetTargetFPS(60);              
    while (!WindowShouldClose())    
    {
      
        BeginDrawing();

            ClearBackground(RAYWHITE);
            
            DrawLine(SW/2, 0, SW/2, SH, BLACK);
            DrawLine(0, SH/2, SW, SH/2, BLACK);

            for(int i = -SW/2; i < SW/2; i++){
                DrawCircle(i + SW/2, (*funcs[index_of_func])(i)+ SH/2, 2, GREEN);
                
                for(int j = 1; j < (int)num_of_it; j++){
                    DrawCircle(i + SW/2, 10*higher(funcs[index_of_func], i, j) + SH/2, 2, (Color){0, 0, 250 - (50*j), 250 - (10*j)});
                }
                
            }
            
           DrawText(TextFormat("nth (n = %d) derivative of f(x)", (int)num_of_it), 20, 20, 25, BLACK);
           DrawText("y", SW/2 + 5, 5, 20, BLACK);
           DrawText("x", SW - 15, SH/2 + 5, 20, BLACK);
            
          num_of_it += .02;
            
            if(num_of_it > 5){ index_of_func ++; num_of_it = 0;}
            if(index_of_func > 3){CloseWindow(); return 0;}
            
            
            

        EndDrawing();
       
    }

 
    CloseWindow();   

  return 0;
}