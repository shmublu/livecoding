#include "music.h"
#include "instrument.h"

std::unordered_map<int, Instrument> instruments;
std::unordered_map<int, Rhythm> rhythms;
std::mutex state_mutex;

void create_instrument(const std::string& filepath, int rhythm_id, int instrument_id, int pitchVal) {
    std::lock_guard<std::mutex> guard(state_mutex);
    Instrument newInstrument(filepath, rhythm_id, pitchVal);
    instruments.emplace(instrument_id, newInstrument);
}

void destroy_instrument(int instrument_id) {
    std::lock_guard<std::mutex> guard(state_mutex);
    if (instruments.find(instrument_id) != instruments.end()) {
    instruments.erase(instrument_id); // Delete the entry with the key 'id'
    }  
}


void create_rhythm(char pattern, int rhythm_id) {
    rhythms[rhythm_id] = {pattern};
}

void change_rhythm_pattern(char pattern, int rhythm_id){
    rhythms[rhythm_id] = {pattern};
}

void change_instrument_file(const std::string& filepath, int instrument_id){
    auto inst = instruments.find(instrument_id);
    if(inst != instruments.end()){
        inst->second.filepath = filepath;
    }
}

void change_instrument_pitch(float pitch, int instrument_id){
    auto inst = instruments.find(instrument_id);
    if(inst != instruments.end() && pitch > 0){
        inst->second.pitch = pitch;
    }
}

char get_instrument_rhythm(int instrument_id){
    auto inst = instruments.find(instrument_id);
    if(inst != instruments.end()){
        int rhythm_id = inst->second.rhythm_id;
        return rhythms[rhythm_id].pattern;
    }
    return '\0';
}
