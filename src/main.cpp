#include <SFML/Audio.hpp>
#include <iostream>
#include "music.h"
#include <sstream>

int main() {
    // test
    start_music_thread();

    
    std::string input;
    int number;
    int count = 0;

    while (true) {
        
        std::cout << "Enter a number (or 'exit' to quit): ";
        std::getline(std::cin, input);

        // Check if the user wants to exit
        if (input == "exit") {
            break;
        }

        // Using stringstream to convert string to number
        std::stringstream ss(input);
        if (ss >> number) {
            std::cout << "You entered: " << number << std::endl;
        } else {
            std::cout << "Invalid input. Please enter a valid number." << std::endl;
        }
        create_rhythm(number, ++count);
        create_instrument("./samples/uh.wav", count, count);
        
} 

    }

