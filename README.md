# Criptography
Criptography - University Projects (mathematical approaches implemented)

## Modules
- Algorithms for GCD.
- RSA 
- Systems of congruences.
- ECDSA 

# ECC Digital Notary System

A lightweight, standalone C++ implementation of the **Elliptic Curve Digital Signature Algorithm (ECDSA)**. This application demonstrates how cryptographic signatures can be used to verify the authenticity of documents and detect tampering.

## 📌 Overview

This project implements a custom Elliptic Curve Cryptography (ECC) engine from scratch, without relying on external cryptographic libraries like OpenSSL. It serves as a practical demonstration of:
* **Finite Field Arithmetic** (Modulo operations, Extended Euclidean Algorithm).
* **Elliptic Curve Operations** (Point Addition, Point Doubling, Scalar Multiplication).
* **ECDSA Protocol** (Key Generation, Signing, and Verifying).

The application simulates a **Digital Notary**:
1.  **Sign:** A user signs a contract with their Private Key.
2.  **Tamper:** A simulated hacker alters the file content.
3.  **Verify:** The system mathematically detects the fraud because the signature no longer matches the file hash.

# Elliptic Curve Digital Signature Algorithm (ECDSA)

This document outlines the core steps of the ECDSA algorithm, including Key Generation, Signing, and Verification.

## 1. Key Generation
The first step is to establish the identity of the user.

* **Create Private Key ($d$):** Pick a random number between $1$ and the curve order $n$.
* **Derive Public Key ($Q$):** Multiply the Generator point ($G$) by the private key:
    $$Q = d \cdot G$$

## 2. Signing (The Sender)
The sender creates a digital signature to prove authenticity.

* **Hash:** Convert the message into a number (fingerprint).
* **Nonce ($k$):** Pick a random "ephemeral" number $k$.
* **Calculate $r$:** Compute a random point $R = k \cdot G$ and take its x-coordinate ($r$).
* **Calculate $s$:** Solve the signature equation:
    $$s = k^{-1} (hash + d \cdot r) \pmod n$$

## 3. Verification (The Receiver)
The receiver validates the signature using the sender's public key.

* **Invert:** Calculate the modular inverse of $s$:
    $$w = s^{-1}$$
* **Recover Point:** Compute a check point $P$:
    $$P = (hash \cdot w \cdot G) + (r \cdot w \cdot Q)$$
* **Match:** If the x-coordinate of $P$ equals $r$, the signature is valid.

## Getting Started

### Prerequisites
* A C++ Compiler (GCC/G++ or Clang) supporting C++11 or later.

### Compilation
Since the project is self-contained with no external dependencies, you can compile it using a single command:

```bash
g++ -o digital_notary main.cpp functions.cpp -std=c++11