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

// Instrument& Instrument::getInstrument(std::unordered_map<int, Instrument>& instruments, int instrument_id, float pitchVal) {
//     // auto it = instruments.find(instrument_id);

//     // // If not found, emplace a new instrument into the map
//     // if (it == instruments.end()) {
//     //     Instrument newInstr(0, 0, pitchVal);
//     //     it = instruments.emplace(instrument_id, newInstr).first;
//     // }

//     auto it = instruments.find(instrument_id);
//     return it->second;
// }

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

    std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // Platform-dependent ... see example in tests directory.
 
    // Note Off: 128, 64, 40
    message[0] = 128;
    message[1] = 64;
    message[2] = 40;
    midiout->sendMessage( &message );


}