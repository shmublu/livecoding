#include <SFML/Audio.hpp>
#include <iostream>
#include "music.h"
#include <sstream>
#include <algorithm>

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
            std::cout << "Invalid input, enter an 8-bit binary string." << std::endl;
        } else {
            std::reverse(input.begin(), input.end());
            std::bitset<8> binaryRepresentation(input);
            unsigned char character = static_cast<unsigned char>(binaryRepresentation.to_ulong());
            create_rhythm(character, ++count);
            create_instrument("./samples/big snare.wav", count, count);
            std::cout << "Created instrument " << count << " with rhythm " << input << std::endl;
        }
        
    } 
}

