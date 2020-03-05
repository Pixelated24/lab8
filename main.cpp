#include <iostream>
#include <fstream>
#include <string>

using std::string;
using std::endl;
using std::cin;
using std::cout;
using std::ifstream;
using std::ofstream;

void displayMenu();
void setShiftKeyValue(int& key);
void encrypt(int key);
void decrypt(int key);


int main() {
    int choice, key;
    key = 3; //default
    do {
        displayMenu();
        cin >> choice;
        if (choice == 1) {
            setShiftKeyValue(key);
        }
        else if (choice == 2) {
            encrypt(key);
        }
        else if (choice == 3) {
            decrypt(key);
        }
    } while(choice != 4);
    return 0;
}
void setShiftKeyValue(int& key){
    cout << "What would you like the offset to be 0 - 10 (0: None) ";
    do{
    cin >> key;
    } while (key < 0 || key > 10);
}
void displayMenu(){
    cout << endl << "1. Set the shift key value (default is 3)" << endl;
    cout << "2. Encrypt a file" << endl;
    cout << "3. Decrypt a file" << endl;
    cout << "4. Quit" << endl;
}
void encrypt(int key){
    string inFileName, outFileName;
    ifstream inFile;
    ofstream outFile;
    cout << "What file would you like to encrypt? (Including extension) ";
    do {
        cin >> inFileName;
        inFile.open(inFileName);
    } while (inFile.fail());
    cout << "Name of encrypted file? (Including extension) ";
    do {
        cin >> outFileName;
        outFile.open(outFileName);
    } while (outFile.fail());
    cout << "Encrypting...";
    char temp;
    while(!inFile.eof()){
        inFile.get(temp);
        bool upperCaseLetter = temp >= 'A' && temp <= 'Z';
        bool lowerCaseLetter = temp >= 'a' && temp <= 'z';
        bool isLetter = upperCaseLetter || lowerCaseLetter;
        if(!isLetter){
            outFile << temp;
        } else {
            temp = (char)((int)temp + key);
            if(temp > 'Z' && temp < 'a'){
                temp = (char)((int)temp -91+65);
                outFile << temp;
            } else if (temp > 'z'){
                temp = (char)((int)temp -122+97);
                outFile << temp;
            } else {
                outFile << temp;
            }
        }
    }
        outFile.close();
        inFile.close();
}

void decrypt(int key){
    string inFileName, outFileName;
    ifstream inFile;
    ofstream outFile;
    cout << "What file would you like to decrypt? (Including extension) ";
    do {
        cin >> inFileName;
        inFile.open(inFileName);
    } while (inFile.fail());
    cout << "What would you like the decrypted file to be called? (Including extension) ";
    do {
        cin >> outFileName;
        outFile.open(outFileName);
    } while (outFile.fail());
    cout << "Decrypting...";
    while(!inFile.eof()){
        char temp;
        inFile.get(temp);
        bool upperCaseLetter = temp >= 'A' && temp <= 'Z';
        bool lowerCaseLetter = temp >= 'a' && temp <= 'z';
        bool isLetter = upperCaseLetter || lowerCaseLetter;
        if(!isLetter){
            outFile << temp;
        } else {
            temp = (char)((int)temp - key);
            if(temp < 'A'){
                temp = (char)(90 - 65 - (int)temp);
                outFile << temp;
            } else if (temp > 'Z' && temp < 'a') {
                temp = 122 - 97 - (int)temp;
                outFile << temp;
            } else {
                outFile << temp;
            }
        }
    }
    outFile.close();
    inFile.close();
}