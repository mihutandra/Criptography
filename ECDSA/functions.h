#ifndef ECDSA_FUNCTIONS_H
#define ECDSA_FUNCTIONS_H

#include <cstdint>
#include <string>

struct Curve {
    std::int64_t p;
    std::int64_t a;
    std::int64_t b;
};

struct Point {
    std::int64_t x;
    std::int64_t y;
    bool infinity;
};

struct KeyPair {
    std::int64_t private_key;
    Point public_key;
};

struct Signature {
    std::int64_t r;
    std::int64_t s;
};
/* 
    STEPS OF ECDSA:
        1. Key Generation
        2. Signing
        3. Verification 
*/

// ECDSA function declarations

std::int64_t mod(std::int64_t value, std::int64_t modulus);                                 // Modulo operation ensuring non-negative result
std::int64_t mod_inverse(std::int64_t value, std::int64_t modulus);                         // Modular inverse using Extended Euclidean Algorithm
std::int64_t hash_message(const std::string &message, std::int64_t modulus);                // Simple hash function for messages

Point point_add(const Curve &curve, const Point &p1, const Point &p2);                      // Point addition on elliptic curve
Point scalar_multiply(const Curve &curve, const Point &point, std::int64_t scalar);         // Scalar multiplication on elliptic curve

KeyPair generate_keypair(const Curve &curve, const Point &generator, std::int64_t order);   // Generate ECDSA key pair
Signature sign_message(const Curve &curve, const Point &generator, std::int64_t order,
                       std::int64_t private_key, const std::string &message);               // Sign a message 
bool verify_signature(const Curve &curve, const Point &generator, std::int64_t order, 
                      const Point &public_key, const std::string &message,
                      const Signature &signature);                                          // Verify a message signature 
Signature sign_hash(const Curve &curve, const Point &generator, std::int64_t order,
                    std::int64_t private_key, std::int64_t hash);                           // Sign a hash value
bool verify_hash(const Curve &curve, const Point &generator, std::int64_t order,
                 const Point &public_key, std::int64_t hash,
                 const Signature &signature);                                               // Verify a hash signature

#endif
