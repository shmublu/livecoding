#include "music.h"
#include "instrument.h"
#include <vector>
#include <bitset>
#include <fstream>

std::unordered_map<std::string, Instrument> instruments;
std::unordered_map<std::string, Rhythm> rhythms;
std::shared_mutex state_mutex;

bool isDuplicate(const std::vector<std::string>& vec, const std::string& value) {
    return std::find(vec.begin(), vec.end(), value) != vec.end();
}


std::string charToBinary(char c) {
    return std::bitset<8>(c).to_string();
}


void listInstruments() {
    std::shared_lock<std::shared_mutex> lock(state_mutex); // Ensures thread safety
    std::cout << "Instruments:\n";
    for (const auto& pair : instruments) {
        std::cout << "Instrument Name: " << pair.first << " - Sound File: " << pair.second.filepath  << " - Rhythm Name: " << pair.second.rhythm_id <<"\n";
    }
}

void listRhythms() {
    std::shared_lock<std::shared_mutex> lock(state_mutex); // Ensures thread safety
    std::cout << "Rhythms:\n";
    for (const auto& rhythm_pair : rhythms) {
            std::cout << "Rhythm Name: " << rhythm_pair.first << " - Pattern: " << charToBinary(rhythm_pair.second.pattern) << "\n";
        }
}




void create_instrument(const std::string& filepath, std::string rhythm_name, std::string instrument_name, int pitchVal) {
    std::lock_guard<std::shared_mutex> lock(state_mutex);

    // Check if the instrument already exists
    if (instruments.find(instrument_name) != instruments.end()) {
        std::cout << "Error: Instrument '" << instrument_name << "' already exists." << std::endl;
        return;
    }

    // Check if the file exists
    std::ifstream file(filepath);
    if (!file) {
        std::cout << "Error: File at '" << filepath << "' does not exist." << std::endl;
        return;
    }

    // If file exists, proceed to create the instrument
    Instrument newInstrument(filepath, rhythm_name, pitchVal);
    instruments.emplace(instrument_name, newInstrument);
    std::cout << "Instrument '" << instrument_name << "' created successfully." << std::endl;
}


char convertToChar(const std::string& binaryStr) {
    // Check if the string length is 8
    if (binaryStr.length() != 8) {
        throw std::invalid_argument("Error: String must be 8 characters long.");
    }

    // Check if the string contains only '0's and '1's
    for (char c : binaryStr) {
        if (c != '0' && c != '1') {
            throw std::invalid_argument("Error: String must contain only '0's and '1's.");
        }
    }

    // Convert binary string to character
    char character = static_cast<char>(std::bitset<8>(binaryStr).to_ulong());
    return character;
}
void create_rhythm(std::string input, std::string rhythm_name) {
    std::lock_guard<std::shared_mutex> lock(state_mutex);
    if (rhythms.find(rhythm_name) == rhythms.end()) {
        char pattern = convertToChar(input);
        rhythms[rhythm_name] = {pattern};
        std::cout << "Rhythm '" << rhythm_name << "' created successfully." << std::endl;
    } else {
        std::cout << "Error: Rhythm '" << rhythm_name << "' already exists." << std::endl;
    }
}

void change_rhythm_pattern(char pattern, std::string rhythm_name){
    std::lock_guard<std::shared_mutex> lock(state_mutex);
    if (rhythms.find(rhythm_name) != rhythms.end()) {
        rhythms[rhythm_name] = {pattern};
        std::cout << "Rhythm pattern for '" << rhythm_name << "' changed successfully." << std::endl;
    } else {
        std::cout << "Error: Rhythm '" << rhythm_name << "' not found." << std::endl;
    }
}


void change_instrument_pitch(float pitch, std::string instrument_name){
    std::shared_lock<std::shared_mutex> lock(state_mutex);
    auto inst = instruments.find(instrument_name);
    if(inst != instruments.end()) {
        if (pitch > 0) {
            inst->second.pitch = pitch;
            std::cout << "Pitch for instrument '" << instrument_name << "' changed to " << pitch << "." << std::endl;
        } else {
            std::cout << "Error: Invalid pitch value. Pitch must be greater than 0." << std::endl;
        }
    } else {
        std::cout << "Error: Instrument '" << instrument_name << "' not found." << std::endl;
    }
}

char get_instrument_rhythm(std::string instrument_name){
    std::shared_lock<std::shared_mutex> lock(state_mutex);
    auto inst = instruments.find(instrument_name);
    if(inst != instruments.end()) {
        std::string rhythm_id = inst->second.rhythm_id;
        return rhythms[rhythm_id].pattern;
    } else {
        std::cout << "Error: Instrument '" << instrument_name << "' not found." << std::endl;
        return '\0';
    }
}

void delete_instrument(std::string instrument_name){
    std::lock_guard<std::shared_mutex> lock(state_mutex);
    std::cout << "Attempting to delete instrument: " << instrument_name << std::endl;

    // Check if the instrument exists in the map
    if (instruments.find(instrument_name) != instruments.end()) {
        std::cout << "Instrument found. Deleting..." << std::endl;
        instruments.erase(instrument_name);
        std::cout << "Instrument deleted successfully." << std::endl;
    } else {
        std::cout << "Instrument not found. No deletion performed." << std::endl;
    }
}