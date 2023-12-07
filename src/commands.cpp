#include "music.h"
#include "instrument.h"

std::unordered_map<int, Instrument> instruments;
std::unordered_map<int, Rhythm> rhythms;
std::vector<std::string> instrument_names;
std::vector<std::string> rhythm_names;
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
    for (const auto& instrument_name : instrument_names) {
        auto it = std::find_if(instruments.begin(), instruments.end(),
                               [&](const auto& pair) { return pair.second.name == instrument_name; });
        if (it != instruments.end()) {
            std::cout << "Instrument Name: " << it->second.name << " - Output Channel: " << it->second.outputChannel << "\n";
        }
    }
}

void listRhythms() {
    std::shared_lock<std::shared_mutex> lock(state_mutex); // Ensures thread safety
    std::cout << "Rhythms:\n";
    for (size_t i = 0; i < rhythm_names.size(); ++i) {
        // Use the index to access the corresponding rhythm in the rhythms map
        auto it = rhythms.find(i);
        if (it != rhythms.end()) {
            std::cout << "Rhythm Name: " << rhythm_names[i] << " - Pattern: " << charToBinary(it->second.pattern) << "\n";
        }
    }
}


void create_instrument(const uint32_t outputChannel, std::string rhythm_name, std::string instrument_name, int pitchVal) {
    std::lock_guard<std::shared_mutex> lock(state_mutex);
    int rhythm_id = find_id_num(rhythm_names, rhythm_name);

    if(rhythm_id < 0){
        return;
    }

    if (!isDuplicate(instrument_names, instrument_name)) {
        int instrument_id = instrument_names.size();
        instrument_names.push_back(instrument_name); 

        try{
            Instrument newInstrument(outputChannel, rhythm_id, pitchVal);
            instruments.emplace(instrument_id, newInstrument);
        } catch (...) {
            std::cerr << "Failed to create instrument." << std::endl;
        }
    }
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

    if (!isDuplicate(rhythm_names, rhythm_name)) {
        int rhythm_id = rhythm_names.size();
        rhythm_names.push_back(rhythm_name);
        rhythms[rhythm_id] = {pattern};
    }
}

void change_rhythm_pattern(char pattern, std::string rhythm_name){
    std::lock_guard<std::shared_mutex> lock(state_mutex); // Ensures thread safety
    int rhythm_id = find_id_num(rhythm_names, rhythm_name);
    if(rhythm_id < 0){
        return;
    }
    rhythms[rhythm_id] = {pattern};
}

void change_instrument_pitch(float pitch, std::string instrument_name){
    int instrument_id = find_id_num(instrument_names, instrument_name);
    if(instrument_id < 0){
        return;
    }
    auto inst = instruments.find(instrument_id);
    if(inst != instruments.end() && pitch > 0){
        inst->second.pitch = pitch;
    }
}

char get_instrument_rhythm(std::string instrument_name){
    int instrument_id = find_id_num(instrument_names, instrument_name);
    if(instrument_id < 0){
        return '\0';
    }
    auto inst = instruments.find(instrument_id);
    if(inst != instruments.end()){
        int rhythm_id = inst->second.rhythm_id;
        return rhythms[rhythm_id].pattern;
    }
    return '\0';
}

void delete_instrument(std::string instrument_name){
    int instrument_id = find_id_num(instrument_names, instrument_name);
    if(instrument_id < 0){
        return;
    }
    instruments.erase(instrument_id);
}

