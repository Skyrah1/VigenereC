/*
Encrypt/decrypt text using a Vigenere cipher.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

const char * alphabet =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

//----------------------------------------------------------------------------//
//------------------------The really important stuff--------------------------//
//----------------------------------------------------------------------------//

//Finds the first index of a character in a string
//Returns -1 if character is not in string
int indexOfChar(char c, const char * str){
    int index = -1;
    char currentChar;
    bool found = false;
    for (int i = 0; i < strlen(str) && found == false; i++){
      currentChar = str[i];
      if (c == currentChar){
            index = i;
            found = true;
        }
    }
    return index;
}

//Takes in a key, a character (plain text) and the current key index
//Returns the encrypted character
char encryptChar(char * key, char oldChar, int keyIndex){
    int newCharIndex;
    int oldCharAlphaIndex = indexOfChar(oldChar, alphabet);
    int keyAlphaIndex = indexOfChar(key[keyIndex], alphabet);
    char newChar;

    if (oldCharAlphaIndex != -1){
        newCharIndex = (oldCharAlphaIndex + keyAlphaIndex) % strlen(alphabet);
        newChar = alphabet[newCharIndex];
    } else {
        newChar = oldChar;
    }

    return newChar;
}

//Takes in a key, a character (ciphertext) and the current key index
//Returns the decrypted character
char decryptChar(char * key, char oldChar, int keyIndex){
    int newCharIndex;
    int oldCharAlphaIndex = indexOfChar(oldChar, alphabet);
    int keyAlphaIndex = indexOfChar(key[keyIndex], alphabet);
    char newChar;

    if (oldCharAlphaIndex != -1){
        newCharIndex = (oldCharAlphaIndex - keyAlphaIndex);
        if (newCharIndex < 0){
            newCharIndex += strlen(alphabet);
        }
        newChar = alphabet[newCharIndex];
    } else {
        newChar = oldChar;
    }

    return newChar;
}

//Encrypts/decrypts a string depending on the option
//If option is "e", encrypt text
//If option is "d", decrypt text
//Store the result in...result[]
//Note: the length of result[] needs to be at least (the length of the text + 1)
//to add the null character at the end
void encryptOrDecryptString(char * key, char * option, char * text, char result[]){
    int keyIndex = 0;
    //Encrypt/decrypt in this loop
    for (int i = 0; i < strlen(text); i++){
        if (strcmp(option, "e") == 0){
            result[i] = encryptChar(key, text[i], keyIndex);
        } else if (strcmp(option, "d") == 0){
            result[i] = decryptChar(key, text[i], keyIndex);
        }
        if (indexOfChar(text[i], alphabet) != -1){
            //printf("%d\n", keyIndex);
            keyIndex = (keyIndex + 1) % (strlen(key));
        }
    }
    result[strlen(text)] = '\0';
}

//----------------------------------------------------------------------------//
//---------------------------Automated testing--------------------------------//
//----------------------------------------------------------------------------//

//Test that encryptChar() is working
//Verified all cases by hand
//Note to self: remember to start counting from zero
//when encrypting by hand
void testEncryptChar(){
    assert(encryptChar("ImagineBreaker", 'Z', 0) == 'h');
    assert(encryptChar("Electromaster", 'A', 12) == 'r');
    assert(encryptChar("Accelerator", 'W', 4) == 'H');
    assert(encryptChar("STEAL", 'A', 2) == 'E');
    assert(encryptChar("EXPLOSION", 'r', 5) == 'J');
    assert(encryptChar("BenevolentCrumpetstash", 'u', 19) == 'U');
    assert(encryptChar("insertNavySealsCopypastaHere", 'd', 27) == 'H');
    assert(encryptChar("IdkManIRanOutOfIdeas", 'o', 6) == 'w');
    assert(encryptChar("lol", '!', 1) == '!');
}

//Test that decryptChar() is working
//This test takes advantage of the fact that decrypting an
//encrypted character with the same key and keyIndex should
//yield the same result
void testDecryptChar(){
    assert(decryptChar("Bedivere", encryptChar("Bedivere", 'K', 0), 0) == 'K');
    assert(decryptChar("Gareth", encryptChar("Gareth", 'O', 1), 1) == 'O');
    assert(decryptChar("Lancelot", encryptChar("Lancelot", 'N', 2), 2) == 'N');
    assert(decryptChar("Mordred", encryptChar("Mordred", 'o', 3), 3) == 'o');
    assert(decryptChar("Galahad", encryptChar("Galahad", 's', 4), 4) == 's');
    assert(decryptChar("Arthur", encryptChar("Arthur", 'u', 5), 5) == 'u');
    assert(decryptChar("RANSAGASHINDA", encryptChar("RANSAGASHINDA", 'B', 6), 6) == 'B');
    assert(decryptChar("KONOHITODENASHI", encryptChar("KONOHITODENASHI", 'a', 7), 7) == 'a');
    assert(decryptChar("yorokobeshounen", encryptChar("yorokobeshounen", '!', 8), 8) == '!');
}

//Tests the encryptOrDecryptString function
//(yes, this IS a JoJo reference)
void testEncryptOrDecryptString(){
    char * original = "SONO CHI NO SADAME";
    char * key = "JoJo";
    char eTest[strlen(original) + 1];
    encryptOrDecryptString(key, "e", original, eTest);
    //printf("%s\n", eTest);
    assert(eTest[0] == 'b' && eTest[1] == 'C' && eTest[2] == 'W' && eTest[3] == 'C');
    assert(eTest[4] == ' ' && eTest[5] == 'L' && eTest[6] == 'v' && eTest[7] == 'R');
    assert(eTest[8] == ' ' && eTest[9] == 'B' && eTest[10] == 'X' && eTest[11] == ' ');
    assert(eTest[12] == 'G' && eTest[13] == 'J' && eTest[14] == 'r' && eTest[15] == 'J');
    assert(eTest[16] == 'A' && eTest[17] == 'N' && eTest[18] == '\0');
    char dTest[strlen(eTest + 1)];
    encryptOrDecryptString(key, "d", eTest, dTest);
    assert(strcmp(dTest, original) == 0);
}

//Test it out!
void test(){
    testEncryptChar();
    testDecryptChar();
    testEncryptOrDecryptString();
}

//----------------------------------------------------------------------------//
//----------------------------Main Input/Output-------------------------------//
//----------------------------------------------------------------------------//

//Prints out how to use the function if the user gets it wrong
void displayInstructions(){
    printf("Enter the key, option, and text you wish to encrypt/decrypt as arguments.\n");
    printf("Example of encryption: './vigenere bristol e \"Hello World!\"' to encrypt\n");
    printf("Example of decryption: './vigenere bristol d \"iVTdh KPiTV!\"' to decrypt\n");
    printf("Note: double quotation marks are required for texts that consist of\n");
    printf("more than one word. Bash might also complain about ending the string with\n");
    printf("an exclamation mark. (type ! \" instead of !\")\n");
}

/*
If no arguments are given, runs automatic tests on the functions.
If 3 arguments are given - those being the encryption key, the option
(either e for encrypt or d for decrypt) and a string, performs either
encryption or decryption on the string using a Vigenere cipher and a
key.
*/
int main(int n, char * args[n]){
    setbuf(stdout, NULL);
    if (n == 1){
        printf("Running tests...\n\n");
        test();
        printf("Tests complete! :D\n");
    }else if (n == 4){
        char * key = args[1];
        char * option = args[2];
        char * text = args[3];
        char result[strlen(text) + 1];

        encryptOrDecryptString(key, option, text, result);
        printf("%s\n", result);
        //If the user enters an option other than "d" or "e"
        if (strcmp(option, "e") != 0 && strcmp(option, "d") != 0){
            displayInstructions();
        }
    } else {
        displayInstructions();
    }
    return 0;
}
