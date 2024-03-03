#include <vector>
#include <iostream>
#include <numeric>
#include "functions.h"
using namespace std;

long long customGCD(long long a, long long b) {
    while (b != 0) {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Extended Euclidean Algorithm to find the modular multiplicative inverse
long long extendedGCD(long long a, long long b, long long &x, long long &y) {
    if (a == 0) {
        x = 0;
        y = 1;
        return b; //it means that b is the GCD
    }
    //It calculates the GCD of b % a and a using a recursive call and stores it in gcd
    long long x1, y1;
    long long gcd = extendedGCD(b % a, a, x1, y1);
    //The equations used here are derived from Bézout's identity.
    x = y1 - (b / a) * x1;
    y = x1;

    return gcd;
}
bool areCoprime(const vector<long long>& moduli) {
    int n = moduli.size();
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (customGCD(moduli[i], moduli[j]) != 1) {
                return false;
            }
        }
    }
    return true;
}

// Solve a single congruence equation a * x ≡ b (mod m)
bool solveCongruence(long long a, long long b, long long m, long long &x) {

    long long x1, y1;
    long long g = extendedGCD(a, m, x1, y1);

    if (b % g != 0) {
        return false; // No solution exists
    }
    //value of x using the coefficients and the modular arithmetic formula. This formula ensures that the solution is within the range [0, m).
    x = (x1 * (b / g) % (m / g) + (m / g)) % (m / g);

    return true;
}

// Solve a system of congruences using the Chinese Remainder Theorem
/*The Chinese remainder theorem is a theorem which gives a unique solution to simultaneous linear congruences with
 * coprime moduli. In its basic form, the Chinese remainder theorem will determine a number
 * p that, when divided by some given divisors, leaves given remainders.
*/
long long solveSystemOfCongruences(const vector<long long> &a, const vector<long long> &b) {
    if (a.size() != b.size() || !areCoprime(b)) {
        return -1; // Invalid input
    }

    unsigned long n = a.size();
    long long M = 1; //M is the least common multiple (LCM) of the moduli and will be used in the Chinese Remainder Theorem
    for (int i = 0; i < n; i++) {
        M *= a[i];
    }

    long long result = 0;

    for (int i = 0; i < n; i++) { //iterates through each congruence equation in the system.

        long long Mi = M / a[i]; // the product of all the moduli except the current modulus
        long long xi; //solution for the current congruence equation
        solveCongruence(Mi, 1, a[i], xi);
        result += (b[i] * Mi * xi) % M; //partial result
        result %= M; //ensures that the result remains within the range [0, M).

    }

    return result;
}

