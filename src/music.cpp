#include "music.h"
#include <thread>
#include <chrono>
#include <list>
#include <iostream>
#include <vector>
#include <signal.h>

const int periodSeconds = 4;
const int bitsInRhythm = 8;
const std::chrono::milliseconds interval(periodSeconds * 1000 / bitsInRhythm);

std::vector<float> key = {0, 58, 60, 61, 63, 65, 66, 68, 70, 60};

// Define the function to be called when ctrl-c (SIGINT) is sent to process
void signal_callback_handler(int signum) {
    // std::cout << "Caught signal " << signum << std::endl;
    // for (auto& pair : instruments) {
    //     delete_instrument(instrument_names[pair.first]);
    // } 

    exit(signum);   
}

void music_thread_function() {

    while (true) {  // Infinite loop to keep the thread running
        {
            std::shared_lock<std::shared_mutex> lock(state_mutex);

            for (int bit = 0; bit < bitsInRhythm; ++bit) {
                // std::cout << bit << ": "; 
                for (auto& pair : instruments) {
                    int instrument_id = pair.first;
                    Instrument& instrument = pair.second;
                    const Rhythm& rhythm = rhythms[instrument.rhythm_id];
                    if (rhythm.pattern[bit] - '0') {
                        // std::cout << "id: " << instrument_id << " channel: " << instrument.outputChannel << std::endl; 
                        instrument.play(key[rhythm.pattern[bit] - '0']);
                    }
                }
                // std::this_thread::sleep_for(interval);
                // Release the lock before sleeping
                lock.unlock();
                std::this_thread::sleep_for(interval);
                // Re-acquire the lock after sleeping
                lock.lock();
            }
        }
        // std::this_thread::sleep_for(interval);
        // std::cout << std::endl; 
    }
}

void start_music_thread() {
    signal(SIGINT, signal_callback_handler);
    std::thread musicThread(music_thread_function);
    musicThread.detach(); // Detach the thread to run independently
    std::cerr << "Music thread started.\n"; 
}
