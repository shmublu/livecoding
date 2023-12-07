#ifndef INSTRUMENT_H
#define INSTRUMENT_H

#include <string>
#include <iostream>
#include <unordered_map>
#include <thread>
#include "../external/rtmidi/RtMidi.h"

class Player {
public:
    uint32_t outputChannel;
    Player(const uint32_t outputChannel);
    void playSound(float pitch);
    RtMidiOut * midiout;
};

class Instrument {
public:
    uint32_t outputChannel;
    int rhythm_id;
    int pitch;
    Player player;
    std::string name;

    Instrument(const uint32_t outputChannel, int id, int pitch);
    
    void play();

    //static Instrument& getInstrument(std::unordered_map<int, Instrument>& instruments, int instrument_id, float pitchVal);

};

#endif // INSTRUMENT_H
