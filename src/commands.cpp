#include "music.h"
#include "instrument.h"
#include <vector>
#include <bitset>

std::unordered_map<std::string, Instrument> instruments;
std::unordered_map<std::string, Rhythm> rhythms;
std::shared_mutex state_mutex;

bool isDuplicate(const std::vector<std::string>& vec, const std::string& value) {
    return std::find(vec.begin(), vec.end(), value) != vec.end();
}


std::string charToBinary(char c) {
    return std::bitset<8>(c).to_string();
}

int find_id_num(const std::vector<std::string>& vec, const std::string& value){
    auto it = std::find(vec.begin(), vec.end(), value);
    if (it != vec.end()) {
        return std::distance(vec.begin(), it);
    }
    return 0;
}

void listInstruments() {
    std::shared_lock<std::shared_mutex> lock(state_mutex); // Ensures thread safety
    std::cout << "Instruments:\n";
    for (const auto& pair : instruments) {
        std::cout << "Instrument Name: " << pair.second.name << " - Sound File: " << pair.second.filepath  << " - Rhythm Name: " << pair.second.rhythm_id <<"\n";
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
        Instrument newInstrument(filepath, rhythm_name, pitchVal);
        instruments.emplace(rhythm_name, newInstrument);
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
    std::lock_guard<std::shared_mutex> lock(state_mutex); // Ensures thread safety
    //Convert rhythm string to character representation
    char pattern = convertToChar(input);
    rhythms[rhythm_name] = {pattern};
}

void change_rhythm_pattern(char pattern, std::string rhythm_name){
    std::lock_guard<std::shared_mutex> lock(state_mutex); // Ensures thread safety
    rhythms[rhythm_name] = {pattern};
}


void change_instrument_pitch(float pitch, std::string instrument_name){
    auto inst = instruments.find(instrument_name);
    if(inst != instruments.end() && pitch > 0){
        inst->second.pitch = pitch;
    }
}

char get_instrument_rhythm(std::string instrument_name){
    auto inst = instruments.find(instrument_name);
    if(inst != instruments.end()){
        std::string rhythm_id = inst->second.rhythm_id;
        return rhythms[rhythm_id].pattern;
    }
    return '\0';
}

void delete_instrument(std::string instrument_name){
    instruments.erase(instrument_name);
}
