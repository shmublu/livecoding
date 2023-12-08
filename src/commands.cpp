#include "music.h"

std::unordered_map<int, Instrument> instruments;
std::unordered_map<int, Rhythm> rhythms;
std::vector<std::string> instrument_names;
std::vector<std::string> rhythm_names;
std::shared_mutex state_mutex;

bool isDuplicate(const std::vector<std::string>& vec, const std::string& value) {
    return std::find(vec.begin(), vec.end(), value) != vec.end();
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
            std::cout << "Rhythm Name: " << rhythm_names[i] << " - Pattern: " << it->second.pattern << "\n";
        }
    }
}

void create_instrument(const uint32_t outputChannel, std::string rhythm_name, std::string instrument_name) {
    std::lock_guard<std::shared_mutex> lock(state_mutex);
    int rhythm_id = find_id_num(rhythm_names, rhythm_name);

    if(rhythm_id < 0){
        return;
    }

    if (!isDuplicate(instrument_names, instrument_name)) {
        int instrument_id = instrument_names.size();
        instrument_names.push_back(instrument_name); 

        try{
            Instrument newInstrument(outputChannel, rhythm_id);
            instruments.emplace(instrument_id, newInstrument);
            std::cout << "Created instrument " << instrument_name << std::endl;
        } catch (...) {
            std::cerr << "Failed to create instrument." << std::endl;
        }
    }
}

void create_rhythm(std::string input, std::string rhythm_name) {
    std::lock_guard<std::shared_mutex> lock(state_mutex); // Ensures thread safety
    //Convert rhythm string to character representation
    std::string pattern = input;

    if (!isDuplicate(rhythm_names, rhythm_name)) {
        int rhythm_id = rhythm_names.size();
        rhythm_names.push_back(rhythm_name);
        rhythms[rhythm_id] = {pattern};
        std::cout << "Created rhythm " << rhythm_name << std::endl;
    }
}

void change_rhythm_pattern(std::string pattern, std::string rhythm_name){
    std::lock_guard<std::shared_mutex> lock(state_mutex); // Ensures thread safety
    int rhythm_id = find_id_num(rhythm_names, rhythm_name);
    if(rhythm_id < 0){
        return;
    }
    rhythms[rhythm_id] = {pattern};
}

std::string get_instrument_rhythm(std::string instrument_name){
    int instrument_id = find_id_num(instrument_names, instrument_name);
    if(instrument_id < 0){
        return "";
    }
    auto inst = instruments.find(instrument_id);
    if(inst != instruments.end()){
        int rhythm_id = inst->second.rhythm_id;
        return rhythms[rhythm_id].pattern;
    }
    return "";
}

void delete_instrument(std::string instrument_name){
    int instrument_id = find_id_num(instrument_names, instrument_name);
    if(instrument_id < 0){
        return;
    }
    instruments.erase(instrument_id);
    std::cout << "Deleted instrument " << instrument_name << std::endl;
}

