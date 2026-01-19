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

## 🚀 Getting Started

### Prerequisites
* A C++ Compiler (GCC/G++ or Clang) supporting C++11 or later.

### Compilation
Since the project is self-contained with no external dependencies, you can compile it using a single command:

```bash
g++ -o digital_notary main.cpp functions.cpp -std=c++11