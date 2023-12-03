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
    std::string input;
    int rhythmNumber, pitchNumber;

    std::cout << "Enter a rhythm number (or 'exit' to quit): ";
    std::getline(std::cin, input);

    // Check if the user wants to exit
    if (input == "exit") {
        break;
    }

    // Using stringstream to convert string to number for rhythm
    std::stringstream ss(input);
    if (ss >> rhythmNumber) {
        std::cout << "Rhythm number entered: " << rhythmNumber << std::endl;
    } else {
        std::cout << "Invalid input for rhythm. Please enter a valid number." << std::endl;
        continue; // Go to the next iteration of the loop
    }

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

    create_rhythm(rhythmNumber, ++count);
    create_instrument("./samples/big snare.wav", count, count, pitchNumber);
}

}

