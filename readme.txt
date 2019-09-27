-----------------------------
What is vigenere.c?
-----------------------------
This is a program used to encrypt/decrypt strings using a Vigenere cipher.

The idea of a Vigenere cipher was taken from one of the slides from my
Security 101 class. That being said, the program is of my own design.

You can find the explanation for how it works here:
https://www.ole.bris.ac.uk/bbcswebdav/courses/COMS10005_2018/web/lectures/Cryptography-historical.pdf

Note: Instead of modulo 26, my version of the cipher uses modulo 52
due to the fact that it takes both upper and lowercase letters into
account.

-----------------------------
How do we use it?
-----------------------------
Enter the key, option, and text you wish to encrypt/decrypt as arguments.

Example of encryption: './vigenere bristol e "Hello World!"'

Example of decryption: './vigenere bristol d "iVTdh KPiTV!"'

Note: double quotation marks are required for texts that consist of
more than one word. Bash might also complain about ending the string
with an exclamation mark. (type "! " instead of "!")

-----------------------------
What could be improved?
-----------------------------
The way that the text is entered as a parameter is kind of awkward.
Although I have tried to use the scanf() function to allow the user
to enter the text after the program has started, scanf() stops reading
when it encounters any whitespace, making it unsuitable for text that
consists of more than one word.
