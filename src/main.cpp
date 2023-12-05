#include <SFML/Audio.hpp>
#include <iostream>
#include "music.h"
#include <sstream>
#include <algorithm>
#include <bitset>

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
    /*
        void change_rhythm_pattern(char pattern, int rhythm_id);
        void change_instrument_file(const std::string& filepath, int instrument_id);
        void change_instrument_pitch(float pitch, int instrument_id);
        char get_instrument_rhythm(int instrument_id);
    */

    // Testing Get_instrument_rhythm
    char rhyt = get_instrument_rhythm(count);
    std::bitset<8> rhytbinary(rhyt);
    std::cout << "Testing get instr rhyt -- rhythm: " << rhytbinary << std:: endl;

    // Testing change_rhythm_pattern
    change_rhythm_pattern('A', count);
    rhyt = get_instrument_rhythm(count);
    std::bitset<8> rhytbinary2(rhyt);
    std::cout << "Testing change rhyt -- new rhythm: " << rhytbinary2 << std:: endl;

    // Testing change_instrument_pitch
    change_instrument_pitch(10, count);

    // Testing change_instrument_file
    change_instrument_file("./samples/cocoon_perc.wav", count);
    }

}

