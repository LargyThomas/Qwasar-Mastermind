# Welcome to My Mastermind
***

## Task
What is the problem? And where is the challenge?
The goal of this project is to code a version of the Mastermind game.

## Description
How have you solved the problem?
The program generates or receives as an argument a secret code of 4 different digits between 0 and 8.

## Installation
How to install your project? npm install? make? make re?
I used the terminal to create my files and my Makefile to compile.

## Usage
I created several functions to handle different tasks (generate_code(), str_len(), validation_format(), compare_code(), read_code(), handle_arguments())

In the main function:
The player must try to guess the code within a limited number of attempts (10 by default, adjustable with -t).
After each guess, the program displays:

The number of well-placed digits (correct value + correct position)
The number of misplaced digits (correct value but wrong position)
If the player finds the exact code, the program displays a victory message.


### The Core Team


<span><i>Made at <a href='https://qwasar.io'>Qwasar SV -- Software Engineering School</a></i></span>
