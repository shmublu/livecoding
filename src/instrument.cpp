#include "instrument.h"
#include <unordered_map>
#include <iostream>

Instrument::Instrument(const uint32_t channel, int id, int pitchVal) : outputChannel(channel), rhythm_id(id),  pitch(pitchVal), player(channel){
}

void Instrument::play(){
    std::thread([this]() {
            this->player.playSound(pitch);
        }).detach(); // Detach the thread to run independently
}

Player::Player(const uint32_t channel) : outputChannel(channel) {
    Player::midiout = 0;

    try {
        midiout = new RtMidiOut(RtMidi::Api::UNSPECIFIED);
    }
    catch ( RtMidiError &error ) {
        error.printMessage();
        return;
    }

    std::string portName;
    unsigned int nPorts = midiout->getPortCount();
    if ( nPorts == 0 ) {
        std::cerr << "No output ports available!" << std::endl;
        goto cleanup;
    }
    if(channel >= nPorts) {
        std::cerr << "Channel number " << channel << " is not open." << std::endl;
        goto cleanup;
    }

    try {
        midiout->openPort(channel);
    }
    catch ( RtMidiError &error ) {
        error.printMessage();
        goto cleanup;
    }

    return;

    cleanup:
        delete midiout;
        throw std::invalid_argument("Instrument creation failed."); 
    
    return;

}

void Player::playSound(float pitch){
    std::vector<unsigned char> message(3);
    // Note On: 144, 64, 90
    message[0] = 144;
    message[1] = 64;
    message[2] = 90;
    try {
        midiout->sendMessage( &message );
    }
    catch ( RtMidiError &error ) {
        error.printMessage();
        exit(EXIT_FAILURE);
    }
}