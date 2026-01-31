#include <stdio.h>

/*
 * C Imperative Paradigm Lab
 * Parts 1–4 are implemented in this file.
 *
 * Do NOT change function signatures.
 * 
 * 1/15/26 - Brian Toone
 */

/* ===== Part 2 ===== */

int sum_to(int n) {
    int sum = 0;
    for(int i=1; i<=(n); i++){ //<- Control
        sum += i; //<- State Change
    }
    return sum;
}

/* ===== Part 3 ===== */

double avg_1_to_n(int n) {
    return (double)sum_to(n) / n;
}

/* ===== Part 4 ===== */
void increment_bad(int x) {
    x++;
}

void increment(int *x) {
    (*x)++;
}

int main() {

    /* ===== Part 1 ===== */

    printf("--- Part 1: State and Sequence ---\n");
    //I think it will result in x=20
    int x = 2;
    x = x * 3;
    x = x + 4;
    printf("x=%d\n", x);
    
    //1.1 The value of x changes each line. The intermediate values don't get to "live" because x changes the next line.
    // TODO: swap the last two assignments above and re-run
    //1.2 The final value of x is 10. Changing the order of the last two assignments changes the final value, much like algebra.

    /* ===== Part 2 ===== */
    
    printf("\n--- Part 2: Control Flow ---\n");
    printf("sum_to(5) = %d (expected 15)\n", sum_to(5));
    printf("sum_to(1) = %d (expected 1)\n", sum_to(1));

    //2.2 The C code has to have the full loop structure built, whereas Python and Java can use built-in functions to achieve the same result with less code.

    /* ===== Part 3 ===== */

    printf("\n--- Part 3: Functions as Procedures ---\n");
    printf("avg_1_to_n(5) = %.1f (expected 3.0)\n", avg_1_to_n(5));
    //3.1 C doesn't really require much more code than Python or Java for this function. The main difference is the need for type declarations in C.

    /* ===== Part 4 ===== */

    printf("\n--- Part 4: Pass-by-Value vs Pointers ---\n");

    int a = 5;
    increment_bad(a);
    printf("after increment_bad: a=%d (expected 5)\n", a);

    increment(&a);
    printf("after increment:     a=%d (expected 6)\n", a);

    return 0;
    // 4.1 In C, arguments are passed by value, so a copy of the variable is made. This causes changes to not affect the original variable.
    // 4.2 A pointer allows multiple parts of your code to read and modify the same memory location. This allows for state sharing across fumction calls.
}
