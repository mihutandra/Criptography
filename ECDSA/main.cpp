#include "functions.h"

#include <iostream>
#include <string>

int main() {
    Curve curve{17, 2, 2};
    Point generator{5, 1, false};
    std::int64_t order = 19;

    std::cout << "Toy ECDSA over a small prime field (educational, not secure).\n";
    std::cout << "Curve: y^2 = x^3 + " << curve.a << "x + " << curve.b << " (mod " << curve.p << ")\n";
    std::cout << "Generator: (" << generator.x << ", " << generator.y << ") with order " << order << "\n\n";

    std::cout << "Enter a message to sign: ";
    std::string message;
    std::getline(std::cin, message);

    if (message.empty()) {
        std::cout << "Message was empty. Exiting.\n";
        return 0;
    }

    KeyPair keys = generate_keypair(curve, generator, order);

    std::cout << "Private key: " << keys.private_key << "\n";
    std::cout << "Public key: (" << keys.public_key.x << ", " << keys.public_key.y << ")\n";

    Signature signature = sign_message(curve, generator, order, keys.private_key, message);

    std::cout << "Signature (r, s): (" << signature.r << ", " << signature.s << ")\n";

    bool valid = verify_signature(curve, generator, order, keys.public_key, message, signature);
    std::cout << "Signature verification: " << (valid ? "valid" : "invalid") << "\n";

    return 0;
}
