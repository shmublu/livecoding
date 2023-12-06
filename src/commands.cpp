#include "music.h"
#include "instrument.h"
#include <vector>

std::unordered_map<int, Instrument> instruments;
std::unordered_map<int, Rhythm> rhythms;
std::vector<std::string> instrument_names;
std::vector<std::string> rhythm_names;
std::mutex state_mutex;

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

void create_instrument(const std::string& filepath, std::string rhythm_name, std::string instrument_name, int pitchVal) {
    std::lock_guard<std::mutex> guard(state_mutex);
    int rhythm_id = find_id_num(rhythm_names, rhythm_name);
    if(rhythm_id < 0){
        return;
    }

    if (!isDuplicate(instrument_names, instrument_name)) {
        int instrument_id = instrument_names.size();
        instrument_names.push_back(instrument_name);
        Instrument newInstrument(filepath, rhythm_id, pitchVal);
        instruments.emplace(instrument_id, newInstrument);
    }

}

void create_rhythm(char pattern, std::string rhythm_name) {
    if (!isDuplicate(rhythm_names, rhythm_name)) {
        int rhythm_id = rhythm_names.size();
        rhythm_names.push_back(rhythm_name);
        rhythms[rhythm_id] = {pattern};
    }
}

void change_rhythm_pattern(char pattern, std::string rhythm_name){
    int rhythm_id = find_id_num(rhythm_names, rhythm_name);
    if(rhythm_id < 0){
        return;
    }
    rhythms[rhythm_id] = {pattern};
}

void change_instrument_file(const std::string& filepath, std::string instrument_name){
    int instrument_id = find_id_num(instrument_names, instrument_name);
    if(instrument_id < 0){
        return;
    }
    auto inst = instruments.find(instrument_id);
    if(inst != instruments.end()){
        inst->second.filepath = filepath;
    }
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
