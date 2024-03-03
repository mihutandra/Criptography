
#include <vector>
using namespace std;

/*calculates the extended greatest common divisor (GCD) of two integers, a and b,
 * while also finding the coefficients x and y that satisfy Bézout's identity.
 * This function uses a recursive approach to find the GCD and its associated coefficients.
*/
long long extendedGCD(long long a, long long b, long long &x, long long &y);

/*designed to solve a linear congruence equation of the form "ax ≡ b (mod m)," where a, b, and m
 * are given integers, and x is the unknown variable we want to find. This function checks whether
 * a solution exists for the congruence and, if so, calculates the value of x
*/
bool solveCongruence(long long a, long long b, long long m, long long &x);

/*designed to solve a system of linear congruence equations, where each equation
 * has the form "x ≡ b (mod a)." The function takes two vectors, a and b, as input,
 * where a contains the moduli, and b contains the remainders. The goal is to find
 * a single value of x that simultaneously satisfies all the congruence equations in the system.
*/
long long solveSystemOfCongruences(const vector<long long> &a, const vector<long long> &b);
