#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <vector>
#include <windows.h>
#include <conio.h>
using namespace std;

// Function declarations
void changeTextColor(int colorCode);
int getNumberInput();
void clearBuffer();
void showMainTitle(string sectionTitle);
void showCipherTitle(string cipherName, string operation = "");

// Shift cipher functions
char encryptCharShift(char letter, int shift);
string encryptTextShift(const string& text, int shift);
string decryptTextShift(const string& text, int shift);
int findKeyByFrequency(const string& text);
void processShiftFile(bool doEncrypt);
void analyzeFileFrequency();
void shiftCipherMenu();

// Affine cipher functions
bool checkCoprime(int a, int b);
int findInverse(int a, int m);
char encryptCharAffine(char letter, int a, int b);
char decryptCharAffine(char letter, int a, int b);
void affineCipherMenu();

// Vigenere cipher functions
string generateVigenereKey(const string& text, const string& keyword);
char encryptCharVigenere(char textChar, char keyChar);
char decryptCharVigenere(char textChar, char keyChar);
void vigenereCipherMenu();

// RSA cipher functions
bool isPrime(long long num);
long long findGCD(long long a, long long b);
long long modPower(long long base, long long exp, long long mod);
void generatePrivateKey();
void rsaEncryptFile();
void rsaDecryptFile();
void showSampleRSAKeys();
void rsaCipherMenu();

int main() {
    system("title SECURE COMMUNICATION SYSTEM");
    system("mode con: cols=90 lines=35");
    
    int mainChoice;
    bool running = true;
    
    while (running) {
        system("cls");
        showMainTitle("MAIN MENU");
        
        changeTextColor(14);
        cout << "\t\t\t======================================" << endl;
        cout << "\t\t\t        CHOOSE CRYPTOGRAPHY TOOL     " << endl;
        cout << "\t\t\t======================================" << endl << endl;
        
        changeTextColor(11);
        cout << "\t\t1. Shift Cipher (Caesar Cipher)" << endl;
        cout << "\t\t2. Affine Cipher" << endl;
        cout << "\t\t3. Vigenere Cipher" << endl;
        cout << "\t\t4. RSA Cipher (Educational)" << endl;
        cout << "\t\t5. Exit Program" << endl << endl;
        
        changeTextColor(10);
        cout << "\t\tEnter your choice: ";
        changeTextColor(7);
        mainChoice = getNumberInput();
        clearBuffer();
        
        if (mainChoice == 1) shiftCipherMenu();
        else if (mainChoice == 2) affineCipherMenu();
        else if (mainChoice == 3) vigenereCipherMenu();
        else if (mainChoice == 4) rsaCipherMenu();
        else if (mainChoice == 5) {
            changeTextColor(10);
            cout << "\n\tThank you for using Secure Communication System!" << endl;
            cout << "\t\t      Stay secure!" << endl;
            changeTextColor(7);
            Sleep(2000);
            running = false;
        }
        else {
            changeTextColor(12);
            cout << "\n\tPlease choose 1-5." << endl;
            changeTextColor(7);
            Sleep(1000);
        }
    }
    
    return 0;
}

// Color and utility functions
void changeTextColor(int colorCode) {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(consoleHandle, colorCode);
}

int getNumberInput() {
    int userInput;
    while (!(cin >> userInput)) {
        cin.clear();
        cin.ignore(1000, '\n');
        changeTextColor(12);
        cout << "\tPlease enter a valid number: ";
        changeTextColor(7);
    }
    return userInput;
}

void clearBuffer() {
    cin.clear();
    cin.ignore(1000, '\n');
}

// Display functions - Changed header colors
void showMainTitle(string sectionTitle) {
    changeTextColor(3);  // Cyan for main title
    cout << "\n\t\t================================================================" << endl;
    cout << "\t\t        SECURE COMMUNICATION SYSTEM - CRYPTOGRAPHY TOOLS       " << endl;
    cout << "\t\t================================================================" << endl;
    changeTextColor(10);  // Green for section title
    cout << "\t\t\t>> " << sectionTitle << " <<" << endl << endl;
    changeTextColor(7);
}

void showCipherTitle(string cipherName, string operation) {
    system("cls");
    changeTextColor(3);  // Cyan for main title
    cout << "\n\t\t================================================================" << endl;
    cout << "\t\t        SECURE COMMUNICATION SYSTEM - CRYPTOGRAPHY TOOLS       " << endl;
    cout << "\t\t================================================================" << endl;
    changeTextColor(10);  // Green for cipher title
    cout << "\t\t\t>> " << cipherName;
    if (!operation.empty()) cout << " --- " << operation;
    cout << " <<" << endl << endl;
    changeTextColor(7);
}

// Shift cipher implementations with simpler algorithm
char encryptCharShift(char letter, int shift) {
    if (isalpha(letter)) {
        char baseChar = islower(letter) ? 'a' : 'A';
        return (letter - baseChar + shift) % 26 + baseChar;
    }
    return letter;
}

string encryptTextShift(const string& text, int shift) {
    string result = "";
    for (char letter : text) result += encryptCharShift(letter, shift);
    return result;
}

string decryptTextShift(const string& text, int shift) {
    return encryptTextShift(text, 26 - (shift % 26));
}

int findKeyByFrequency(const string& text) {
    vector<int> freqCount(26, 0);
    
    for (char letter : text) {
        if (letter >= 'A' && letter <= 'Z') freqCount[letter - 'A']++;
        else if (letter >= 'a' && letter <= 'z') freqCount[letter - 'a']++;
    }
    
    int maxIndex = 0;
    for (int i = 1; i < 26; i++) {
        if (freqCount[i] > freqCount[maxIndex]) maxIndex = i;
    }
    
    return (maxIndex - ('e' - 'a') + 26) % 26;
}

void processShiftFile(bool doEncrypt) {
    string inputFile, outputFile;
    int shiftValue;
    
    changeTextColor(10);
    cout << "\n\tEnter input filename: ";
    changeTextColor(7);
    getline(cin, inputFile);
    
    changeTextColor(10);
    cout << "\tEnter output filename: ";
    changeTextColor(7);
    getline(cin, outputFile);
    
    changeTextColor(10);
    cout << "\tEnter shift (0-25): ";
    changeTextColor(7);
    shiftValue = getNumberInput();
    clearBuffer();
    
    ifstream inFile(inputFile);
    if (!inFile) {
        changeTextColor(12);
        cout << "\n\tError: Couldn't open the file!" << endl;
        changeTextColor(7);
        cout << "\tPress any key...";
        _getch();
        return;
    }
    
    string content((istreambuf_iterator<char>(inFile)), istreambuf_iterator<char>());
    inFile.close();
    
    string result;
    if (doEncrypt) result = encryptTextShift(content, shiftValue);
    else result = decryptTextShift(content, shiftValue);
    
    ofstream outFile(outputFile);
    outFile << result;
    outFile.close();
    
    changeTextColor(10);
    cout << "\n\tSuccess! File saved as: " << outputFile << endl;
    changeTextColor(7);
    cout << "\tPress any key...";
    _getch();
}

void analyzeFileFrequency() {
    string filename;
    changeTextColor(10);
    cout << "\n\tEnter encrypted filename: ";
    changeTextColor(7);
    getline(cin, filename);
    
    ifstream inFile(filename);
    if (!inFile) {
        changeTextColor(12);
        cout << "\n\tError: Couldn't open the file!" << endl;
        changeTextColor(7);
        cout << "\tPress any key...";
        _getch();
        return;
    }
    
    string content((istreambuf_iterator<char>(inFile)), istreambuf_iterator<char>());
    inFile.close();
    
    int guessedKey = findKeyByFrequency(content);
    string decryptedText = decryptTextShift(content, guessedKey);
    
    changeTextColor(10);
    cout << "\n\tFrequency Analysis Results:" << endl;
    cout << "\t---------------------------" << endl;
    changeTextColor(11);
    cout << "\tMost likely key: " << guessedKey << endl;
    
    changeTextColor(10);
    cout << "\n\tSave decrypted text to file? (y/n): ";
    changeTextColor(7);
    char choice;
    cin >> choice;
    clearBuffer();
    
    if (choice == 'y' || choice == 'Y') {
        string outFile;
        changeTextColor(10);
        cout << "\tEnter output filename: ";
        changeTextColor(7);
        getline(cin, outFile);
        
        ofstream outputFile(outFile);
        outputFile << decryptedText;
        outputFile.close();
        
        changeTextColor(10);
        cout << "\n\tFile saved as: " << outFile << endl;
    }
    
    changeTextColor(7);
    cout << "\n\tPress any key...";
    _getch();
}

void shiftCipherMenu() {
    int choice = 0;
    
    while (choice != 7) {
        showCipherTitle("SHIFT CIPHER (CAESAR CIPHER)");
        changeTextColor(14);
        cout << "\t\t\t======================================" << endl;
        cout << "\t\t\t          SHIFT CIPHER MENU          " << endl;
        cout << "\t\t\t======================================" << endl << endl;
        changeTextColor(11);
        cout << "\t\t1. Encrypt Text" << endl;
        cout << "\t\t2. Decrypt Text" << endl;
        cout << "\t\t3. Guess Key from Text" << endl;
        cout << "\t\t4. Analyze File (Frequency Analysis)" << endl;
        cout << "\t\t5. Encrypt File" << endl;
        cout << "\t\t6. Decrypt File" << endl;
        cout << "\t\t7. Back to Main Menu" << endl << endl;
        changeTextColor(10);
        cout << "\t\tEnter choice: ";
        changeTextColor(7);
        choice = getNumberInput();
        clearBuffer();
        
        if (choice == 1) {
            string text;
            int shift;
            changeTextColor(10);
            cout << "\n\tEnter text: ";
            changeTextColor(7);
            getline(cin, text);
            changeTextColor(10);
            cout << "\tEnter shift (0-25): ";
            changeTextColor(7);
            shift = getNumberInput();
            clearBuffer();
            changeTextColor(10);
            cout << "\n\tEncrypted: ";
            changeTextColor(11);
            cout << encryptTextShift(text, shift) << endl;
            changeTextColor(7);
            cout << "\n\tPress any key...";
            _getch();
        }
        else if (choice == 2) {
            string text;
            int shift;
            changeTextColor(10);
            cout << "\n\tEnter text: ";
            changeTextColor(7);
            getline(cin, text);
            changeTextColor(10);
            cout << "\tEnter shift (0-25): ";
            changeTextColor(7);
            shift = getNumberInput();
            clearBuffer();
            changeTextColor(10);
            cout << "\n\tDecrypted: ";
            changeTextColor(11);
            cout << decryptTextShift(text, shift) << endl;
            changeTextColor(7);
            cout << "\n\tPress any key...";
            _getch();
        }
        else if (choice == 3) {
            string text;
            changeTextColor(10);
            cout << "\n\tEnter encrypted text: ";
            changeTextColor(7);
            getline(cin, text);
            int key = findKeyByFrequency(text);
            changeTextColor(10);
            cout << "\n\tGuessed key: ";
            changeTextColor(11);
            cout << key << endl;
            changeTextColor(10);
            cout << "\tDecrypted: ";
            changeTextColor(11);
            cout << decryptTextShift(text, key) << endl;
            changeTextColor(7);
            cout << "\n\tPress any key...";
            _getch();
        }
        else if (choice == 4) analyzeFileFrequency();
        else if (choice == 5) processShiftFile(true);
        else if (choice == 6) processShiftFile(false);
        else if (choice != 7) {
            changeTextColor(12);
            cout << "\n\tInvalid choice!" << endl;
            changeTextColor(7);
            Sleep(1000);
        }
    }
}

// Affine cipher implementations with simpler algorithm
bool checkCoprime(int a, int b) {
    for (int i = 2; i <= a && i <= b; i++) {
        if (a % i == 0 && b % i == 0) return false;
    }
    return true;
}

int findInverse(int a, int m) {
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) return x;
    }
    return -1;
}

char encryptCharAffine(char letter, int a, int b) {
    if (isalpha(letter)) {
        char base = islower(letter) ? 'a' : 'A';
        int val = letter - base;
        return (a * val + b) % 26 + base;
    }
    return letter;
}

char decryptCharAffine(char letter, int a, int b) {
    if (isalpha(letter)) {
        char base = islower(letter) ? 'a' : 'A';
        int val = letter - base;
        int inv = findInverse(a, 26);
        return (inv * (val - b + 26)) % 26 + base;
    }
    return letter;
}

void affineCipherMenu() {
    int choice = 0;
    
    while (choice != 5) {
        showCipherTitle("AFFINE CIPHER");
        changeTextColor(14);
        cout << "\t\t\t======================================" << endl;
        cout << "\t\t\t           AFFINE CIPHER MENU        " << endl;
        cout << "\t\t\t======================================" << endl << endl;
        changeTextColor(11);
        cout << "\t\t1. Encrypt Text" << endl;
        cout << "\t\t2. Decrypt Text" << endl;
        cout << "\t\t3. Encrypt File" << endl;
        cout << "\t\t4. Decrypt File" << endl;
        cout << "\t\t5. Back to Main Menu" << endl << endl;
        changeTextColor(10);
        cout << "\t\tEnter choice: ";
        changeTextColor(7);
        choice = getNumberInput();
        clearBuffer();
        
        if (choice >= 1 && choice <= 4) {
            int a, b;
            changeTextColor(10);
            cout << "\n\tEnter key 'a' (coprime with 26): ";
            changeTextColor(7);
            a = getNumberInput();
            changeTextColor(10);
            cout << "\tEnter key 'b' (0-25): ";
            changeTextColor(7);
            b = getNumberInput();
            clearBuffer();
            
            if (!checkCoprime(a, 26)) {
                changeTextColor(12);
                cout << "\n\tError: 'a' must be coprime with 26!" << endl;
                cout << "\tValid: 1,3,5,7,9,11,15,17,19,21,23,25" << endl;
                changeTextColor(7);
                cout << "\tPress any key...";
                _getch();
                continue;
            }
            
            if (choice == 1 || choice == 2) {
                string text;
                changeTextColor(10);
                cout << "\n\tEnter text: ";
                changeTextColor(7);
                getline(cin, text);
                
                string result = "";
                for (char ch : text) {
                    if (choice == 1) result += encryptCharAffine(ch, a, b);
                    else result += decryptCharAffine(ch, a, b);
                }
                
                changeTextColor(10);
                if (choice == 1) cout << "\n\tEncrypted: ";
                else cout << "\n\tDecrypted: ";
                changeTextColor(11);
                cout << result << endl;
                changeTextColor(7);
                cout << "\n\tPress any key...";
                _getch();
            }
            else if (choice == 3 || choice == 4) {
                string inFile, outFile;
                changeTextColor(10);
                cout << "\n\tEnter input filename: ";
                changeTextColor(7);
                getline(cin, inFile);
                changeTextColor(10);
                cout << "\tEnter output filename: ";
                changeTextColor(7);
                getline(cin, outFile);
                
                ifstream inputFile(inFile);
                if (!inputFile) {
                    changeTextColor(12);
                    cout << "\n\tError opening file!" << endl;
                    changeTextColor(7);
                    cout << "\tPress any key...";
                    _getch();
                    continue;
                }
                
                string content((istreambuf_iterator<char>(inputFile)), istreambuf_iterator<char>());
                inputFile.close();
                
                string result = "";
                for (char ch : content) {
                    if (choice == 3) result += encryptCharAffine(ch, a, b);
                    else result += decryptCharAffine(ch, a, b);
                }
                
                ofstream outputFile(outFile);
                outputFile << result;
                outputFile.close();
                
                changeTextColor(10);
                cout << "\n\tFile saved as: " << outFile << endl;
                changeTextColor(7);
                cout << "\tPress any key...";
                _getch();
            }
        }
        else if (choice != 5) {
            changeTextColor(12);
            cout << "\n\tInvalid choice!" << endl;
            changeTextColor(7);
            Sleep(1000);
        }
    }
}

// Vigenere cipher implementations with simpler algorithm
string generateVigenereKey(const string& text, const string& keyword) {
    string key = "";
    int keyIndex = 0;
    for (int i = 0; i < text.length(); i++) {
        if (isalpha(text[i])) {
            key += toupper(keyword[keyIndex % keyword.length()]);
            keyIndex++;
        } else {
            key += text[i];
        }
    }
    return key;
}

char encryptCharVigenere(char textChar, char keyChar) {
    if (!isalpha(textChar)) return textChar;
    
    char base = islower(textChar) ? 'a' : 'A';
    int textVal = textChar - base;
    int keyVal = toupper(keyChar) - 'A';
    return (textVal + keyVal) % 26 + base;
}

char decryptCharVigenere(char textChar, char keyChar) {
    if (!isalpha(textChar)) return textChar;
    
    char base = islower(textChar) ? 'a' : 'A';
    int textVal = textChar - base;
    int keyVal = toupper(keyChar) - 'A';
    return (textVal - keyVal + 26) % 26 + base;
}

void vigenereCipherMenu() {
    int choice = 0;
    
    while (choice != 5) {
        showCipherTitle("VIGENERE CIPHER");
        changeTextColor(14);
        cout << "\t\t\t======================================" << endl;
        cout << "\t\t\t         VIGENERE CIPHER MENU        " << endl;
        cout << "\t\t\t======================================" << endl << endl;
        changeTextColor(11);
        cout << "\t\t1. Encrypt Text" << endl;
        cout << "\t\t2. Decrypt Text" << endl;
        cout << "\t\t3. Encrypt File" << endl;
        cout << "\t\t4. Decrypt File" << endl;
        cout << "\t\t5. Back to Main Menu" << endl << endl;
        changeTextColor(10);
        cout << "\t\tEnter choice: ";
        changeTextColor(7);
        choice = getNumberInput();
        clearBuffer();
        
        if (choice >= 1 && choice <= 4) {
            string keyword;
            changeTextColor(10);
            cout << "\n\tEnter keyword (letters only): ";
            changeTextColor(7);
            getline(cin, keyword);
            
            bool valid = true;
            for (char ch : keyword) {
                if (!isalpha(ch)) {
                    valid = false;
                    break;
                }
            }
            
            if (!valid) {
                changeTextColor(12);
                cout << "\n\tError: Keyword must be letters only!" << endl;
                changeTextColor(7);
                cout << "\tPress any key...";
                _getch();
                continue;
            }
            
            if (choice == 1 || choice == 2) {
                string text;
                changeTextColor(10);
                cout << "\n\tEnter text: ";
                changeTextColor(7);
                getline(cin, text);
                
                string key = generateVigenereKey(text, keyword);
                string result = "";
                
                for (int i = 0; i < text.length(); i++) {
                    if (choice == 1) result += encryptCharVigenere(text[i], key[i]);
                    else result += decryptCharVigenere(text[i], key[i]);
                }
                
                changeTextColor(10);
                if (choice == 1) cout << "\n\tEncrypted: ";
                else cout << "\n\tDecrypted: ";
                changeTextColor(11);
                cout << result << endl;
                changeTextColor(7);
                cout << "\n\tPress any key...";
                _getch();
            }
            else if (choice == 3 || choice == 4) {
                string inFile, outFile;
                changeTextColor(10);
                cout << "\n\tEnter input filename: ";
                changeTextColor(7);
                getline(cin, inFile);
                changeTextColor(10);
                cout << "\tEnter output filename: ";
                changeTextColor(7);
                getline(cin, outFile);
                
                ifstream inputFile(inFile);
                if (!inputFile) {
                    changeTextColor(12);
                    cout << "\n\tError opening file!" << endl;
                    changeTextColor(7);
                    cout << "\tPress any key...";
                    _getch();
                    continue;
                }
                
                string content((istreambuf_iterator<char>(inputFile)), istreambuf_iterator<char>());
                inputFile.close();
                
                string key = generateVigenereKey(content, keyword);
                string result = "";
                
                for (int i = 0; i < content.length(); i++) {
                    if (choice == 3) result += encryptCharVigenere(content[i], key[i]);
                    else result += decryptCharVigenere(content[i], key[i]);
                }
                
                ofstream outputFile(outFile);
                outputFile << result;
                outputFile.close();
                
                changeTextColor(10);
                cout << "\n\tFile saved as: " << outFile << endl;
                changeTextColor(7);
                cout << "\tPress any key...";
                _getch();
            }
        }
        else if (choice != 5) {
            changeTextColor(12);
            cout << "\n\tInvalid choice!" << endl;
            changeTextColor(7);
            Sleep(1000);
        }
    }
}

// RSA cipher implementations with simpler algorithm
bool isPrime(long long num) {
    if (num <= 1) return false;
    if (num <= 3) return true;
    if (num % 2 == 0 || num % 3 == 0) return false;
    
    for (long long i = 5; i * i <= num; i += 6) {
        if (num % i == 0 || num % (i + 2) == 0) return false;
    }
    return true;
}

long long findGCD(long long a, long long b) {
    while (b != 0) {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

long long modPower(long long base, long long exp, long long mod) {
    long long result = 1;
    while (exp > 0) {
        if (exp % 2 == 1) result = (result * base) % mod;
        base = (base * base) % mod;
        exp = exp / 2;
    }
    return result;
}

void generatePrivateKey() {
    long long e, n, p, q;
    
    changeTextColor(10);
    cout << "\n\tEnter public exponent (e): ";
    changeTextColor(7);
    e = getNumberInput();
    changeTextColor(10);
    cout << "\tEnter modulus (n): ";
    changeTextColor(7);
    n = getNumberInput();
    changeTextColor(10);
    cout << "\tEnter first prime (p): ";
    changeTextColor(7);
    p = getNumberInput();
    changeTextColor(10);
    cout << "\tEnter second prime (q): ";
    changeTextColor(7);
    q = getNumberInput();
    clearBuffer();
    
    if (!isPrime(p) || !isPrime(q)) {
        changeTextColor(12);
        cout << "\n\tError: p and q must be prime!" << endl;
        changeTextColor(7);
        return;
    }
    
    if (p * q != n) {
        changeTextColor(12);
        cout << "\n\tError: n should equal p * q!" << endl;
        cout << "\tp * q = " << p * q << ", but n = " << n << endl;
        changeTextColor(7);
        return;
    }
    
    long long phi = (p - 1) * (q - 1);
    
    if (e <= 1 || e >= phi || findGCD(e, phi) != 1) {
        changeTextColor(12);
        cout << "\n\tError: Invalid e!" << endl;
        cout << "\te must be between 1 and " << phi << " and coprime with " << phi << endl;
        changeTextColor(7);
        return;
    }
    
    long long d = -1;
    for (long long i = 1; i < phi; i++) {
        if ((e * i) % phi == 1) {
            d = i;
            break;
        }
    }
    
    if (d == -1) {
        changeTextColor(12);
        cout << "\n\tError: No private key found!" << endl;
        changeTextColor(7);
        return;
    }
    
    changeTextColor(10);
    cout << "\n\t=== PRIVATE KEY ===" << endl;
    cout << "\tModulus (n): " << n << endl;
    cout << "\tPrivate exponent (d): " << d << endl;
    cout << "\tPublic exponent (e): " << e << endl;
    cout << "\tφ(n) = " << phi << endl;
    cout << "\n\tSave these values!" << endl;
    changeTextColor(7);
}

void rsaEncryptFile() {
    long long e, n;
    changeTextColor(10);
    cout << "\n\tEnter public key:" << endl;
    cout << "\tPublic exponent (e): ";
    changeTextColor(7);
    e = getNumberInput();
    changeTextColor(10);
    cout << "\tModulus (n): ";
    changeTextColor(7);
    n = getNumberInput();
    clearBuffer();
    
    if (n <= 255) {
        changeTextColor(12);
        cout << "\n\tError: n must be > 255 for ASCII!" << endl;
        changeTextColor(7);
        cout << "\tPress any key...";
        _getch();
        return;
    }
    
    string inFile, outFile;
    changeTextColor(10);
    cout << "\n\tEnter input filename: ";
    changeTextColor(7);
    getline(cin, inFile);
    changeTextColor(10);
    cout << "\tEnter output filename: ";
    changeTextColor(7);
    getline(cin, outFile);
    
    ifstream inputFile(inFile);
    if (!inputFile) {
        changeTextColor(12);
        cout << "\n\tError opening file!" << endl;
        changeTextColor(7);
        cout << "\tPress any key...";
        _getch();
        return;
    }
    
    string content((istreambuf_iterator<char>(inputFile)), istreambuf_iterator<char>());
    inputFile.close();
    
    ofstream outputFile(outFile);
    if (!outputFile) {
        changeTextColor(12);
        cout << "\n\tError creating file!" << endl;
        changeTextColor(7);
        cout << "\tPress any key...";
        _getch();
        return;
    }
    
    outputFile << content.length() << endl;
    for (char ch : content) {
        long long charVal = (unsigned char)ch;
        if (charVal >= n) {
            changeTextColor(12);
            cout << "\n\tError: Character value too large!" << endl;
            changeTextColor(7);
            outputFile.close();
            return;
        }
        long long encryptedVal = modPower(charVal, e, n);
        outputFile << encryptedVal << " ";
    }
    outputFile.close();
    
    changeTextColor(10);
    cout << "\n\tFile encrypted: " << outFile << endl;
    changeTextColor(7);
    cout << "\tPress any key...";
    _getch();
}

void rsaDecryptFile() {
    long long d, n;
    changeTextColor(10);
    cout << "\n\tEnter private key:" << endl;
    cout << "\tPrivate exponent (d): ";
    changeTextColor(7);
    d = getNumberInput();
    changeTextColor(10);
    cout << "\tModulus (n): ";
    changeTextColor(7);
    n = getNumberInput();
    clearBuffer();
    
    string inFile, outFile;
    changeTextColor(10);
    cout << "\n\tEnter encrypted filename: ";
    changeTextColor(7);
    getline(cin, inFile);
    changeTextColor(10);
    cout << "\tEnter output filename: ";
    changeTextColor(7);
    getline(cin, outFile);
    
    ifstream inputFile(inFile);
    if (!inputFile) {
        changeTextColor(12);
        cout << "\n\tError opening file!" << endl;
        changeTextColor(7);
        cout << "\tPress any key...";
        _getch();
        return;
    }
    
    int count;
    inputFile >> count;
    
    vector<long long> encrypted;
    for (int i = 0; i < count; i++) {
        long long num;
        inputFile >> num;
        encrypted.push_back(num);
    }
    inputFile.close();
    
    string decrypted = "";
    for (long long num : encrypted) {
        long long decVal = modPower(num, d, n);
        decrypted += (char)decVal;
    }
    
    ofstream outputFile(outFile);
    outputFile << decrypted;
    outputFile.close();
    
    changeTextColor(10);
    cout << "\n\tFile decrypted: " << outFile << endl;
    
    changeTextColor(7);
    cout << "\n\tPress any key...";
    _getch();
}

void showSampleRSAKeys() {
    system("cls");
    showCipherTitle("RSA CIPHER", "Sample Keys");
    
    changeTextColor(14);
    cout << "\t\t\t======================================" << endl;
    cout << "\t\t\t         RSA SAMPLE KEYS            " << endl;
    cout << "\t\t\t======================================" << endl << endl;
    
    changeTextColor(11);
    cout << "\tSample RSA Key Sets for Testing:" << endl;
    cout << "\t--------------------------------" << endl << endl;
    
    changeTextColor(10);
    cout << "\t=== SET 1 (Small - For Text) ===" << endl;
    changeTextColor(7);
    cout << "\tPublic Key (e, n): (17, 3233)" << endl;
    cout << "\tPrivate Key (d, n): (2753, 3233)" << endl;
    cout << "\tPrimes: p = 61, q = 53" << endl;
    cout << "\tMax message value: 3232" << endl << endl;
    
    changeTextColor(10);
    cout << "\t=== SET 2 (Medium - For Files) ===" << endl;
    changeTextColor(7);
    cout << "\tPublic Key (e, n): (65537, 951631)" << endl;
    cout << "\tPrivate Key (d, n): (17993, 951631)" << endl;
    cout << "\tPrimes: p = 997, q = 955" << endl;
    cout << "\tMax message value: 951630" << endl << endl;
    
    changeTextColor(10);
    cout << "\t=== SET 3 (Large - Secure) ===" << endl;
    changeTextColor(7);
    cout << "\tPublic Key (e, n): (65537, 164983)" << endl;
    cout << "\tPrivate Key (d, n): (157313, 164983)" << endl;
    cout << "\tPrimes: p = 443, q = 373" << endl;
    cout << "\tMax message value: 164982" << endl << endl;
    
    changeTextColor(10);
    cout << "\t=== SET 4 (Very Small - Testing) ===" << endl;
    changeTextColor(7);
    cout << "\tPublic Key (e, n): (5, 323)" << endl;
    cout << "\tPrivate Key (d, n): (29, 323)" << endl;
    cout << "\tPrimes: p = 17, q = 19" << endl;
    cout << "\tMax message value: 322" << endl << endl;
    
    changeTextColor(11);
    cout << "\tInstructions:" << endl;
    cout << "\t-------------" << endl;
    changeTextColor(7);
    cout << "\t1. For text encryption: Use SET 1 or SET 4" << endl;
    cout << "\t2. For file encryption: Use SET 2 or SET 3" << endl;
    cout << "\t3. Make sure n > 255 for file operations" << endl;
    cout << "\t4. For testing: Use SET 4 with small messages" << endl << endl;
    
    changeTextColor(7);
    cout << "\tPress any key to return...";
    _getch();
}

void rsaCipherMenu() {
    int choice = 0;
    
    while (choice != 7) {
        showCipherTitle("RSA CIPHER");
        changeTextColor(14);
        cout << "\t\t\t======================================" << endl;
        cout << "\t\t\t            RSA CIPHER MENU          " << endl;
        cout << "\t\t\t======================================" << endl << endl;
        changeTextColor(11);
        cout << "\t\t1. Generate Private Key from Public" << endl;
        cout << "\t\t2. Encrypt Text" << endl;
        cout << "\t\t3. Decrypt Text" << endl;
        cout << "\t\t4. Encrypt File" << endl;
        cout << "\t\t5. Decrypt File" << endl;
        cout << "\t\t6. View Sample Keys" << endl;
        cout << "\t\t7. Back to Main Menu" << endl << endl;
        changeTextColor(10);
        cout << "\t\tEnter choice: ";
        changeTextColor(7);
        choice = getNumberInput();
        clearBuffer();
        
        if (choice == 1) {
            generatePrivateKey();
            cout << "\n\tPress any key...";
            _getch();
        }
        else if (choice == 2) {
            long long e, n;
            changeTextColor(10);
            cout << "\n\tEnter public key:" << endl;
            cout << "\tPublic exponent (e): ";
            changeTextColor(7);
            e = getNumberInput();
            changeTextColor(10);
            cout << "\tModulus (n): ";
            changeTextColor(7);
            n = getNumberInput();
            clearBuffer();
            
            string text;
            changeTextColor(10);
            cout << "\n\tEnter text: ";
            changeTextColor(7);
            getline(cin, text);
            
            changeTextColor(10);
            cout << "\n\tEncrypted numbers:" << endl;
            changeTextColor(11);
            for (char ch : text) {
                long long charVal = (unsigned char)ch;
                if (charVal >= n) {
                    changeTextColor(12);
                    cout << "\tError: Character value too large!" << endl;
                    changeTextColor(7);
                    break;
                }
                long long encryptedVal = modPower(charVal, e, n);
                cout << encryptedVal << " ";
            }
            cout << endl;
            changeTextColor(7);
            cout << "\n\tPress any key...";
            _getch();
        }
        else if (choice == 3) {
            long long d, n;
            changeTextColor(10);
            cout << "\n\tEnter private key:" << endl;
            cout << "\tPrivate exponent (d): ";
            changeTextColor(7);
            d = getNumberInput();
            changeTextColor(10);
            cout << "\tModulus (n): ";
            changeTextColor(7);
            n = getNumberInput();
            clearBuffer();
            
            changeTextColor(10);
            cout << "\n\tEnter encrypted numbers (space separated, end with -1):" << endl;
            changeTextColor(7);
            cout << "\t";
            vector<long long> encrypted;
            long long num;
            while (cin >> num && num != -1) encrypted.push_back(num);
            clearBuffer();
            
            string decrypted = "";
            for (long long num : encrypted) {
                long long decVal = modPower(num, d, n);
                decrypted += (char)decVal;
            }
            
            changeTextColor(10);
            cout << "\n\tDecrypted text: ";
            changeTextColor(11);
            cout << decrypted << endl;
            changeTextColor(7);
            cout << "\n\tPress any key...";
            _getch();
        }
        else if (choice == 4) rsaEncryptFile();
        else if (choice == 5) rsaDecryptFile();
        else if (choice == 6) showSampleRSAKeys();
        else if (choice != 7) {
            changeTextColor(12);
            cout << "\n\tInvalid choice!" << endl;
            changeTextColor(7);
            Sleep(1000);
        }
    }
}