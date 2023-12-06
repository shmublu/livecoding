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
extern std::unordered_map<std::string&, Instrument> instruments;
extern std::unordered_map<std::string&, Rhythm> rhythms;
extern std::mutex state_mutex;

void start_music_thread();
void create_instrument(const std::string& filepath, const std::string& rhythm_id, const std::string& instrument_id, int pitch);
void create_rhythm(char pattern, const std::string& rhythm_id);

void change_rhythm_pattern(char pattern, const std::string& rhythm_id);
void change_instrument_file(const std::string& filepath, const std::string& instrument_id);
void change_instrument_pitch(float pitch, std::string& instrument_id);
char get_instrument_rhythm(std::string& instrument_id);

#endif // MUSIC_H
