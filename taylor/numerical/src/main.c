#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "raylib.h"
#include "../../../fib/fib.c"


#define SW 1000
#define SH 800
#define STEP 10
/*
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

*/

double higher(double( * f)(double), double x, double n) {
    const long double h = .0001;

    int * fibs = (int * ) malloc((n + 1) * sizeof(int));
    fib(fibs, n + 1);

    double numer = 0;

    for (int i = 0; i <= n; i++) {
        numer += pow(-1, i) * fibs[i] * ( * f)(x + (n - i) * h);

    }

    return numer / (pow(h, n));
}



//pass function pointer
double taylor(double a, double x, int iteration, double( * f)(double)) {
    double y = 0;
    long long int unsigned factorial = 1;
    for (int i = 1; i < iteration; i++) {
        double derivative = higher(f, a, i - 1);
        double term = (derivative / factorial) * powf(x - a, i - 1);
        y += term;
        factorial *= i;
    }

    return y;
}

double f1(double x) {
    return (1000) / (10 + (x / 10));
}
double f2(double x) {
    return 40 * cos(x / 40);
}
double f3(double x) {
    return sinh(x / 50);
}
double f4(double x) {
    return 50 * tanh(x / 50);
}

int main() {


    InitWindow(SW, SH, "Taylor Series Sim | John Lins");


    double( * funcs[4])(double x) = {
        & f1,
        & f2,
        & f3,
        & f4
    };

    int index_of_func = 0;
    double num_of_it = 1;

    SetTargetFPS(60);
    while (!WindowShouldClose()) {

        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawLine(SW / 2, 0, SW / 2, SH, BLACK);
        DrawLine(0, SH / 2, SW, SH / 2, BLACK);

        for (int i = -SW / 2; i < SW / 2; i++) {
            DrawCircle(i + SW / 2, ( * funcs[index_of_func])(i) + SH / 2, 2, (Color) {
                0,
                0,
                255,
                255
            });
            DrawCircle(i + SW / 2, taylor(30, i, (int) num_of_it, funcs[index_of_func]) + SH / 2, 2, (Color) {
                10,
                200,
                0,
                255
            });

        }

        DrawText(TextFormat("Iteration: %d", (int) num_of_it), 20, 20, 15, BLACK);
        DrawText(TextFormat("a = %d", 30), 20, 50, 15, BLACK);
        DrawText("y", SW / 2 + 5, 5, 20, BLACK);
        DrawText("x", SW - 15, SH / 2 + 5, 20, BLACK);

        num_of_it += .01;



        if (num_of_it > 6) {
            index_of_func++;
            num_of_it = 0;
        }
        if (index_of_func > 3) {
            CloseWindow();
            return 0;
        }

        EndDrawing();

    }


    CloseWindow();

    return 0;
}