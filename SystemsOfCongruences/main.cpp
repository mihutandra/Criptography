#include <iostream>
#include "functions.h"

/*A system of congruences, also known as a system of modular equations,
 * is a set of equations that express congruence relationships between
 * an unknown variable (usually denoted as "x") and several moduli.
 * Congruence refers to the idea that two numbers have THE SAME REMAINDER
 * when divided by a common divisor (modulus).*/

//The congruence relation ax ≡ b (mod m) has a solution if the (“unknown”) integers x (where 0 ≤ x ≤ m−1) and k satisfy ax = b+km.
// In other words, you're looking for a value of x such that when you divide it by each mᵢ, it leaves the remainder aᵢ.
int main() {
    /*  x ≡ 3 (mod 2) -> (x and 3 have the same remainder when divided with 2)
        x ≡ 5 (mod 3)
        x ≡ 7 (mod 2)
        -> sol: x ≡ 23 (mod 105)
    */
    vector<long long> a1 = {3, 5, 7};
    vector<long long> b1 = {2, 3, 12};

    long long solution1 = solveSystemOfCongruences(a1, b1);

    if (solution1 != -1) {
        cout << "The solution to the system of congruences is x ≡ " << solution1 << " (mod " << b1[0] * b1[1] * b1[2] << ")" << endl;
    } else {
        cout << "No solution exists for the system of congruences because the moduli are not coprime." << endl;
    }

    /*  x ≡ 2 (mod 3)
        x ≡ 3 (mod 7)
        x ≡ 5 (mod 11)
        -> sol: x ≡ 1 (mod 30)
    */
    vector<long long> a2 = {2, 3, 5};
    vector<long long> b2 = {3, 7, 11};

    long long solution2 = solveSystemOfCongruences(a2, b2);

    if (solution2 != -1) {
        cout << "The solution to the system of congruences is x ≡ " << solution2 << " (mod " << b2[0] * b2[1] * b2[2] << ")" << endl;
    } else {
        cout << "No solution exists for the system of congruences." << endl;
    }

    /*  x ≡ 3 (mod 7)
        x ≡ 4 (mod 11)
        x ≡ 1 (mod 13)
        -> sol: x ≡ 7 (mod 12)
    */
    vector<long long> a3 = {3, 4, 1};
    vector<long long> b3 = {7, 11, 13};

    long long solution3 = solveSystemOfCongruences(a3, b3);

    if (solution3 != -1) {
        cout << "The solution to the system of congruences is x ≡ " << solution3 << " (mod " << b3[0] * b3[1] * b3[2] << ")" << endl;
    } else {
        cout << "No solution exists for the system of congruences." << endl;
    }

    return 0;
}
