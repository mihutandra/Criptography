#include<iostream>
#include<cstdlib>
#include<vector>
#include<map>
#include<set>
#include<string>
#include<algorithm>
#include<cmath>


using namespace std;

int generatePublicKey() {
    return rand() % 28;
}

int gcd(int a, int b)
{
    int t;
    while (1)
    {
        t = a % b;
        if (t == 0)
            return b;
        a = b;
        b = t;
    }
}

int calculate_n(int p, int q) {
    return p * q;
}

int calculate_phi(int p, int q) {
    return  (p - 1) * (q - 1);
}

bool isPrime(int x) {
    if (x < 2)
        return false;
    if (x % 2 == 0 && x != 2)
        return false;
    for (int d = 3; d * d <= x; d+=2)
        if (x % d == 0)
            return false;
    return true;
}

vector<string> splitString(const string& inputString, int substringLength) {
    vector<string> substrings;

    for (size_t i = 0; i < inputString.length(); i += substringLength) {
        string substring = inputString.substr(i, substringLength);
        substrings.push_back(substring);
    }

    return substrings;
}

map<char, int> createLetterToNumberMap() {
    map<char, int> letterToNumberMap;

    const string letters = "_abcdefghijklmnopqrstuvwxyz";
    for (int i = 0; i < letters.length(); ++i) {
        letterToNumberMap[letters[i]] = i;
    }

    return letterToNumberMap;
}

int calculateNrEquiv(string cuv) {
    map<char, int> letterToNumberMap = createLetterToNumberMap();
    return letterToNumberMap[cuv[0]] * 27 + letterToNumberMap[cuv[1]];
}

// transform letter groups to numbers
vector<int> createAllNrVals(string initialWord, int substringLength) {
    vector<int> rez;
    vector<string> splitedWord = splitString(initialWord, substringLength);

    for (auto group : splitedWord)
        rez.push_back(calculateNrEquiv(group));

    return rez;
}

vector<int> allModExp(int n, string initialWord, int substringLength, int e) {
    vector<int> bases = createAllNrVals(initialWord, substringLength);
    vector<int> results;

    for (int i = 0; i < bases.size(); i++) {

        int base = bases[i];
        int result = 1;
        int exp = e;
        while (exp > 0) {
            if (exp % 2 == 1)
            {
                result = (result * base) % n;
            }

            exp = exp >> 1;  // equivalent to exponent /= 2
            base = (base * base) % n;

        }
        results.push_back(result);
    }
    return results;
}

//retuen the litteral equivalent of a number
string transformToString(int nr) {
    map<char, int> letterToNumberMap = createLetterToNumberMap();
    vector<int> nrRez;
    vector<char> temp;
    for (int firstNr = 0; firstNr < 27; firstNr++) {
        for (int secondNr = 0; secondNr < 27; secondNr++) {
            for (int thirdNr = 0; thirdNr < 27; thirdNr++) {
                if ((firstNr * 27 * 27 + secondNr * 27 + thirdNr) == nr)
                {
                    nrRez.push_back(firstNr);
                    nrRez.push_back(secondNr);
                    nrRez.push_back(thirdNr);
                }
            }
        }
    }

    for (int value = 0; value < 3; value++)
    {
        for (auto& entry : letterToNumberMap) {
            if (entry.second == nrRez[value]) {
                temp.push_back(entry.first);
            }
        }
    }
    string result(temp.begin(), temp.end());
    return result;
}

vector<string> getEncryptedText(int n, string initialWord, int substringLength, int e) {
    vector<int> expRezults = allModExp(n, initialWord, substringLength, e);
    vector<string> rez;

    for (auto value : expRezults) {
        rez.push_back(transformToString(value));
    }
    return rez;
}

int generateE(int p, int q) {
    int phi = calculate_phi(p, q);
    int e = 3;
    while (e < phi) {
        // e must be co-prime to phi and
        // smaller than phi.
        if (gcd(e, phi) == 1 && isPrime(e))
            break;
        else
            e += 2;
    }
    return e;
}

// --------------------------------- DECRIPTION ---------------------------------
int generatePrivateKey(int e, int phi) {
    int d = 1;

    while ((d * e) % phi != 1) {
        d++;
    }

    return d;
}

int calculateNrEquiv_2(string cuv) {
    map<char, int> letterToNumberMap = createLetterToNumberMap();
    return letterToNumberMap[cuv[0]] * 27*27 + letterToNumberMap[cuv[1]] * 27 + letterToNumberMap[cuv[2]];
}

// transform letter groups to numbers
vector<int> createAllNrVals_2(string initialWord, int substringLength) {
    vector<int> rez;
    vector<string> splitedWord = splitString(initialWord, substringLength);

    for (auto group : splitedWord)
        rez.push_back(calculateNrEquiv_2(group));

    return rez;
}

vector<int> allModExp_2(int n, string initialWord, int substringLength, int e) {
    vector<int> bases = createAllNrVals_2(initialWord, substringLength);
    vector<int> results;

    for (int i = 0; i < bases.size(); i++) {

        int base = bases[i];
        int result = 1;
        int exp = e;
        while (exp > 0) {
            if (exp % 2 == 1)
            {
                result = (result * base) % n;
            }

            exp = exp >> 1;  // equivalent to exponent /= 2
            base = (base * base) % n;

        }
        results.push_back(result);
    }
    return results;
}

string transformToString_2(int nr) {
    map<char, int> letterToNumberMap = createLetterToNumberMap();
    vector<int> nrRez;
    vector<char> temp;

    for (int secondNr = 0; secondNr < 27; secondNr++) {
        for (int thirdNr = 0; thirdNr < 27; thirdNr++) {
            if ((secondNr * 27 + thirdNr) == nr)
            {
                nrRez.push_back(secondNr);
                nrRez.push_back(thirdNr);
            }
        }
    }

    for (int value = 0; value < 2; value++)
    {
        for (auto& entry : letterToNumberMap) {
            if (entry.second == nrRez[value]) {
                temp.push_back(entry.first);
            }
        }
    }
    string result(temp.begin(), temp.end());
    return result;
}

vector<string> getDecryptedText(int n, string initialWord, int substringLength, int d) {
    vector<int> expRezults = allModExp_2(n, initialWord, substringLength, d);
    vector<string> rez;

    for (auto value : expRezults) {
        rez.push_back(transformToString_2(value));
    }
    return rez;
}
