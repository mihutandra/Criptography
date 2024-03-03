#include "functions.h"
#include<iostream>
#include<cstdlib>
#include<vector>
#include<map>
#include<set>
#include<string>
#include<algorithm>
#include<cmath>
using namespace std;

bool isValidInitialWord(const string& word) {
    for (char c : word) {
        if (!((c >= 'a' && c <= 'z') || c == '_')) {
            return false;
        }
    }
    return true;
}

int main() {
    cout<<"Give p: "<<endl;
    int p; //31
    cin >> p;
    cout<<"Give q: "<<endl;
    int q; //53
    cin >> q;
    int n = calculate_n(p,q);
    int e = generateE(p,q); // smallest odd prime and co-prime with phi
    int l = 3;
    int k = 2;

    // ENCRYPT
    string initialWord;
    do {
        cout << "Enter the initial word (should contain only small letters and '_'): ";
        cin >> initialWord;
    } while (!isValidInitialWord(initialWord));

    vector<string> encrypted = getEncryptedText(n, initialWord, k, 67);
    cout << "Encrypted: ";
    for (auto val : encrypted)
        cout << val;
    cout << endl;

    // DECRYPT
    do {
        cout << "Enter the initial word (should contain only small letters and '_'): ";
        cin >> initialWord;
    } while (!isValidInitialWord(initialWord));
    int phi = calculate_phi(p, q);
    int d = generatePrivateKey(67, phi);
    initialWord = "ayx_rlagabar";  // Replace with the actual encrypted word
    vector<string> decrypted = getDecryptedText(n, initialWord, l, d);
    cout << "Decrypted: ";
    for (auto val : decrypted)
        cout << val;
    cout << endl;

    return 0;
}