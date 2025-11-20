# ASCII Art Menu (C++)

A small C++ project I wrote to get more comfortable with the language.  
The program shows a simple menu, lets the user select one of a few pieces of ASCII art (originals from https://www.asciiart.eu/, included locally), prints it, and then asks
whether they want to print more art or exit. The ASCII author tags are retained for attribution purposes (such as jgs in the frog ascii).

This is not a serious application. It is just a practice project focused on input handling and basic control flow in C++.

## Design choices

### 1. Strict single-character menu input
The program accepts only one digit between 1 and 5.  
It checks this by reading one character with cin.get(), using cin.peek() to confirm that the next character is a newline, and using cin.ignore() to discard anything extra.  
This prevents accidental multi-character input and avoids allocating large buffers if a user pastes a long string. 
Not super necessary for a program this simple, but I wanted to practice making input handling more robust and predictable.

### 2. Strict 'y' or 'n' confirmation
After printing art, the program accepts only 'y' or 'n' as valid responses.  
This is similar to many terminal tools that only allow single-key confirmation.  
Input is checked the same way as above: if more than one character is entered before the newline, the entire line is rejected. Like above, not necessary, just nice to have.

### 3. No recursion in menu logic
The program uses while loops for menu repetition.  
This avoid using recursion for menu prompts, which can eventually overflow the call stack if the menu calls itself repeatedly. 
This is a much more real risk than 1 or 2, because deep menu recursion can quickly overflow the call stack.

### 4. No mutual recursion between startMenu and endMenu
Instead of having the menus call each other, `endMenu` returns a boolean indicating whether the user wants to continue.  
`startMenu` uses this return value to decide what to do next. This prevents the two functions from calling each other forever. Again, easier to trigger than 1 and 2.

## How to compile
g++ -std=c++17 -Wall -Wextra ascii.cpp -o ascii-menu
./ascii-menu

## What I practiced

* strict and safe input validation (points 1 and 2)
* basic use of `std::unordered_map`  
* raw string literals. I used (R"( ... )") for ASCII art to avoid having to escape quotes and backslashes that are displayed in the art.
* clean control flow without recursion  (points 3 and 4)
* basic use of `std::unordered_map`
* basic use of `std::array` instead of `std::unordered_map` for storing the ASCII art.  A hash map is only useful when you need key-based lookup, but in this project the menu uses fixed numeric positions (1–5). Since the number of art is known at compile time, `std::array` is simpler and avoids the dynamic memory used by `std::vector`.
