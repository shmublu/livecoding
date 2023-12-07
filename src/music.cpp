#include "music.h"
#include <thread>
#include <chrono>
#include <list>
#include <iostream>


const int periodSeconds = 4;
const int bitsInRhythm = 8;
const std::chrono::milliseconds interval(periodSeconds * 1000 / bitsInRhythm);

void music_thread_function() {

    while (true) {  // Infinite loop to keep the thread running
        {
            std::shared_lock<std::shared_mutex> lock(state_mutex);

            for (int bit = 0; bit < bitsInRhythm; ++bit) {
                for (auto& pair : instruments) {
                    int instrument_id = pair.first;
                    Instrument& instrument = pair.second;
                    const Rhythm& rhythm = rhythms[instrument.rhythm_id];
                    if (rhythm.pattern & (1ULL << bit)) {
                        instrument.play();
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
