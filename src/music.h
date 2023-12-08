#ifndef MUSIC_H
#define MUSIC_H

#include "instrument.h"
#include <string>
#include <unordered_map>
#include <mutex>
#include <shared_mutex>

struct Rhythm {
    std::string pattern;
};

extern std::unordered_map<int, Instrument> instruments;
extern std::unordered_map<int, Rhythm> rhythms;

extern std::vector<std::string> instrument_names;
extern std::vector<std::string> rhythm_names;
extern std::shared_mutex state_mutex;

extern std::vector<float> key; 

void start_music_thread();
void create_instrument(const uint32_t outputChannel, std::string rhythm_name, std::string instrument_name);

void create_rhythm(std::string input, std::string rhythm_name);

void delete_instrument(std::string instrument_name);


void change_rhythm_pattern(std::string pattern, std::string rhythm_name);
std::string get_instrument_rhythm(std::string instrument_name);

void listRhythms();
void listInstruments();

#endif // MUSIC_H
