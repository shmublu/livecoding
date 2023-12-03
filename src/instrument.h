#ifndef INSTRUMENT_H
#define INSTRUMENT_H

#include <string>
#include <SFML/Audio.hpp>
#include <iostream>
#include <unordered_map>
#include <thread>

class Player {
public:
    std::string filepath;
    
    Player(const std::string& path);

    void playSound();
    void loadBuffer();
    
private:
    sf::Sound sound;
    sf::SoundBuffer buffer;
    bool bufferLoaded = false;     
};

class Instrument {
public:
    std::string filepath;
    int rhythm_id;
    Player player;

    Instrument(const std::string& path, int id);
    void play();

    static Instrument& getInstrument(std::unordered_map<int, Instrument>& instruments, int instrument_id);


};

#endif // INSTRUMENT_H
