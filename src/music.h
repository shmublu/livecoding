#ifndef MUSIC_H
#define MUSIC_H

#include "instrument.h"
#include <string>
#include <unordered_map>
#include <mutex>
#include <SFML/Audio.hpp>


struct Rhythm {
    uint64_t pattern;
};
extern std::unordered_map<int, Instrument> instruments;
extern std::unordered_map<int, Rhythm> rhythms;
extern std::mutex state_mutex;

void start_music_thread();
void create_instrument(const std::string& filepath, int rhythm_id, int instrument_id);
void create_rhythm(uint64_t pattern, int rhythm_id);

#endif // MUSIC_H
