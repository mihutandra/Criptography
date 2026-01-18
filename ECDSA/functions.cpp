#include "functions.h"

#include <iostream>
#include <random>
#include <stdexcept>


namespace {
std::int64_t extended_gcd(std::int64_t a, std::int64_t b, std::int64_t &x, std::int64_t &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    std::int64_t x1 = 0;
    std::int64_t y1 = 0;
    std::int64_t gcd = extended_gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return gcd;
}

std::int64_t random_in_range(std::int64_t min_value, std::int64_t max_value) {
    static std::random_device rd;
    static std::mt19937_64 generator(rd());
    std::uniform_int_distribution<std::int64_t> distribution(min_value, max_value);
    return distribution(generator);
}
} // namespace

std::int64_t mod(std::int64_t value, std::int64_t modulus) {
    std::int64_t result = value % modulus;
    if (result < 0) {
        result += modulus;
    }
    return result;
}

std::int64_t mod_inverse(std::int64_t value, std::int64_t modulus) {
    std::int64_t x = 0;
    std::int64_t y = 0;
    std::int64_t gcd = extended_gcd(mod(value, modulus), modulus, x, y);
    if (gcd != 1) {
        throw std::runtime_error("Inverse does not exist");
    }
    return mod(x, modulus);
}

std::int64_t hash_message(const std::string &message, std::int64_t modulus) {
    std::int64_t hash = 0;
    for (unsigned char ch : message) {
        hash = mod(hash * 31 + ch, modulus);
    }
    return hash;
}

Point point_add(const Curve &curve, const Point &p1, const Point &p2) {
    if (p1.infinity) {
        return p2;
    }
    if (p2.infinity) {
        return p1;
    }

    if (p1.x == p2.x && mod(p1.y + p2.y, curve.p) == 0) {
        return {0, 0, true};
    }

    std::int64_t slope = 0;
    if (p1.x == p2.x && p1.y == p2.y) {
        std::int64_t numerator = mod(3 * p1.x * p1.x + curve.a, curve.p);
        std::int64_t denominator = mod_inverse(mod(2 * p1.y, curve.p), curve.p);
        slope = mod(numerator * denominator, curve.p);
    } else {
        std::int64_t numerator = mod(p2.y - p1.y, curve.p);
        std::int64_t denominator = mod_inverse(mod(p2.x - p1.x, curve.p), curve.p);
        slope = mod(numerator * denominator, curve.p);
    }

    std::int64_t x3 = mod(slope * slope - p1.x - p2.x, curve.p);
    std::int64_t y3 = mod(slope * (p1.x - x3) - p1.y, curve.p);
    return {x3, y3, false};
}

Point scalar_multiply(const Curve &curve, const Point &point, std::int64_t scalar) {
    Point result{0, 0, true};
    Point addend = point;
    std::int64_t k = scalar;

    while (k > 0) {
        if (k & 1) {
            result = point_add(curve, result, addend);
        }
        addend = point_add(curve, addend, addend);
        k >>= 1;
    }

    return result;
}

KeyPair generate_keypair(const Curve &curve, const Point &generator, std::int64_t order) {
    std::int64_t private_key = random_in_range(1, order - 1);
    Point public_key = scalar_multiply(curve, generator, private_key);
    return {private_key, public_key};
}

Signature sign_message(const Curve &curve, const Point &generator, std::int64_t order,
                       std::int64_t private_key, const std::string &message) {
    std::int64_t hash = hash_message(message, order);
    return sign_hash(curve, generator, order, private_key, hash);
}

Signature sign_hash(const Curve &curve, const Point &generator, std::int64_t order,
                    std::int64_t private_key, std::int64_t hash) {
    while (true) {
        std::int64_t k = random_in_range(1, order - 1);
        Point point = scalar_multiply(curve, generator, k);
        std::int64_t r = mod(point.x, order);
        if (r == 0) {
            continue;
        }
        std::int64_t k_inverse = mod_inverse(k, order);
        std::int64_t s = mod(k_inverse * (hash + private_key * r), order);
        if (s == 0) {
            continue;
        }
        return {r, s};
    }
}

bool verify_signature(const Curve &curve, const Point &generator, std::int64_t order,
                      const Point &public_key, const std::string &message,
                      const Signature &signature) {
    std::int64_t hash = hash_message(message, order);
    return verify_hash(curve, generator, order, public_key, hash, signature);
}

bool verify_hash(const Curve &curve, const Point &generator, std::int64_t order,
                 const Point &public_key, std::int64_t hash,
                 const Signature &signature) {
    if (signature.r <= 0 || signature.r >= order || signature.s <= 0 || signature.s >= order) {
        return false;
    }

    std::int64_t w = mod_inverse(signature.s, order);
    std::int64_t u1 = mod(hash * w, order);
    std::int64_t u2 = mod(signature.r * w, order);

    Point point = point_add(curve,
                            scalar_multiply(curve, generator, u1),
                            scalar_multiply(curve, public_key, u2));
    if (point.infinity) {
        return false;
    }

    std::int64_t v = mod(point.x, order);
    return v == signature.r;
}
