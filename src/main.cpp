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
        
        std::cout << "Enter an 8-bit binary string (or 'exit' to quit): ";
        std::getline(std::cin, input);

        // Check if the user wants to exit
        if (input == "exit") {
            break;
        }

        if (input.length() != 8) {
            std::cout << "Invalid input, Please enter an 8-bit binary string." << std::endl;
        }

        std::bitset<8> binaryRepresentation(input);
        unsigned char character = static_cast<unsigned char>(binaryRepresentation.to_ulong());

        // Print the result
        std::cout << "Binary: " << binaryRepresentation << std::endl;
        std::cout << "Decimal: " << static_cast<unsigned int>(character) << std::endl;
        std::cout << "Character: " << character << std::endl;

        create_rhythm(character, ++count);
        create_instrument("./samples/big snare.wav", count, count);
        
    } 
}

