#include "music.h"

std::unordered_map<int, Instrument> instruments;
std::unordered_map<int, Rhythm> rhythms;
std::mutex state_mutex;

void create_instrument(const std::string& filepath, int rhythm_id, int instrument_id) {
    std::lock_guard<std::mutex> guard(state_mutex);
    instruments[instrument_id] = {filepath, rhythm_id};
}

void create_rhythm(uint64_t pattern, int rhythm_id) {
    rhythms[rhythm_id] = {pattern};
}
