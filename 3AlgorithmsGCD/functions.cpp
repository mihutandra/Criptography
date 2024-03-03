#include <iostream>
#include <string>
#include <map>
#include <cmath>
using namespace std;

// Function to find the prime factors of a number and their powers
map<long long, int> primeFactorization(string numStr) {
    long long myNumber = stoll(numStr); //string to long long
    map<long long, int> factors;

    for (long long i = 2; i * i <= myNumber; i++) {
        while (myNumber % i == 0) { //if i is divisor of the nr
            factors[i]++; //factor of i is growing
            myNumber /= i;
        }
    }

    if (myNumber > 1) {
        factors[myNumber]++;
    }

    return factors;
}

// Function to compute the GCD using common prime factors with smallest powers
// non-zero integers between -2147483648 and 2147483647
long long computeGCD(map<long long, int> factors1, map<long long, int> factors2) {
    long long actualgcd = 1;

    for (auto& factor : factors1) {
        if (factors2.count(factor.first)) {
            int commonPower = min(factor.second, factors2[factor.first]); //minimum of common powrs
            actualgcd *= static_cast<long long>(pow(factor.first, commonPower)); //result increaseas by factor at the minimum power
        }
    }

    return actualgcd;
}

/// 1 - Euclidean Algorithm
int euclideanGCD(int a, int b) {
    if(a==0 || b==0){
        return 0;
    }
    while (b != 0) {
        int aux = b;
        b = a % b; // b becomes the remainder
        a = aux;
    }
    return a;
}


/// 2 - Stein Algorithm
/*highly efficient way to compute the GCD by quickly reducing the numbers to smaller values with common factors of 2
 * and then directly calculating the GCD from the odd values. This makes it particularly useful when working
 * with large integers where the repeated division operations of the Euclidean algorithm can be time-consuming.*/
int steinGCD(int a, int b) {
    if (a == 0) return 0;
    if (b == 0) return 0;

    int k;/* finding k, where k is the greatest power of 2
      that divides both a and b. */
    for (k = 0; (a % 2 == 0) && (b % 2 == 0); ++k) {
        a = a/2;
        b = b/2;
    }

    /* dividing a by 2 until a becomes odd */
    while (a % 2 == 0)
        a = a / 2;

    do {
        /* while b is even, remove all factor of 2 in b */
        while (b % 2 == 0)
            b = b / 2;

        /* now a and b are both odd.
          Swap if necessary so a <= b,
          then set b = b - a (which is even).*/
        if (a > b) {
            int aux = a;
            a = b;
            b = aux;
        }

        b = (b - a); //result in an even number since one of them is odd and the other is even.
    } while (b != 0); // if b is zero then a is the GCD

    /* restore common factors of 2 */
    return a * static_cast<int>(std::pow(2, k));
}

/// 3 - Big Integers Algorithm
long long longlongGCD(string numStr1, string numStr2) {
    map<long long, int> factors1 = primeFactorization(numStr1);
    map<long long, int> factors2 = primeFactorization(numStr2);

    return computeGCD(factors1, factors2);
}


