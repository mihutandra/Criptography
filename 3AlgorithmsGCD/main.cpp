#include <iostream>
#include <time.h>
#include <math.h>
#include <iomanip> // for std::setprecision
#include "functions.cpp"
#define NTRIALS 50000 /// we try 50000 cases


void testerINT(int (*func)(int, int)) { /// tester for the 2 INT functions
    int nr1 = 30;
    int nr2 = 12;
    int i;
    unsigned long accum = 0;
    for (i = 0; i < NTRIALS; i++) {
        accum += (*func)(nr1, nr2);
        nr1 = (nr1 + 1) % 5;
        nr2 = (nr2 + 7) % 25;
    }


}
void testerLONG(long long (*func)(string, string)) { /// tester for LONG LONG function
    string numStr1 = "30";
    string numStr2 = "12";
    unsigned long long accum = 0;
    for (long long i = 0; i < NTRIALS; i++) {
        accum += (*func)(numStr1, numStr2);
        numStr1 = to_string((stoll(numStr1) + 1LL) % 5);  // Use 'LL' to ensure it's a long long
        numStr2 = to_string((stoll(numStr2) + 7LL) % 25);  // Use 'LL' to ensure it's a long long
    }

}

    int main() {
            clock_t begin;
            clock_t end;
            double time_spent;
            std::cout<<std::endl;
// euclidean
            begin = clock();
            testerINT(euclideanGCD);
            end = clock();
            time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
            cout << "EUCLIDEAN: Time: " << std::fixed << std::setprecision(9)
                 << time_spent << " nanoseconds  " << std::fixed << std::setprecision(10)<<std::endl<<std::endl;

// stein
            begin = clock();
            testerINT(steinGCD);
            end = clock();
            time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
            cout << "STEIN: Time: " << std::fixed << std::setprecision(9)
                 << time_spent << " nanoseconds  " << std::fixed << std::setprecision(10)<<std::endl<<std::endl;

// long long numbers
            begin = clock();
            testerLONG(longlongGCD);
            end = clock();
            time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
            cout << "LONG LONG: Time: " << std::fixed << std::setprecision(9)
                 << time_spent << " nanoseconds  " << std::fixed << std::setprecision(10)<<std::endl;



        /* string numStr1 = "1234567890";  //
        string numStr2 = "39832128";  // Replace with your second number as a string

        map<long long, int> factors1 = primeFactorization(numStr1);
        map<long long, int> factors2 = primeFactorization(numStr2);

        long long gcd = computeGCD(factors1, factors2);

        cout << "GCD of " << numStr1 << " and " << numStr2 << " is: " << gcd << endl;*/

        return 0;
    }


