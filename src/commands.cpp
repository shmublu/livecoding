#include "music.h"
#include "instrument.h"

std::unordered_map<int, Instrument> instruments;
std::unordered_map<int, Rhythm> rhythms;
std::mutex state_mutex;

void create_instrument(const uint32_t outputChannel, int rhythm_id, int instrument_id, int pitchVal) {
    try{
        std::lock_guard<std::mutex> guard(state_mutex);
        Instrument newInstrument(outputChannel, rhythm_id, pitchVal);
        instruments.emplace(instrument_id, newInstrument);
    } catch (...) {
        std::cerr << "Failed to create instrument." << std::endl;
    }
}

void create_rhythm(char pattern, int rhythm_id) {
    rhythms[rhythm_id] = {pattern};
}
