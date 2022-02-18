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

Dual fd(Dual a){
    //return dual_sin(dual_mult(a, a));
    return dual_mult((Dual){20,1}, dual_sin(dual_mult((Dual){.02,1}, a)));
}

double first_derivative(Dual (*f)(Dual), double x){
    return (*f)((Dual){x,1}).dual;
}

double higher_derivative(Dual (*f)(Dual), double x, int n) {
    
    double h = .00001;
    
   return  ((*f)((Dual){x + h,1}).real - n*((*f)((Dual){x,1}).real) + (*f)((Dual){x-h,1}).real)/powf(h,n);
    
    
}

//pass function pointer
double taylor(double a, double x, int iteration, Dual (*f)(Dual)){
    double y = 0;
    long long int unsigned  factorial = 1;
    for(int i = 1; i < iteration; i++){
        double derivative = higher_derivative(f,a,i);//(*f)((Dual){a,1}).dual;
        //^You are not taking higher order derivates!!
        y += (derivative / factorial) * powf(x - a, i-1);
        
        printf("::: %f\n", derivative);
        factorial *= i;
    }
    
    return y;
}

int main()
{
 



    InitWindow(SW, SH, "Taylor Series Sim | John Lins");

    double num_of_it = 1;

    SetTargetFPS(60);              
    while (!WindowShouldClose())    
    {
      
        BeginDrawing();

            ClearBackground(RAYWHITE);
            
            DrawLine(SW/2, 0, SW/2, SH, BLACK);
            DrawLine(0, SH/2, SW, SH/2, BLACK);

            for(int i = -SW/2; i < SW/2; i++){
                DrawCircle(i + SW/2, fd((Dual){i,1}).real + SH/2, 2, BLUE);
                DrawCircle(i + SW/2, taylor(0, i, (int)num_of_it, &fd) + SH/2, 2, RED);
                //printf("::: %f", taylor(0, i, (int)num_of_it));
            }//fd((Dual){i/SW * STEP, 1}).real
            
            DrawText(TextFormat("%d", (int)num_of_it), 20, 20, 15, BLACK);
            
            num_of_it += .1;

        EndDrawing();
       
    }

 
    CloseWindow();     

  return 0;
}