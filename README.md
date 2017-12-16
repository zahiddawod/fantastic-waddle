Assignment 5 - README

CONTENTS OF THIS FILE
-------------------
 * Purpose of software
 * Developer
 * File list
 * How to compile
 * Issues & limitations
 * How to use software

-------------------
Purpose of software
-------------------

The purpose of this software is to read from binary files, differentiating between
parent and child processes, as well as program morphing, inter process communication,
and usage of signals.

-------------------
Developer
-------------------

Auther: Zahid Dawod

Student ID: #########

Development Date: 02/12/2017

-------------------
File list
-------------------

 - createBinary.c: A program that creates a binary file from a given set of numbers
 
 - isPrime.c: This is the base program for checking whether a number is a prime
 
 - singlePrime.c: Program that retrieves first number of given file and morphs into isPrime program
 
 - singleSpawn.c: Program that creates child/parent process and morphs child process into isPrime program
 
 - multiSpawn.c: Program that creates multiple child processes to check 10 different numbers read from a given file
 
 - prime.bin: A file that contains 12 unsigned numbers in binary format
 
 - prime.txt: A file that contains 12 unsigned numbers in ASCII format
 
 - Makefile2: Second makefile rules for 

Files created for testing purposes:
-test.txt
-test.bin

EXECUTABLE FILES:
- cbinary
- isPrime
- singlePrime
- singleSpawn
- multiSpawn

-------------------
How to compile
-------------------

In order to compile ensure you follow you have all the files available by extracting it from the tar file into a folder.
After that depending on which program you want to compile type 'gcc -o fileName fileName.c' in the console while being in the same directory as your files.
Where 'fileName' is the name of the c file you are trying to compile.

Compiling isPrime.c program (Example):
1. Ensure that you are in the directory of the file you are trying to compile
2. Type 'gcc -o isPrime isPrime.c'
3. Then an executable file will be created for that program

Command for singlePrime compilation:
gcc -o singlePrime singlePrime.c

Command for singleSpawn compilation:
gcc -o singleSpawn singleSpawn.c

Command for multiSpawn compilation:
gcc -o multiSpawn multiSpawn.c

--------------------------------------
Issues & limitations
--------------------------------------

When reading binary files the name of the file has to contain '.bin' in it for the program to properly read from the file.
It is assumed that the file being read is a .bin

-------------------
How to use software
-------------------

Once the program you want to use is compiled type "./" with the name of the executable file.

Assuming the program we want to use is already compiled ..
For example (isPrime program):
Type './isPrime #' where # is the number you want to check that is prime
