#include <stdio.h>
#include <math.h>
#include "raylib.h"

//Hackathon: https://ypstemhackathon2022.devpost.com/?ref_feature=challenge&ref_medium=discover

#define SW 1000
#define SH 800
#define STEP 10

typedef struct Dual {
  double real;
  double dual;
} Dual;


Dual dual_add(Dual a, Dual b){
  return (Dual){a.real + b.real, a.dual + b.dual};
}

Dual dual_mult(Dual a, Dual b){
  return (Dual){ a.real * b.real,
   a.real * b.dual + a.dual * b.real};
}

Dual dual_sin(Dual a){
    return (Dual){sin(a.real), a.dual * cos(a.real)};
}

void print_dual(Dual a){
  printf("%lf + %lf ♤\n", a.real, a.dual);
}

double f(double x){
  return x;
}
//=
Dual fd(Dual a){
    //return dual_sin(dual_mult(a, a));
    return dual_sin(a);
}

//pass function pointer
double taylor(double a, double x, int iteration){
    double y = 0;
    int factorial = 1;
    for(int i = 1; i < iteration; i++){
        
        y += fd((Dual){a,1}).dual / factorial * powf(x - a, i-1);
        
        
        factorial *= i;
    }
    
    return y;
}

int main()
{
 

    for(int i = 0; i < 10; i++){
        printf("Derivative @ x = %d: %lf, Real: %lf\n", i, fd((Dual){i,1}).dual, fd((Dual){i,1}).real);
    }






    InitWindow(SW, SH, "Taylor Series Sim | John Lins");

    double num_of_it = 1;

    SetTargetFPS(60);              
    while (!WindowShouldClose())    
    {
      
        BeginDrawing();

            ClearBackground(RAYWHITE);

            for(int i = -SW/2; i < SW/2; i++){
                DrawCircle(i + SW/2, fd((Dual){i,1}).real + SH/2, 1, BLUE);
                DrawCircle(i + SW/2, taylor(0, i, (int)num_of_it) + SH/2, 1, RED);
            }//fd((Dual){i/SW * STEP, 1}).real
            
            
            
            num_of_it += .01;

        EndDrawing();
       
    }

 
    CloseWindow();     

  return 0;
}