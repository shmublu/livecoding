#ifndef MUSIC_H
#define MUSIC_H

#include "instrument.h"
#include <string>
#include <unordered_map>
#include <mutex>

struct Rhythm {
    char pattern;
};
extern std::unordered_map<int, Instrument> instruments;
extern std::unordered_map<int, Rhythm> rhythms;
extern std::mutex state_mutex;

void start_music_thread();
void create_instrument(const uint32_t outputChannel, int rhythm_id, int instrument_id, int pitch);
void create_rhythm(char pattern, int rhythm_id);

#endif // MUSIC_H
