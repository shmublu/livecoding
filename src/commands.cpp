#include "music.h"
#include "instrument.h"

std::unordered_map<std::string&, Instrument> instruments;
std::unordered_map<std::string&, Rhythm> rhythms;
std::mutex state_mutex;

void create_instrument(const std::string& filepath, const std::string& rhythm_id, const std::string& instrument_id, int pitchVal) {
    std::lock_guard<std::mutex> guard(state_mutex);
    Instrument newInstrument(filepath, rhythm_id, pitchVal);
    instruments.emplace(instrument_id, newInstrument);
}

void create_rhythm(char pattern, const std::string& rhythm_id) {
    rhythms[rhythm_id] = {pattern};
}

void change_rhythm_pattern(char pattern, const std::string& rhythm_id){
    rhythms[rhythm_id] = {pattern};
}

void change_instrument_file(const std::string& filepath,const std::string& instrument_id){
    auto inst = instruments.find(instrument_id);
    if(inst != instruments.end()){
        inst->second.filepath = filepath;
    }
}

void change_instrument_pitch(float pitch, const std::string& instrument_id){
    auto inst = instruments.find(instrument_id);
    if(inst != instruments.end() && pitch > 0){
        inst->second.pitch = pitch;
    }
}

char get_instrument_rhythm(const std::string& instrument_id){
    auto inst = instruments.find(instrument_id);
    if(inst != instruments.end()){
        std::string& rhythm_id = inst->second.rhythm_id;
        return rhythms[rhythm_id].pattern;
    }
    return '\0';
}
