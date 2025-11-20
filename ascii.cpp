#include <iostream>
#include <limits>
#include <string>
#include <unordered_map>
using std::cout, std::cin, std::endl, std::unordered_map, std::string,
    std::numeric_limits, std::streamsize;

// Have an unordered map to be a hashtable of the ascii art,
// where we have strings as values and strings as keys.
unordered_map<string, string> asciiMap;

// Functions must be "prototyped" in C++ before main, or main will not recognize
// them.
void makeAscii();

void startMenu();
bool endMenu(const string& art);

int main() {
  makeAscii();
  startMenu();
  return 0;
}

// Do not use recursion for menus! Use loops!
void startMenu() {
  // make an empty string to hold what art was printed
  string art;
  int choice;
  while (true) {
    // list of menu options.
    cout << "-Choose your art to display-" << endl;
    cout << "1: frog" << endl;
    cout << "2: bulbasaur" << endl;
    cout << "3: linux penguin" << endl;
    cout << "4: apple" << endl;
    cout << "5: earth" << endl;
    cout << "Enter your choice: " << endl;
    // We enforce that the user enters EXACTLY one character.
    // 1–5. First int could be '1'..'5', '\n', EOF, etc.
    int firstInt = cin.get();

    // If EOF, the stream is in a bad state (Ctrl+D / closed input).
    if (firstInt == EOF) {
      cin.clear();
      cout << "End of file. Exiting." << endl;
      return;
    }

    // Look at the next character without removing it from the buffer.
    int second = cin.peek();

    // If the next character is not '\n', the user typed more than one
    // character (e.g., "12", "1abc"). That is not allowed.
    if (second != '\n') {
      // Discard the rest of the line so this junk does not affect future input.
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      cout << "Error. Please enter a SINGLE digit between 1 and 5." << endl;
      continue;
    }

    // At this point, the line is exactly: <firstInt><newline>.
    // Consume the newline.
    cin.get();

    choice = firstInt - '0';
    switch (choice) {
      case 1:
        // print the ascii. Get it using .at(), using [] would create keys if
        // they dont already exist.
        cout << asciiMap.at("frog") << endl;
        // set what art was printed for later
        art = "frog";
        // break the switch statement for the later endMenu check
        break;
      case 2:
        cout << asciiMap.at("bulbasaur") << endl;
        art = "bulbasaur";
        break;
      case 3:
        cout << asciiMap.at("linux penguin") << endl;
        art = "linux penguin";
        break;
      case 4:
        cout << asciiMap.at("apple") << endl;
        art = "apple";
        break;
      case 5:
        cout << asciiMap.at("earth") << endl;
        art = "earth";
        break;
      // All other cases are invalid.
      default:
        cout << "Error. Please make a choice between 1 and 5." << endl;
        // continue to not run the below code
        continue;
    }
    // art must be set by one of the 5 above cases that are not default.
    // Otherwise, this section of code would not run
    // store the result of the end menu
    bool result = endMenu(art);
    // the user wanted to end the code, so we return to main to end the code.
    if (result == false) {
      return;
    }
    // otherwise we do nothing so the while loop runs again, reprinting the
    // menu as desired.
  }
}

// Don't let endMenu() call startMenu() and vice versa—that leads to recursion.
// Instead, endMenu returns a bool so startMenu can decide what to do next.
bool endMenu(const string& art) {
  cout << art << " has been printed. Would you like to choose another?" << endl;
  int first;
  int second;
  while (true) {
    cout << "Please choose: [y] or [n] for yes or no:" << endl;
    // Accept ONLY 'y' or 'n'. This avoids accidental confirmations from longer
    // inputs that happen to start with 'y' (e.g., typing in the wrong window).

    // Read the first character. cin.get() returns an int so it can represent
    // all valid char values plus EOF (-1). We'll check for EOF before treating
    // it as a char.
    first = cin.get();

    // If first is EOF, the stream is in a failed state (Ctrl+D, closed input,
    // etc.)
    if (first == EOF) {
      cin.clear();
      cout << "Error. Please input y or n." << endl;
      continue;
    }

    // look at the *next* character, but don't remove it from the cin buffer yet
    second = cin.peek();

    // If the next character is not '\n', the user typed more than one
    // character, so the input cannot be exactly 'y' or 'n'.
    if (second != '\n') {
      // Discard the rest of the line. This prevents huge inputs from ending up
      // in a std::string (which would allocate a massive buffer) and ensures we
      // never store more than the first character. This still runs very
      // fast—even with millions of characters—because ignore() discards input
      // in large buffered chunks.
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      cout << "Error. Please input y or n." << endl;
      // start the loop over with continue.
      continue;
    }

    // At this point, we know the line has exactly:
    // a first character (may or may not be y/n) and a newline.
    // So consume the newline using get().
    cin.get();

    // Now interpret the first character. Comparing the int to 'y'/'n' works
    // because character literals are just ints.
    if (first == 'y') {
      return true;
    } else if (first == 'n') {
      cout << "Thank you, have a great day!" << endl;
      return false;
    } else {
      cout << "Error. Please input y or n." << endl;
      // do nothing, as the if-else statement ends after this, and the loop
      // resets as expected.
    }
  }
}

void makeAscii() {
  // R"()" forces all text, including characters like ' and "" to be displayed
  // as text instead of instruction.
  asciiMap["frog"] = R"(
            (')-=-(')
          __(   "   )__
          / _/'-----'\_ \
      ___\\ \\     // //___
  jgs  >____)/_\---/_\(____<
  )";
  asciiMap["bulbasaur"] = R"(
                                              /
                          _,.------....___,.' ',.-.
                      ,-'          _,.--"        |
                    ,'         _.-'              .
                    /   ,     ,'                   `
                  .   /     /                     ``.
                  |  |     .                       \.\
        ____      |___._.  |       __               \ `.
      .'    `---""       ``"-.--"'`  \               .  \
      .  ,            __               `              |   .
      `,'         ,-"'  .               \             |    L
    ,'          '    _.'                -._          /    |
    ,`-.    ,".   `--'                      >.      ,'     |
  . .'\'   `-'       __    ,  ,-.         /  `.__.-      ,'
  ||:, .           ,'  ;  /  / \ `        `.    .      .'/
  j|:D  \          `--'  ' ,'_  . .         `.__, \   , /
  / L:_  |                 .  "' :_;                `.'.'
  .    ""'                  """""'                    V
  `.                                 .    `.   _,..  `
    `,_   .    .                _,-'/    .. `,'   __  `
      ) \`._        ___....----"'  ,'   .'  \ |   '  \  .
    /   `. "`-.--"'         _,' ,'     `---' |    `./  |
    .   _  `""'--.._____..--"   ,             '         |
    | ." `. `-.                /-.           /          ,
    | `._.'    `,_            ;  /         ,'          .
  .'          /| `-.        . ,'         ,           ,
  '-.__ __ _,','    '`-..___;-...__   ,.'\ ____.___.'
  `"^--'..'   '-`-^-'"--    `-^-'`.''"""""`.,^.`.--' mh
  )";
  asciiMap["linux penguin"] = R"(
              .-"""-.
            '       \
            |,.  ,-.  |
            |()L( ()| |
            |,'  `".| |
            |.___.',| `
          .j `--"' `  `.
          / '        '   \
        / /          `   `.
        / /            `    .
      / /              l   |
      . ,               |   |
      ,"`.             .|   |
  _.'   ``.          | `..-'l
  |       `.`,        |      `.
  |         `.    __.j         )
  |__        |--""___|      ,-'
    `"--...,+""""   `._,.-' mh
  )";
  asciiMap["apple"] = R"(
    ,--./,-.
  / #      \
  |          |
  \        /    hjw
    `._,._,'
  )";
  asciiMap["earth"] = R"(
             _____
          .-'.  ':'-.
        .''::: .:    '.
       /   :::::'      \
      ;.    ':' `       ;
      |       '..       |
      ; '      ::::.    ;
       \       '::::   /
        '.      :::  .'
jgs        '-.___'_.-'
  )";
}
