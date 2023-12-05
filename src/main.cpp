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
    std::string input;
    int rhythmNumber;
    float pitchNumber;

    std::cout << "Enter an 8-bit binary string (or 'exit' to quit): ";
    std::getline(std::cin, input);

    // Check if the user wants to exit
    if (input == "exit") {
        break;
    }

    if (input.length() != 8) {
        std::cout << "Invalid input, enter an 8-bit binary string." << std::endl;
        continue;
    }
  
    // Reverse so plays in order of input
    std::reverse(input.begin(), input.end());
    std::bitset<8> binaryRepresentation(input);
    unsigned char character = static_cast<unsigned char>(binaryRepresentation.to_ulong());

    std::cout << "Enter a pitch number: ";
    std::getline(std::cin, input);

    // Using stringstream to convert string to number for pitch
    std::stringstream ssPitch(input);
    if (ssPitch >> pitchNumber) {
        std::cout << "Pitch number entered: " << pitchNumber << std::endl;
    } else {
        std::cout << "Invalid input for pitch. Please enter a valid number." << std::endl;
        continue; // Go to the next iteration of the loop
    }

    create_rhythm(character, ++count);
    create_instrument("./samples/big snare.wav", count, count, pitchNumber);
    std::cout << "Created instrument " << count << " with rhythm " << input << std::endl;
}

}

