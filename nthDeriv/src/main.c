#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "raylib.h"
#include "../../fib/fib.c"


#define SW 1000
#define SH 800
#define e 2.71828



double higher(double( * f)(double), double x, double n) {
    const long double h = .00001;

    int * fibs = (int * ) malloc((n + 1) * sizeof(int));
    fib(fibs, n + 1);

    double numer = 0;

    for (int i = 0; i <= n; i++) {
        numer += pow(-1, i) * fibs[i] * ( * f)(x + (n - i) * h);

    }

    return numer / (pow(h, n));
}


double taylor(double a, double x, int iteration, double( * f)(double)) {
    double y = 0;
    long long int unsigned factorial = 1;
    for (int i = 1; i < iteration; i++) {
        double derivative = higher(f, a, i);
        y += (derivative / factorial) * powf(x - a, i - 1);

        factorial *= i;
    }

    return y;
}


double f1(double x) {
    return 70 / tan(x / 70);
}
double f4(double x) {
    return e * e * cos(x / 20);
}
double f3(double x) {
    return sinh(x / 50);
}
double f2(double x) {
    return 30 * powf(e, cos(x / 30));
}



int main() {

    InitWindow(SW, SH, "Higher-Order Derivative Sim | John Lins");

    double( * funcs[4])(double x) = {
        & f1,
        & f2,
        & f3,
        & f4
    };

    double num_of_it = 1;
    int index_of_func = 0;

    SetTargetFPS(60);
    while (!WindowShouldClose()) {

        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawLine(SW / 2, 0, SW / 2, SH, BLACK);
        DrawLine(0, SH / 2, SW, SH / 2, BLACK);

        for (int i = -SW / 2; i < SW / 2; i++) {
            DrawCircle(i + SW / 2, ( * funcs[index_of_func])(i) + SH / 2, 2, GREEN);

            for (int j = 1; j < (int) num_of_it; j++) {
                DrawCircle(i + SW / 2, 10 * higher(funcs[index_of_func], i, j) + SH / 2, 2, (Color) {
                    0,
                    0,
                    250 - (50 * j),
                    250 - (10 * j)
                });
            }

        }

        DrawText(TextFormat("nth (n = %d) derivative of f(x)", (int) num_of_it), 20, 20, 25, BLACK);
        DrawText("y", SW / 2 + 5, 5, 20, BLACK);
        DrawText("x", SW - 15, SH / 2 + 5, 20, BLACK);

        num_of_it += .02;

        if (num_of_it > 5) {
            index_of_func++;
            num_of_it = 0;
        }
        if (index_of_func > 4) {
            CloseWindow();
            return 0;
        }




        EndDrawing();

    }


    CloseWindow();

    return 0;
}