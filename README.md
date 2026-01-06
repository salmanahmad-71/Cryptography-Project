Cryptography Tools Program
Description
A C++ program with 4 encryption methods: Shift, Affine, Vigenere, and RSA ciphers.

Features

  Shift (Caesar) Cipher with file encryption
  Affine Cipher with coprime validation
  Vigenere Cipher with keyword encryption
  RSA encryption/decryption with file support
  Color-coded console interface

Frequency analysis for Shift cipher

How to Run
Clone the repository: git clone https://github.com/yourname/cryptography-tools.git

Compile: g++ main.cpp -o cryptography.exe

Run: ./cryptography.exe

Prerequisites
Windows OS (for Windows.h functions)

C++ compiler (GCC/MinGW recommended)

Usage
Run the program and choose from:

1.Shift Cipher
2.Affine Cipher
3.Vigenere Cipher
4.RSA Cipher
5.Exit

Table of Functions
Cipher Type	Key Functions
Shift Cipher	               encryptTextShift(), decryptTextShift(), analyzeFileFrequency()
Affine Cipher                encryptCharAffine(), decryptCharAffine(), checkCoprime()
Vigenere Cipher	             encryptCharVigenere(), decryptCharVigenere(), generateVigenereKey()
RSA Cipher	                 rsaEncryptFile(), rsaDecryptFile(), generatePrivateKey()
Author
      Salman Ahmad  --  salmanshafiq7171@gmail.com

