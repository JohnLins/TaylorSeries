#include <math.h>
#include <stdlib.h>
#pragma once

void fib(int * fibs, int len) {

    //init
    int hold[len + 1];
    for (int i = 0; i < len; i++) {
        fibs[i] = 1;
        hold[i] = 1;
    }
    
    hold[len] = 1;

        for (int i = 0; i < len - 2; i++) {
            
            if (i % 2 == 0) {

                for (int j = 0; j <= i / 2; j++) {
                    if (len % 2 == 0) { //even
                        hold[len / 2 + j] = fibs[len / 2 - 1 + j] + fibs[len / 2 + j];
                        hold[len / 2 - j] = fibs[len / 2 - 1 + j] + fibs[len / 2 + j];
                    } else {//odd
                        fibs[len / 2 + j] = hold[len / 2 - 1 + j] + hold[len / 2 + j];
                        fibs[len / 2 - j] = hold[len / 2 - 1 + j] + hold[len / 2 + j];
                    }

                }
            } else {

                for (int j = 0; j <= i / 2; j++) {
                    if(len % 2 == 0){//even
                        fibs[len / 2 - 1 - j] = hold[len / 2 + j] + hold[len / 2 + 1 + j];
                        fibs[len / 2 + j] = hold[len / 2 + j] + hold[len / 2 + 1 + j];
                    } else {//odd
                        hold[len / 2 - 1 - j] = fibs[len / 2 + j] + fibs[len / 2 + 1 + j];
                        hold[len / 2 + j] = fibs[len / 2 + j] + fibs[len / 2 + 1 + j];
                    }

                }
            }
    }
}