#include <iostream>
#include <vector>
#include <portaudio.h>
#include <sndfile.h>
#include <cmath>
#include <mutex>
#include <math.h>
#include <cstring>
#include <thread>

class SoundPlayer {
public:
    SoundPlayer(const std::string& filename)
        : pitchShiftFactor(1.0), bpmAdjustFactor(1.0) {
        // Open the sound file
        file = sf_open(filename.c_str(), SFM_READ, &sfinfo);
        if (file == nullptr) {
            throw std::runtime_error(sf_strerror(file));
        }

        // Initialize PortAudio
        PaError err = Pa_Initialize();
        if (err != paNoError) {
            throw std::runtime_error(Pa_GetErrorText(err));
        }

        // Setup the output stream parameters
        PaStreamParameters outputParameters;
        outputParameters.device = Pa_GetDefaultOutputDevice();
        outputParameters.channelCount = sfinfo.channels;
        outputParameters.sampleFormat = paFloat32;
        outputParameters.suggestedLatency = Pa_GetDeviceInfo(outputParameters.device)->defaultLowOutputLatency;
        outputParameters.hostApiSpecificStreamInfo = nullptr;

        // Open the audio stream
        err = Pa_OpenStream(&stream, nullptr, &outputParameters, sfinfo.samplerate, 256, paClipOff, &SoundPlayer::paCallback, this);
        if (err != paNoError) {
            sf_close(file);
            throw std::runtime_error(Pa_GetErrorText(err));
        }
    }

    ~SoundPlayer() {
        Pa_StopStream(stream);
        Pa_CloseStream(stream);
        Pa_Terminate();
        sf_close(file);
    }

    void play() {
        // Start the audio stream
        PaError err = Pa_StartStream(stream);
        if (err != paNoError) {
            throw std::runtime_error(Pa_GetErrorText(err));
        }
    }

    void setPitchShift(double pitchShift) {
        std::lock_guard<std::mutex> guard(controlMutex);
        pitchShiftFactor = pitchShift;
    }

    void setBpmAdjust(double bpmAdjust) {
        std::lock_guard<std::mutex> guard(controlMutex);
        bpmAdjustFactor = bpmAdjust;
    }

private:
    SNDFILE* file;
    SF_INFO sfinfo;
    PaStream* stream;
    double pitchShiftFactor;
    double bpmAdjustFactor;
    std::mutex controlMutex;

    static int paCallback(const void* inputBuffer, void* outputBuffer, unsigned long framesPerBuffer,
                          const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags, void* userData) {
        SoundPlayer* player = static_cast<SoundPlayer*>(userData);
        float* out = static_cast<float*>(outputBuffer);
        memset(out, 0, sizeof(float) * framesPerBuffer * player->sfinfo.channels);

        // Acquire the lock for thread safety
        std::lock_guard<std::mutex> guard(player->controlMutex);

        // Read and process audio data from file
        // This is where pitch shifting and BPM adjustment would take place
        // For the purposes of this example, we just read the data
       // Read and process audio data from file
            sf_count_t num_read = sf_read_float(player->file, out, framesPerBuffer * player->sfinfo.channels);

            // Loop the file if we reach the end
            if (static_cast<unsigned long>(num_read) < framesPerBuffer * player->sfinfo.channels) {
                sf_seek(player->file, 0, SEEK_SET);
            }

        // Simple pitch and tempo adjustment (for illustration only)
        // In a real application, use a proper pitch-shifting algorithm
        for (unsigned long i = 0; i < framesPerBuffer * player->sfinfo.channels; ++i) {
            out[i] *= std::pow(2.0, player->pitchShiftFactor - 1.0);
        }

        // Loop the file if we reach the end
        if (num_read < framesPerBuffer * player->sfinfo.channels) {
            sf_seek(player->file, 0, SEEK_SET);
        }

        return paContinue;
    }
};

int main() {
    try {
        SoundPlayer player("./samples/uh.wav");
        player.play();

        // Real-time control loop
        std::thread controlThread([&player]() {
            while (true) {
                // Here, you would implement real-time controls to change pitch and BPM
                // For example, listen to keyboard input or GUI controls
                // and call player.setPitchShift() or player.setBpmAdjust() accordingly
            }
        });

        controlThread.join();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return -1;
    }

    return 0;
}
