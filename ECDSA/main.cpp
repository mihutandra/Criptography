#include "functions.h"

#include <fstream>
#include <iostream>
#include <iterator>
#include <string>

namespace {
const char *kContractPath = "contract.txt";
const char *kOriginalText = "I, Bob, owe Alice $100. This is the original contract.";
const char *kTamperedText = "I, Bob, owe Alice $1000. This is not the original contract.";

void print_error(const std::string &message) {
    std::cout << "\033[91m" << message << "\033[0m" << '\n';
}

bool write_text_file(const std::string &path, const std::string &text) {
    std::ofstream out(path, std::ios::binary);
    if (!out) {
        return false;
    }
    out << text;
    return static_cast<bool>(out);
}

bool read_file(const std::string &path, std::string &data) {
    std::ifstream in(path, std::ios::binary);
    if (!in) {
        return false;
    }
    data.assign(std::istreambuf_iterator<char>(in), std::istreambuf_iterator<char>());
    return true;
}

std::int64_t hash_file(const std::string &path, std::int64_t modulus) {
    std::string data;
    if (!read_file(path, data)) {
        throw std::runtime_error("Unable to read file");
    }
    return hash_message(data, modulus);
}

Signature sign_file(const Curve &curve, const Point &generator, std::int64_t order,
                    std::int64_t private_key, const std::string &path) {
    std::int64_t digest = hash_file(path, order);
    return sign_hash(curve, generator, order, private_key, digest);
}

bool verify_file(const Curve &curve, const Point &generator, std::int64_t order,
                 const Point &public_key, const std::string &path, const Signature &signature) {
    std::int64_t digest = hash_file(path, order);
    return verify_hash(curve, generator, order, public_key, digest, signature);
}
} // namespace

int main() {
    Curve curve{17, 2, 2};
    Point generator{5, 1, false};
    std::int64_t order = 19;

    std::cout << "[+] Creating contract file...." << '\n' << '\n';
    if (!write_text_file(kContractPath, kOriginalText)) {
        print_error("[!] ERROR: Failed to create contract file.");
        return 1;
    }

    std::cout
        << "Here we have a standard contract. Alice wants to ensure Bob doesn't change it later, so she needs our help. "
        << "I am acting as the Digital Notary. I am generating a Private/Public key pair." << '\n';

    KeyPair keys = generate_keypair(curve, generator, order);

    Signature signature = sign_file(curve, generator, order, keys.private_key, kContractPath);
    std::cout << "[+] Document signed successfully. Signature: (" << signature.r << ", "
              << signature.s << ")" << '\n' << '\n';
    std::cout
        << "I have hashed this document and signed it with my Private Key. "
        << "This signature acts like a wax seal. It is mathematically unique to this exact version "
        << "of the file." << '\n' << '\n';

    std::cout
        << "Now, let's pretend I am a hacker. I gain access to the file and secretly add a zero "
        << "to the debt. To the naked eye, it looks like a valid text file." << '\n'  << '\n';
    if (!write_text_file(kContractPath, kTamperedText)) {
        print_error("[!] ERROR: Failed to tamper with contract file.");
        return 1;
    }

    if (verify_file(curve, generator, order, keys.public_key, kContractPath, signature)) {
        std::cout << "[+] SUCCESS: Document is authentic." << '\n';
    } else {
        print_error("[!] ERROR: INVALID SIGNATURE! FILE TAMPERED.");
    }

    std::cout
        << "If we revert the change, the math aligns again. "
        << "This proves that with ECC, you can trust data even if you don't trust the network it "
        << "traveled on." << '\n'  << '\n';
    if (!write_text_file(kContractPath, kOriginalText)) {
        print_error("[!] ERROR: Failed to restore contract file.");
        return 1;
    }

    if (verify_file(curve, generator, order, keys.public_key, kContractPath, signature)) {
        std::cout << "[+] SUCCESS: Document is authentic." << '\n'  << '\n';
    } else {
        print_error("[!] ERROR: INVALID SIGNATURE! FILE TAMPERED.");
    }

    return 0;
}
