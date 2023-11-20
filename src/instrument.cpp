#include "instrument.h"
#include <unordered_map>

Instrument::Instrument(const std::string& path, int id) : filepath(path), rhythm_id(id),  player(path){
}

void Instrument::play(){
    player.playSound();
}

Instrument& Instrument::getInstrument(std::unordered_map<int, Instrument>& instruments, int instrument_id) {
    // Use emplace to add a new instrument if it doesn't exist
    auto it = instruments.find(instrument_id);

    // If not found, emplace a new instrument into the map
    if (it == instruments.end()) {
        Instrument newInstr("./samples/uh.wav", 0);
        it = instruments.emplace(instrument_id, newInstr).first;
    }

    return it->second;
}

Player::Player(const std::string& path) : filepath(path) {
    loadBuffer();
}

void Player::playSound(){
    // Load the audio file
    
    loadBuffer();

    sound.play();
    /*
    // Wait until the sound finishes playing
    while (sound.getStatus() == sf::Sound::Playing) {
        // You can add other logic here if needed
    }
    */
}

void Player::loadBuffer(){
    // Load the audio file
    if (!buffer.loadFromFile(filepath)) {
        std::cerr << "Error loading audio file." << std::endl;
    }

    // Set the buffer for the sound
    sound.setBuffer(buffer);
}