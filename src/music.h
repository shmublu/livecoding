#ifndef MUSIC_H
#define MUSIC_H

#include "instrument.h"
#include <string>
#include <unordered_map>
#include <mutex>
#include <SFML/Audio.hpp>


struct Rhythm {
    char pattern;
};
extern std::unordered_map<int, Instrument> instruments;
extern std::unordered_map<int, Rhythm> rhythms;
extern std::mutex state_mutex;

void start_music_thread();
void create_instrument(const std::string& filepath, int rhythm_id, int instrument_id, int pitch);
void create_rhythm(char pattern, int rhythm_id);

void change_rhythm_pattern(char pattern, int rhythm_id);
void change_instrument_file(const std::string& filepath, int instrument_id);
void change_instrument_pitch(float pitch, int instrument_id);
char get_instrument_rhythm(int instrument_id);

#endif // MUSIC_H
