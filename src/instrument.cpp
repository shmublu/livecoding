#include "instrument.h"
#include <unordered_map>

Instrument::Instrument(const std::string& path, int id, float pitchVal) : filepath(path), rhythm_id(id),  pitch(pitchVal), player(path){
}

void Instrument::play(){
    std::thread([this]() {
            this->player.playSound(pitch);
        }).detach(); // Detach the thread to run independently
}
Instrument& Instrument::getInstrument(std::unordered_map<int, Instrument>& instruments, int instrument_id, float pitchVal) {
    auto it = instruments.find(instrument_id);

    // If not found, emplace a new instrument into the map
    if (it == instruments.end()) {
        Instrument newInstr("./samples/uh.wav", 0, pitchVal);
        it = instruments.emplace(instrument_id, newInstr).first;
    }

    return it->second;
}

Player::Player(const std::string& path) : filepath(path) {
    loadBuffer();
}

void Player::playSound(float pitch){
    // Load the audio file
    
    loadBuffer();
    sound.setPitch(pitch);

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
        // return;
    }

    // Set the buffer for the sound
    sound.setBuffer(buffer);
}