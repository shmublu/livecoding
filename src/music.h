#ifndef MUSIC_H
#define MUSIC_H

#include "instrument.h"
#include <string>
#include <unordered_map>
#include <shared_mutex>
#include <SFML/Audio.hpp>


struct Rhythm {
    char pattern;
};
extern std::unordered_map<int, Instrument> instruments;
extern std::unordered_map<int, Rhythm> rhythms;
extern std::vector<std::string> instrument_names;
extern std::vector<std::string> rhythm_names;
extern std::shared_mutex state_mutex;

void start_music_thread();

void create_instrument(const std::string& filepath, std::string rhythm_name, std::string instrument_name, int pitch);
void create_rhythm(std::string pattern, std::string rhythm_id);

void delete_instrument(std::string instrument_name);

void change_rhythm_pattern(char pattern, std::string rhythm_name);
void change_instrument_pitch(float pitch, std::string instrument_name);
char get_instrument_rhythm(std::string instrument_name);

void listRhythms();
void listInstruments();

#endif // MUSIC_H
