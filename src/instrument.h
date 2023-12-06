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

    void playSound(float pitch);
    void loadBuffer();
    
private:
    sf::Sound sound;
    sf::SoundBuffer buffer;
    bool bufferLoaded = false;     
};

class Instrument {
public:
    std::string filepath;
    std::string rhythm_id;
    float pitch;
    Player player;
    std::string name;

    Instrument(const std::string& path, std::string id, float pitch);
    void play();

    static Instrument& getInstrument(std::unordered_map<int, Instrument>& instruments, int instrument_id, float pitchVal);


};

#endif // INSTRUMENT_H
