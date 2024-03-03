#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <vector>
#include <string>
#include <map>

    int gcd(int a, int b);
    int generatePublicKey();
    int generatePrivateKey(int e, int phi);
    int calculate_n(int p, int q);
    int calculate_phi(int p, int q);

    bool isPrime(int x);

    //CRONOLOGICAL STEPS

    // ENCRYPTION
    std::vector<std::string> splitString(const std::string& inputString, int substringLength); // split into groups of N letters
    std::map<char, int> createLetterToNumberMap(); // create map with A-Z letters and their values

    int calculateNrEquiv(std::string cuv); // numerical equivalent of a group of N letters
    std::vector<int> createAllNrVals(std::string initialWord, int substringLength); // all numerical equivalents as a vector
    std::vector<int> allModExp(int n, std::string initialWord, int substringLength, int e); // compute (nr_equivalent)^e
    std::string transformToString(int nr); //write literal equivalents
    std::vector<std::string> getEncryptedText( int n, std::string initialWord, int substringLength, int e); // get the encrypted text
    int generateE(int p, int q); // generate e

    //DECREPTION
    int calculateNrEquiv_2(std::string cuv);
    std::vector<int> createAllNrVals_2(std::string initialWord, int substringLength);
    std::vector<int> allModExp_2(int n, std::string initialWord, int substringLength, int e); // compute (nr_equivalent)^d
    std::string transformToString_2(int nr);
    std::vector<std::string> getDecryptedText(int n, std::string initialWord, int substringLength, int d);

#endif
