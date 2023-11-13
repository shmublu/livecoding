#include "music.h"
#include <thread>
#include <chrono>
#include <list>
#include <iostream>

const int periodSeconds = 4;
const int bitsInRhythm = 64;
const std::chrono::milliseconds interval(periodSeconds * 1000 / bitsInRhythm);

void music_thread_function() {
    std::list<sf::Sound> playingSounds;

    while (true) {  // Infinite loop to keep the thread running
        {
            std::lock_guard<std::mutex> guard(state_mutex);

            playingSounds.remove_if([](const sf::Sound& sound) {
                return sound.getStatus() != sf::Sound::Playing;
            });

            for (int bit = 0; bit < bitsInRhythm; ++bit) {
                for (const auto& [instrument_id, instrument] : instruments) {
                    const Rhythm& rhythm = rhythms[instrument.rhythm_id];
                    if (rhythm.pattern & (1ULL << bit)) {
                        std::cout << "id: " << instrument_id << std::endl;
                        /*
                        sf::SoundBuffer buffer;
                        if (buffer.loadFromFile(instrument.filepath)) {
                            sf::Sound sound;
                            sound.setBuffer(buffer);
                            sound.play();
                            playingSounds.push_back(std::move(sound));
                        } */
                    }
                }
                std::this_thread::sleep_for(interval);
            }
        }
        std::this_thread::sleep_for(interval);
    }
}

void start_music_thread() {
    std::thread musicThread(music_thread_function);
    musicThread.detach(); // Detach the thread to run independently
}
