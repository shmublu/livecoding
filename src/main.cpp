#include <SFML/Audio.hpp>
#include <iostream>

int main() {
    // Create an SFML sound object
    sf::Sound sound;

    // Load the audio file
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile("./samples/uh.wav")) {
        std::cerr << "Error loading audio file." << std::endl;
        return 1;
    }

    // Set the buffer for the sound
    sound.setBuffer(buffer);

    // Play the sound
    sound.play();

    // Wait until the sound finishes playing
    while (sound.getStatus() == sf::Sound::Playing) {
        // You can add other logic here if needed
    }

    return 0;
}
